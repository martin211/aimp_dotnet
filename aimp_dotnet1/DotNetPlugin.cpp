#include "Stdafx.h"
#include "DotNetPlugin.h"

DotNetPlugin::DotNetPlugin()
{
    _optionsLoaded = false;
    _pluginSettings = LoadDotNetPlugin();
}

// TODO: Add finalizer.

PWCHAR WINAPI DotNetPlugin::InfoGet(int index)
{
    switch (index)
    {
    case AIMP_PLUGIN_INFO_NAME:
    {
        pin_ptr<const wchar_t> str1 = PtrToStringChars(_pluginSettings->Name);
        return (PWCHAR)str1;
    }
    case AIMP_PLUGIN_INFO_AUTHOR:
    {
        pin_ptr<const wchar_t> str1 = PtrToStringChars(_pluginSettings->Author);
        return (PWCHAR)str1;
    }
    case AIMP_PLUGIN_INFO_SHORT_DESCRIPTION:
    {
        pin_ptr<const wchar_t> str1 = PtrToStringChars(_pluginSettings->Description);
        return (PWCHAR)str1;
    }
    case AIMP_PLUGIN_INFO_FULL_DESCRIPTION:
    {
        pin_ptr<const wchar_t> str1 = PtrToStringChars(_pluginSettings->FullDescription);
        return (PWCHAR)str1;
    }
    }

    return NULL;
}

DWORD WINAPI DotNetPlugin::InfoGetCategories()
{
    return AIMP_PLUGIN_CATEGORY_ADDONS;
}

HRESULT WINAPI DotNetPlugin::Initialize(IAIMPCore* core)
{
    System::Diagnostics::Debug::WriteLine("BEGIN: Initialize DotNet plugin");

    _managedCore = gcnew ManagedAimpCore(core);
    _managedExtension = gcnew ManagedFunctionality(core, _managedCore);
    _configurationManager = gcnew AIMP::AimpConfigurationManager(_managedCore);
//    _proxyManager = new AIMP::Proxy::ProxyManager(this, _managedCore);

    LoadExtensions(core);

    if (_configurationManager->GetValueAsInt32("AimpDotNet\\Settings\\DebugMode") == 1)
    {
        String ^path;
        _managedCore->GetPath(AimpMessages::AimpCorePathType::AIMP_CORE_PATH_PROFILE, path);
        AIMP::SDK::InternalLogger::Instance->Initialize(path, "aimp_dotnet.log");
    }

    _pluginSettings->PluginInformation->PluginLoadEvent += gcnew AIMP::SDK::PluginLoadUnloadEvent(_managedExtension, &ManagedFunctionality::PluginLoadEventReaction);
    _pluginSettings->PluginInformation->PluginUnloadEvent += gcnew AIMP::SDK::PluginLoadUnloadEvent(_managedExtension, &ManagedFunctionality::PluginUnloadEventReaction);
    _pluginSettings->PluginInformation->Load();

    AIMP::SDK::InternalLogger::Instance->Write("Initialized");
    System::Diagnostics::Debug::WriteLine("END: Initialize DotNet plugin");

    return S_OK;
}

HRESULT WINAPI DotNetPlugin::Finalize()
{
    _pluginSettings->PluginInformation->Unload();
    _pluginSettings->PluginInformation->PluginLoadEvent -= gcnew AIMP::SDK::PluginLoadUnloadEvent(_managedExtension, &ManagedFunctionality::PluginLoadEventReaction);
    _pluginSettings->PluginInformation->PluginUnloadEvent -= gcnew AIMP::SDK::PluginLoadUnloadEvent(_managedExtension, &ManagedFunctionality::PluginUnloadEventReaction);

    _optionsLoaded = false;

    AIMP::SDK::CustomAssemblyResolver::Deinitialize();
    AIMP::SDK::InternalLogger::Instance->Close();
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

    if (IID_IUnknown == riid) {
        *ppvObj = this;
        AddRef();
        System::Diagnostics::Debug::WriteLine("DotNetPlugin: QueryInterface: S_OK");
        return S_OK;
    }

    if (riid == IID_IAIMPExtensionPlaylistManagerListener)
    {
        *ppvObj = _listner;
        AddRef();
        System::Diagnostics::Debug::WriteLine("DotNetPlugin: QueryInterface: S_OK");
        return S_OK;
    }

    if (riid == IID_IAIMPExtensionPlayerHook)
    {
        *ppvObj = this->_playerHook;
        AddRef();
        System::Diagnostics::Debug::WriteLine("DotNetPlugin: QueryInterface: S_OK");
        return S_OK;
    }

    System::Diagnostics::Debug::WriteLine("DotNetPlugin: QueryInterface: E_NOINTERFACE");
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

AIMP::SDK::AimpDotNetPlugin^ DotNetPlugin::LoadDotNetPlugin()
{
    System::String^ path = System::Reflection::Assembly::GetExecutingAssembly()->Location;
    AIMP::SDK::CustomAssemblyResolver::Initialize(System::IO::Path::GetDirectoryName(path));
    return AIMP::SDK::PluginInfoLoader::LoadPlugin(System::IO::Path::GetDirectoryName(path));
}

void DotNetPlugin::SavePluginOptions()
{
    //	_pluginState->Save(_pluginSettings);
}

HRESULT DotNetPlugin::LoadExtensions(IAIMPCore* core)
{
    HRESULT r = S_OK;

    //IAIMPOptionsDialogFrame *frame = new OptionFrame(_managedCore, this);
    //_frame = frame;
    //r = core->RegisterExtension(IID_IAIMPServiceOptionsDialog, frame);

    IAIMPExtensionPlaylistManagerListener *listner = new PlaylistManagerListener(this);
    _listner = listner;
    r = core->RegisterExtension(IID_IAIMPServicePlaylistManager, listner);

    _playerHook = new AimpExtensionPlayerHook(this);
    r = core->RegisterExtension(IID_IAIMPServicePlayer, _playerHook);

    return r;
}
