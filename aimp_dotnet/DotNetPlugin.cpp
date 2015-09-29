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
	_managedExtension = gcnew ManagedFunctionality(core, _managedCore);
	_configurationManager = gcnew AIMP::AimpConfigurationManager(_managedCore);

	LoadExtensions(core);

	if (_configurationManager->GetValueAsInt32("AimpDotNet\\Settings\\DebugMode") == 1)
	{
		String ^path;
		_managedCore->GetPath(AIMP::SDK::AimpMessages::AimpCorePathType::AIMP_CORE_PATH_PROFILE, path);
		AIMP::SDK::InternalLogger::Instance->Initialize(path, "aimp_dotnet.log");
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

	if (riid == AIMP36SDK::IID_IAIMPOptionsDialogFrame)
	{
		*ppvObj = _frame;
		AddRef();
		_optionsLoaded = true;
		System::Diagnostics::Debug::WriteLine("DotNetPlugin: QueryInterface: S_OK");
		return S_OK;
	}

	if (riid == AIMP36SDK::IID_IAIMPExtensionPlaylistManagerListener)
	{
		*ppvObj = _listner;
		AddRef();
		System::Diagnostics::Debug::WriteLine("DotNetPlugin: QueryInterface: S_OK");
		return S_OK;
	}

	if (riid == AIMP36SDK::IID_IAIMPExtensionPlayerHook)
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
	r = core->RegisterExtension(AIMP36SDK::IID_IAIMPServiceOptionsDialog, frame);

	AIMP36SDK::IAIMPExtensionPlaylistManagerListener *listner = new PlaylistManagerListener(this);
	_listner = listner;
	r = core->RegisterExtension(AIMP36SDK::IID_IAIMPServicePlaylistManager, listner);

	_playerHook = new AimpExtensionPlayerHook(this);	
	r = core->RegisterExtension(AIMP36SDK::IID_IAIMPServicePlayer, _playerHook);

	return r;
}