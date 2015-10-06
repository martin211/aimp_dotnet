#pragma once

#include <gcroot.h>
#include "AimpPlayer.h"
#include "ObjectHelper.h"
#include "InternalLogger.h"

private ref class ManagedFunctionality
{
public:
	ManagedFunctionality(IAIMPCore* core, ManagedAimpCore ^managedCore)
	{
		_core = core;
		_managedCore = managedCore;
	}

	/// <summary>
	/// Plugins the load event reaction. Initializes instance of the AIMPController for each plugin.
	/// </summary>
	/// <param name="sender">The sender.</param>
	void PluginLoadEventReaction(AIMP::SDK::PluginInformation^ sender)
	{
		// Each plugin should has his own managed core instance
		//AIMP::SDK360::ManagedAimpCore ^managedCore = gcnew AIMP::SDK360::ManagedAimpCore(_core);
		AIMP::AimpPlayer<StaticSingleThreadAllocator>^ instance = nullptr;
		if (sender->PluginAppDomainInfo != nullptr)
		{
			AIMP::AIMPControllerInitializer^ controllerInitializer = (AIMP::AIMPControllerInitializer^)sender->PluginAppDomainInfo->CreateInstanceFromAndUnwrap(System::Reflection::Assembly::GetExecutingAssembly()->Location, AIMP::AIMPControllerInitializer::TypeName);
			instance = controllerInitializer->CreateWithStaticAllocator(_managedCore, sender->LoadedPlugin->PluginId, sender->PluginAppDomainInfo->Id, true);
		}
		else
			instance = gcnew AIMP::AimpPlayer<StaticSingleThreadAllocator>(_managedCore, sender->LoadedPlugin->PluginId, System::AppDomain::CurrentDomain->Id, false);

		sender->Initialize(instance);
	}

	void PluginUnloadEventReaction(AIMP::SDK::PluginInformation^ sender)
	{
		
	}
private:
	IAIMPCore* _core;
	ManagedAimpCore ^_managedCore;
};

class DotNetPlugin : public IUnknownInterfaceImpl<IAIMPPlugin>
{
public:
	DotNetPlugin();

	virtual PWCHAR WINAPI InfoGet(int index);

	virtual DWORD WINAPI InfoGetCategories();

	// Initialization / Finalization
	virtual HRESULT WINAPI Initialize(IAIMPCore* core);

	virtual HRESULT WINAPI Finalize();

	virtual void WINAPI SystemNotification(int NotifyID, IUnknown* Data);

	virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObj);

	virtual ULONG WINAPI AddRef(void);

	virtual ULONG WINAPI Release(void);

	virtual AIMP::SDK::PluginInfoCollection^ GetAvailablePlugins();

	virtual AIMP::SDK::PluginSettings ^GetPluginSettings();

	virtual void SavePluginOptions();
private:
	HRESULT LoadExtensions(IAIMPCore* core);

public:
	gcroot<ManagedAimpCore^> _managedCore;

private:
	bool inSetFormIntited;
	bool _optionsLoaded;
	gcroot<ManagedFunctionality^> _managedExtension;
	//gcroot<AIMP::SDK::PluginInfoCollection^> inPluginCollection;
	gcroot<AIMP::SDK::PluginStateSaver^> _pluginState;
	gcroot<AIMP::SDK::PluginSettings^> _pluginSettings;
	gcroot<AIMP::AimpConfigurationManager^> _configurationManager;
	IAIMPServiceConfig *_configService;
	IAIMPOptionsDialogFrame *_frame;
	IAIMPExtensionPlaylistManagerListener *_listner;
	IAIMPExtensionPlayerHook *_playerHook;
	typedef IUnknownInterfaceImpl<IAIMPPlugin> Base;
};



class OptionFrame : public IUnknownInterfaceImpl<IAIMPOptionsDialogFrame>
{
private:
	gcroot<ManagedAimpCore^> _core;	
	gcroot<AIMP::SDK::UI::SettingsForm^> _settingForm;
	IAIMPServiceOptionsDialog *_serviceOptionsDialog;

	HWND _optionsPage;
	ULONG _LinkCounter;
	DotNetPlugin* _main;

	boost::signal<void(void)> _eventChangedSignal;
	boost::signals::connection _eventCallback;
	boost::signal<void(void)>::slot_function_type _eventChangedSignalCB;
public:
	OptionFrame(ManagedAimpCore^ core, DotNetPlugin* main)
	{
		_core = core;
		_LinkCounter = 1;
		_main = main;
	}

	virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
	{
		return _main->QueryInterface(riid, ppvObject);
	}

	virtual ULONG WINAPI AddRef(void)
	{
		return _main->AddRef();
	}

	virtual ULONG WINAPI Release(void)
	{
		return _main->Release();
	}

	virtual HRESULT WINAPI GetName(IAIMPString **S)
	{
		IAIMPString *Str = AIMP::ObjectHelper::MakeAimpString(_core->GetAimpCore(), "DotNet Plugins");
		*S = Str;
		return S_OK;
	}

	virtual HWND WINAPI CreateFrame(HWND ParentWnd)
	{
		AIMP::SDK::Services::MUIManager::IAimpMUIManager ^manager = gcnew AIMP::AimpMIUManager(_core);
		_settingForm = gcnew AIMP::SDK::UI::SettingsForm(System::IntPtr(ParentWnd), manager);
		_serviceOptionsDialog = (IAIMPServiceOptionsDialog*)_core->QueryInterface(IID_IAIMPServiceOptionsDialog);

		System::IntPtr Handle = _settingForm->Handle;

		gcroot<AIMP::SDK::PluginSettings^> settings = _main->GetPluginSettings();

		_settingForm->Settings = settings;
		_settingForm->ReloadSettings();
		_settingForm->Show();

		return static_cast<HWND>(Handle.ToPointer());
	}

	virtual void WINAPI DestroyFrame()
	{
		_main->SavePluginOptions();
		_settingForm->Close();
		_settingForm = NULL;
	}

	virtual void WINAPI Notification(int ID)
	{
		if (_optionsPage != NULL)
		{
			if (ID == AIMP_SERVICE_OPTIONSDIALOG_NOTIFICATION_LOCALIZATION)
			{
				// TODO: Notify about new language.
				return;
			}
			else if (ID == AIMP_SERVICE_OPTIONSDIALOG_NOTIFICATION_SAVE)
			{
				_main->SavePluginOptions();
			}
		}
	}

	void NotifyPlayer()
	{

	}
};

class PlaylistManagerListener : public IUnknownInterfaceImpl<IAIMPExtensionPlaylistManagerListener>
{
private:
		DotNetPlugin* _main;
public:
	PlaylistManagerListener(DotNetPlugin* main)
	{
		_main = main;
	}

	virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
	{
		return _main->QueryInterface(riid, ppvObject);
	}

	virtual ULONG WINAPI AddRef(void)
	{
		return _main->AddRef();
	}

	virtual ULONG WINAPI Release(void)
	{
		return _main->Release();
	}

	virtual void WINAPI PlaylistActivated(IAIMPPlaylist *playlist)
	{
		if (playlist != nullptr)
		{
			_main->_managedCore->OnPlaylistActivated(playlist);
		}
	}

	virtual void WINAPI PlaylistAdded(IAIMPPlaylist *playlist)
	{
		if (playlist != nullptr)
		{
			_main->_managedCore->OnPlayListAdded(playlist);
		}
	}

	virtual void WINAPI PlaylistRemoved(IAIMPPlaylist *playlist)
	{
		if (playlist != nullptr)
		{
			_main->_managedCore->OnPlayListRemoved(playlist);
		}
	}
};

class AimpExtensionPlayerHook : public IUnknownInterfaceImpl<IAIMPExtensionPlayerHook>
{
private:
	DotNetPlugin* _main;
public:
	AimpExtensionPlayerHook(DotNetPlugin* main)
	{
		_main = main;
	}

	virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
	{
		System::Diagnostics::Debug::WriteLine("PlaylistManagerListener2: QueryInterface");
		return _main->QueryInterface(riid, ppvObject);
	}

	virtual ULONG WINAPI AddRef(void)
	{
		return _main->AddRef();
	}

	virtual ULONG WINAPI Release(void)
	{
		return _main->Release();
	}

	virtual HRESULT WINAPI OnCheckURL(IAIMPString* URL, BOOL *Handled)
	{
		String ^url = AIMP::ObjectHelper::GetString(URL);
		if (_main->_managedCore->OnCheckUrl(url))
		{
			pin_ptr<const WCHAR> strData = PtrToStringChars(url);
			URL->SetData((PWCHAR)strData, url->Length);
			*Handled = TRUE;
		}
		else
		{
			*Handled = FALSE;
		}

		return S_OK;
	}
};