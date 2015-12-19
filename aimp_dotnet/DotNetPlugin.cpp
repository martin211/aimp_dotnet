#include "Stdafx.h"
#include "DotNetPlugin.h"
#include "vcclr.h"
//#include "Extensions/OptionsDialogFrameExtension.h"

DotNetPlugin::DotNetPlugin()
{
    _optionsLoaded = false;
    System::String ^path = System::IO::Path::GetDirectoryName(System::Reflection::Assembly::GetExecutingAssembly()->Location);
    AIMP::SDK::CustomAssemblyResolver::Initialize(path);
    _dotNetPlugin = AIMP::SDK::PluginInfoLoader::LoadPlugin(path);

    AIMP::SDK::Player::IAimpPlayer ^plr = nullptr;
}

// TODO: Add finalizer.
PWCHAR WINAPI DotNetPlugin::InfoGet(int index)
{
    switch (index)
    {
    case AIMP_PLUGIN_INFO_NAME:
    {
        pin_ptr<const wchar_t> str1 = PtrToStringChars(_dotNetPlugin->Name);
        return (PWCHAR)str1;
    }
    case AIMP_PLUGIN_INFO_AUTHOR:
    {
        pin_ptr<const wchar_t> str1 = PtrToStringChars(_dotNetPlugin->Author);
        return (PWCHAR)str1;
    }
    case AIMP_PLUGIN_INFO_SHORT_DESCRIPTION:
    {
        pin_ptr<const wchar_t> str1 = PtrToStringChars(_dotNetPlugin->Description);
        return (PWCHAR)str1;
    }
    case AIMP_PLUGIN_INFO_FULL_DESCRIPTION:
    {
        pin_ptr<const wchar_t> str1 = PtrToStringChars(_dotNetPlugin->FullDescription);
        return (PWCHAR)str1;
    }
    }

    return NULL;
}

DWORD WINAPI DotNetPlugin::InfoGetCategories()
{
    return (DWORD)_dotNetPlugin->PluginInformation->PluginInfo->AimpPluginType;
}

HRESULT WINAPI DotNetPlugin::Initialize(IAIMPCore* core)
{
    System::Diagnostics::Debug::WriteLine("BEGIN: Initialize DotNet plugin");

    _managedExtension = gcnew ManagedFunctionality(core);

    _dotNetPlugin->PluginInformation->PluginLoadEvent += gcnew AIMP::SDK::PluginLoadUnloadEvent(_managedExtension, &ManagedFunctionality::PluginLoadEventReaction);
    _dotNetPlugin->PluginInformation->PluginUnloadEvent += gcnew AIMP::SDK::PluginLoadUnloadEvent(_managedExtension, &ManagedFunctionality::PluginUnloadEventReaction);
    _dotNetPlugin->PluginInformation->Load();


    System::Diagnostics::Debug::WriteLine("END: Initialize DotNet plugin");

    return S_OK;
}

HRESULT WINAPI DotNetPlugin::Finalize()
{
    _dotNetPlugin->PluginInformation->Unload();
    _dotNetPlugin->PluginInformation->PluginLoadEvent -= gcnew AIMP::SDK::PluginLoadUnloadEvent(_managedExtension, &ManagedFunctionality::PluginLoadEventReaction);
    _dotNetPlugin->PluginInformation->PluginUnloadEvent -= gcnew AIMP::SDK::PluginLoadUnloadEvent(_managedExtension, &ManagedFunctionality::PluginUnloadEventReaction);
    
    AIMP::SDK::CustomAssemblyResolver::Deinitialize();
    System::GC::Collect();

    return S_OK;
}

void WINAPI DotNetPlugin::SystemNotification(int NotifyID, IUnknown* Data)
{

}

HRESULT WINAPI DotNetPlugin::QueryInterface(REFIID riid, LPVOID* ppvObj)
{
    System::Diagnostics::Debug::WriteLine("DotNetPlugin: QueryInterface");
    if (!ppvObj) {
        return E_POINTER;
    }

    if (riid == IID_IAIMPExternalSettingsDialog)
    {
        if (_dotNetPlugin->PluginInformation->PluginInfo->IsExternalSettingsDialog)
        {
            *ppvObj = this;
            return S_OK;
        }

        return E_NOINTERFACE;
    }

    return E_NOINTERFACE;
}

ULONG WINAPI DotNetPlugin::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI DotNetPlugin::Release(void)
{
    return Base::Release();
}

void WINAPI DotNetPlugin::Show(HWND ParentWindow)
{
    System::IntPtr parent = System::IntPtr(ParentWindow);
    _dotNetPlugin->PluginInformation->ShowSettingDialog(parent);
}
