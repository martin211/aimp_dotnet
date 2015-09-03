#include "Stdafx.h"
#include "DotNetPlugin.h"

DotNetPlugin::DotNetPlugin()
{
	_optionsLoaded = false;
}

PWCHAR WINAPI DotNetPlugin::InfoGet(int index)
{
	switch (index)
	{
	case AIMP36SDK::AIMP_PLUGIN_INFO_NAME:
		return L"AIMP DotNet Plugin";
	case AIMP36SDK::AIMP_PLUGIN_INFO_AUTHOR:
		return L"Evgeniy Bogdan";
	case AIMP36SDK::AIMP_PLUGIN_INFO_SHORT_DESCRIPTION:
		return L".NET Interop plugin";
	case AIMP36SDK::AIMP_PLUGIN_INFO_FULL_DESCRIPTION:
		return L".NET Interop plugin";
	}

	return NULL;
}

DWORD WINAPI DotNetPlugin::InfoGetCategories()
{
	return AIMP36SDK::AIMP_PLUGIN_CATEGORY_ADDONS;
}

HRESULT WINAPI DotNetPlugin::Initialize(AIMP36SDK::IAIMPCore* core)
{
	System::Diagnostics::Debug::WriteLine("BEGIN: Initialize DotNet plugin");

	_managedCore = gcnew AIMP::SDK360::ManagedAimpCore(core);
	_managedExtension = gcnew ManagedFunctionality(core);
	_configurationManager = gcnew AIMP::ConfigurationManager(_managedCore);

	LoadExtensions(core);

	if (_configurationManager->GetValueAsInt32("AimpDotNet\\Settings\\DebugMode") == 1)
	{
		AIMP::SDK::InternalLogger::Instance->Initialize(_managedCore->GetPath(AIMP::SDK::AimpMessages::AimpCorePathType::AIMP_CORE_PATH_PROFILE), "aimp_dotnet.log");
	}

	_pluginState = gcnew AIMP::SDK::PluginStateSaver(_configurationManager);

	_pluginSettings = GetPluginSettings();
	_pluginSettings->PluginsCollection->PluginLoadEvent += gcnew AIMP::SDK::PluginLoadUnloadEvent(_managedExtension, &ManagedFunctionality::PluginLoadEventReaction);
	_pluginSettings->PluginsCollection->PluginUnloadEvent += gcnew AIMP::SDK::PluginLoadUnloadEvent(_managedExtension, &ManagedFunctionality::PluginUnloadEventReaction);
	_pluginState->Load(_pluginSettings);

	AIMP::SDK::InternalLogger::Instance->Write("Initialized");
	System::Diagnostics::Debug::WriteLine("END: Initialize DotNet plugin");

	return S_OK;
}

HRESULT WINAPI DotNetPlugin::Finalize()
{
	AIMP::SDK360::ManagedAimpCore::GetAimpCore()->UnregisterExtension((AIMP36SDK::IAIMPOptionsDialogFrame*)_frame);

	delete _frame;
	_frame = nullptr;

	_pluginSettings->PluginsCollection->UnloadAll();
	_pluginSettings->PluginsCollection->PluginLoadEvent -= gcnew AIMP::SDK::PluginLoadUnloadEvent(_managedExtension, &ManagedFunctionality::PluginLoadEventReaction);
	_pluginSettings->PluginsCollection->PluginUnloadEvent -= gcnew AIMP::SDK::PluginLoadUnloadEvent(_managedExtension, &ManagedFunctionality::PluginUnloadEventReaction);

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
	if (!ppvObj) {
		return E_POINTER;
	}

	if (IID_IUnknown == riid) {
		*ppvObj = this;
		AddRef();
		return S_OK;
	}

	if (riid == AIMP36SDK::IID_IAIMPOptionsDialogFrame)
	{
		*ppvObj = _frame;
		AddRef();
		_optionsLoaded = true;
		return S_OK;
	}

	if (riid == AIMP36SDK::IID_IAIMPExtensionPlaylistManagerListener)
	{
		*ppvObj = _listner;
		AddRef();
		return S_OK;
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

AIMP::SDK::PluginInfoCollection^ DotNetPlugin::GetAvailablePlugins()
{
	System::String^ path = System::Reflection::Assembly::GetExecutingAssembly()->Location;
	AIMP::SDK::CustomAssemblyResolver::Initialize(System::IO::Path::GetDirectoryName(path));
	return AIMP::SDK::PluginInfoLoader::LoadPlugins(System::IO::Path::GetDirectoryName(path));
}

AIMP::SDK::PluginSettings ^DotNetPlugin::GetPluginSettings()
{
	if (System::Object::ReferenceEquals(_pluginSettings, nullptr))
	{
		_pluginSettings = gcnew AIMP::SDK::PluginSettings();
		_pluginSettings->PluginsCollection = GetAvailablePlugins();
		_pluginSettings->IsDebugMode = _configurationManager->GetValueAsInt32("AimpDotNet\\Settings\\DebugMode") == 1;		
	}

	return _pluginSettings;
}

void DotNetPlugin::SavePluginOptions()
{
	_pluginState->Save(_pluginSettings);
}

HRESULT DotNetPlugin::LoadExtensions(AIMP36SDK::IAIMPCore* core)
{
	HRESULT r = S_OK;

	AIMP36SDK::IAIMPOptionsDialogFrame *frame = new OptionFrame(_managedCore, this);
	_frame = frame;
	r = core->RegisterExtension(AIMP36SDK::IID_IAIMPServiceOptionsDialog, (AIMP36SDK::IAIMPOptionsDialogFrame*)frame);

	AIMP36SDK::IAIMPExtensionPlaylistManagerListener *listner = new PlaylistManagerListener(this);
	_listner = listner;
	r = core->RegisterExtension(AIMP36SDK::IID_IAIMPServicePlaylistManager, (AIMP36SDK::IAIMPExtensionPlaylistManagerListener*)listner);

	AIMP36SDK::IAIMPExtensionPlayerHook *playerHook = new AimpExtensionPlayerHook(this);
	_playerHook = playerHook;
	r = core->RegisterExtension(AIMP36SDK::IID_IAIMPExtensionPlayerHook, (AIMP36SDK::IAIMPExtensionPlayerHook*)playerHook);

	return r;
}