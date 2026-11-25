//  ----------------------------------------------------
//  AIMP Managed Host - native bootstrap shim
//
//  Pure Win32. No C++/CLI, no AIMP SDK headers.
//
//  AIMP loads this DLL and calls AIMPPluginGetHeader. The shim starts the
//  CLR, lets the managed host build the plugin object and hands the
//  resulting COM callable wrapper (CCW) back to AIMP. From that moment
//  every vtable call goes straight into managed code.
//
//  Expected layout (matches the AIMP per plugin folder convention):
//
//      Plugins\aimp_managed\aimp_managed.dll      <- this shim
//      Plugins\aimp_managed\AIMP.SDK.dll      <- managed host
//      Plugins\aimp_managed\<YourPlugin>.dll      <- plugin written in C#
//  ----------------------------------------------------

#include <windows.h>
#include <metahost.h>

#include <cwchar>
#include <string>

#pragma comment(lib, "mscoree.lib")

// MSVC provides this symbol for the current module image.
extern "C" IMAGE_DOS_HEADER __ImageBase;

namespace
{
    const wchar_t* const kHostMethod = L"Start";
    const wchar_t* const kClrVersion = L"v4.0.30319";

    // New layout: AIMP.Host.dll is a small, version-stable launcher that starts
    // the per-plugin AIMP.SDK.dll in its own AppDomain. The AIMP.SDK entries
    // keep installations created before the split working.
    struct HostEntry
    {
        const wchar_t* assembly;
        const wchar_t* type;
    };

    const HostEntry kHostEntries[] = {
        { L"AIMP.Host.dll", L"AIMP.Host.Bootstrap" },
        { L"AIMP.SDK.dll", L"AIMP.Loader.Bootstrap" },
        { L"AIMP.SDK.dll", L"AIMP.SDK.Loader.Bootstrap" }
    };

    bool FileExists(const std::wstring& path)
    {
        const DWORD attributes = GetFileAttributesW(path.c_str());
        return attributes != INVALID_FILE_ATTRIBUTES &&
               (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
    }

    // Set by AimpShimSetPlugin() from managed code.
    void* g_plugin = nullptr;

    HMODULE SelfModule()
    {
        return reinterpret_cast<HMODULE>(&__ImageBase);
    }

    std::wstring SelfDirectory()
    {
        wchar_t path[MAX_PATH * 2] = {};
        const DWORD length = GetModuleFileNameW(SelfModule(), path, ARRAYSIZE(path));
        if (length == 0)
        {
            return std::wstring(L".\\");
        }

        std::wstring result(path, length);
        const std::wstring::size_type slash = result.find_last_of(L"\\/");
        return slash == std::wstring::npos ? std::wstring(L".\\") : result.substr(0, slash + 1);
    }

    std::wstring LogPath()
    {
        SYSTEMTIME time = {};
        GetLocalTime(&time);

        wchar_t name[32] = {};
        swprintf_s(name, L"%04d%02d%02d.log", time.wYear, time.wMonth, time.wDay);

        const std::wstring directory = SelfDirectory() + L"logs\\";
        CreateDirectoryW(directory.c_str(), nullptr);

        return directory + name;
    }

    void AppendLog(const std::wstring& message)
    {
        const std::wstring path = LogPath();

        const HANDLE file = CreateFileW(path.c_str(), FILE_APPEND_DATA,
                                         FILE_SHARE_READ | FILE_SHARE_WRITE,
                                         nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (file == INVALID_HANDLE_VALUE)
        {
            return;
        }

        const int size = WideCharToMultiByte(CP_UTF8, 0, message.c_str(), -1, nullptr, 0, nullptr, nullptr);
        if (size > 1)
        {
            std::string utf8(static_cast<size_t>(size - 1), '\0');
            WideCharToMultiByte(CP_UTF8, 0, message.c_str(), -1, &utf8[0], size, nullptr, nullptr);

            DWORD written = 0;
            WriteFile(file, utf8.data(), static_cast<DWORD>(utf8.size()), &written, nullptr);
        }

        CloseHandle(file);
    }

    void Trace(const wchar_t* message)
    {
        OutputDebugStringW(L"[aimp_managed] ");
        OutputDebugStringW(message);
        OutputDebugStringW(L"\n");

        SYSTEMTIME time = {};
        GetLocalTime(&time);

        wchar_t prefix[64] = {};
        swprintf_s(prefix, L"%04d-%02d-%02d %02d:%02d:%02d.%03d [shim] ",
                   time.wYear, time.wMonth, time.wDay,
                   time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

        AppendLog(std::wstring(prefix) + message + L"\n");
    }

    void TraceHr(const wchar_t* what, HRESULT hr)
    {
        wchar_t buffer[512] = {};
        swprintf_s(buffer, L"%ls: hr = 0x%08X", what, static_cast<unsigned>(hr));
        Trace(buffer);
    }

    // Starts the CLR, runs AIMP.SDK.Bootstrap.Start and receives the
    // plugin object through AimpShimSetPlugin.
    HRESULT RunManagedBootstrap(const std::wstring& hostDirectory)
    {
        ICLRMetaHost* metaHost = nullptr;
        ICLRRuntimeInfo* runtimeInfo = nullptr;
        ICLRRuntimeHost* runtimeHost = nullptr;

        HRESULT hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost,
                                       reinterpret_cast<void**>(&metaHost));
        if (FAILED(hr))
        {
            TraceHr(L"CLRCreateInstance failed", hr);
            return hr;
        }

        hr = metaHost->GetRuntime(kClrVersion, IID_ICLRRuntimeInfo,
                                  reinterpret_cast<void**>(&runtimeInfo));
        metaHost->Release();

        if (FAILED(hr))
        {
            TraceHr(L"ICLRMetaHost::GetRuntime failed (.NET Framework 4.x is required)", hr);
            return hr;
        }

        hr = runtimeInfo->GetInterface(CLSID_CLRRuntimeHost, IID_ICLRRuntimeHost,
                                       reinterpret_cast<void**>(&runtimeHost));
        runtimeInfo->Release();

        if (FAILED(hr))
        {
            TraceHr(L"ICLRRuntimeInfo::GetInterface failed", hr);
            return hr;
        }

        // S_FALSE when the runtime is already started - that is fine.
        hr = runtimeHost->Start();
        if (FAILED(hr))
        {
            TraceHr(L"ICLRRuntimeHost::Start failed", hr);
            runtimeHost->Release();
            return hr;
        }

        // Single string argument: "<host directory>|<module handle>".
        // The module handle lets the managed side call back into *this*
        // instance of the shim (important when AIMP loads several copies).
        wchar_t argument[2048] = {};
        swprintf_s(argument, L"%ls|%llu", hostDirectory.c_str(),
                   static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(SelfModule())));

        DWORD result = 0;
        HRESULT lastError = E_FAIL;
        bool started = false;

        for (const HostEntry& entry : kHostEntries)
        {
            const std::wstring assemblyPath = hostDirectory + entry.assembly;
            if (!FileExists(assemblyPath))
            {
                continue;
            }

            {
                const std::wstring message = std::wstring(L"bootstrap: ") + entry.assembly + L" / " + entry.type;
                Trace(message.c_str());
            }

            hr = runtimeHost->ExecuteInDefaultAppDomain(assemblyPath.c_str(), entry.type, kHostMethod, argument, &result);
            if (SUCCEEDED(hr))
            {
                started = true;
                break;
            }

            lastError = hr;
        }

        runtimeHost->Release();

        if (!started)
        {
            TraceHr(L"ExecuteInDefaultAppDomain failed", lastError);
            return lastError;
        }

        return result == 0 ? S_OK : E_FAIL;
    }
}

extern "C" BOOL WINAPI AIMPPluginGetHeader(void** header)
{
    if (header == nullptr)
    {
        return FALSE;
    }

    *header = nullptr;

    if (g_plugin != nullptr)
    {
        // AIMP may ask twice, keep the same object.
        *header = g_plugin;
        return TRUE;
    }

    const std::wstring hostDirectory = SelfDirectory();
    Trace((L"AIMPPluginGetHeader: dir = " + hostDirectory).c_str());

    const HRESULT hr = RunManagedBootstrap(hostDirectory);
    if (FAILED(hr))
    {
        Trace(L"managed host failed to start");
        return FALSE;
    }

    if (g_plugin == nullptr)
    {
        Trace(L"managed host returned no plugin object");
        return FALSE;
    }

    Trace(L"plugin object handed to AIMP");
    *header = g_plugin;
    return TRUE;
}

extern "C" void WINAPI AimpShimSetPlugin(void* plugin)
{
    if (plugin == nullptr)
    {
        return;
    }

    // Keep our own reference: AIMP releases the pointer returned by
    // AIMPPluginGetHeader, but the shim caches it and may hand it out again.
    // The shim has no AIMP headers, so AddRef is taken straight from the vtable
    // (slot 1 of IUnknown).
    using AddRefFn = ULONG(WINAPI*)(void*);
    void** vtable = *reinterpret_cast<void***>(plugin);
    if (vtable != nullptr && vtable[1] != nullptr)
    {
        reinterpret_cast<AddRefFn>(vtable[1])(plugin);
    }

    g_plugin = plugin;
    Trace(L"AimpShimSetPlugin: plugin object cached");
}
