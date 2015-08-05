#pragma once

#include <gcroot.h>
#include "AIMP_SDK\aimp3_60_sdk.h"
#include "AIMP_SDK\IUnknownInterfaceImpl.h"
#include "AimpPlayer.h"
#include "DataConversion.h"
#include "ObjectHelper.h"
#include "InternalLogger.h"

namespace AIMP36SDK
{
	#include "AIMP_SDK\AIMP360\apiOptions.h"
}


private ref class ManagedFunctionality
{
public:
	ManagedFunctionality(AIMP36SDK::IAIMPCore* core)
	{
		_core = core;
	}

	/// <summary>
	/// Plugins the load event reaction. Initializes instance of the AIMPController for each plugin.
	/// </summary>
	/// <param name="sender">The sender.</param>
	void PluginLoadEventReaction(AIMP::SDK::PluginInformation^ sender)
	{
		// Each plugin should has his own managed core instance
		AIMP::SDK360::ManagedAimpCore ^managedCore = gcnew AIMP::SDK360::ManagedAimpCore(_core);
		AIMP::AimpPlayer<StaticSingleThreadAllocator>^ instance = nullptr;
		if (sender->PluginAppDomainInfo != nullptr)
		{
			AIMP::AIMPControllerInitializer^ controllerInitializer = (AIMP::AIMPControllerInitializer^)sender->PluginAppDomainInfo->CreateInstanceFromAndUnwrap(System::Reflection::Assembly::GetExecutingAssembly()->Location, AIMP::AIMPControllerInitializer::TypeName);
			instance = controllerInitializer->CreateWithStaticAllocator(managedCore, sender->LoadedPlugin->PluginId, sender->PluginAppDomainInfo->Id, true);
		}
		else
			instance = gcnew AIMP::AimpPlayer<StaticSingleThreadAllocator>(managedCore, sender->LoadedPlugin->PluginId, System::AppDomain::CurrentDomain->Id, false);

		sender->Initialize(instance);
	}

	void PluginUnloadEventReaction(AIMP::SDK::PluginInformation^ sender)
	{
		
	}
private:
	AIMP36SDK::IAIMPCore* _core;
};

class DotNetPlugin : public AIMP36SDK::IUnknownInterfaceImpl<AIMP36SDK::IAIMPPlugin>
{
public:
	DotNetPlugin();

	virtual PWCHAR WINAPI InfoGet(int index);

	virtual DWORD WINAPI InfoGetCategories();

	// Initialization / Finalization
	virtual HRESULT WINAPI Initialize(AIMP36SDK::IAIMPCore* core);

	virtual HRESULT WINAPI Finalize();

	virtual void WINAPI SystemNotification(int NotifyID, IUnknown* Data);

	virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObj);

	virtual ULONG WINAPI AddRef(void);

	virtual ULONG WINAPI Release(void);

	virtual AIMP::SDK::PluginInfoCollection^ GetAvailablePlugins();

	virtual AIMP::SDK::PluginSettings ^GetPluginSettings();

	virtual void SavePluginOptions();
private:
	HRESULT LoadExtensions(AIMP36SDK::IAIMPCore* core);

public:
	gcroot<AIMP::SDK360::ManagedAimpCore^> _managedCore;

private:
	bool inSetFormIntited;	
	bool _optionsLoaded;

	gcroot<ManagedFunctionality^> _managedExtension;
		
	//gcroot<AIMP::SDK::PluginInfoCollection^> inPluginCollection;
	gcroot<AIMP::SDK::PluginStateSaver^> _pluginState;
	gcroot<AIMP::SDK::PluginSettings^> _pluginSettings;
	gcroot<AIMP::ConfigurationManager^> _configurationManager;

	IAIMPServiceConfig *_configService;
	AIMP36SDK::IAIMPOptionsDialogFrame *_frame;
	AIMP36SDK::IAIMPExtensionPlaylistManagerListener *_listner;

	typedef IUnknownInterfaceImpl<IAIMPPlugin> Base;
};



class OptionFrame : public AIMP36SDK::IUnknownInterfaceImpl<AIMP36SDK::IAIMPOptionsDialogFrame>
{
private:
	gcroot<AIMP::SDK360::ManagedAimpCore^> _core;	
	gcroot<AIMP::SDK::UI::SettingsForm^> _settingForm;
	AIMP36SDK::IAIMPServiceOptionsDialog *_serviceOptionsDialog;

	HWND _optionsPage;
	ULONG _LinkCounter;
	DotNetPlugin* _main;

	boost::signal<void(void)> _eventChangedSignal;
	boost::signals::connection _eventCallback;
	boost::signal<void(void)>::slot_function_type _eventChangedSignalCB;
public:
	OptionFrame(AIMP::SDK360::ManagedAimpCore^ core, DotNetPlugin* main)
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

	virtual HRESULT WINAPI GetName(AIMP36SDK::IAIMPString **S)
	{	
		AIMP36SDK::IAIMPString **strObject = NULL;
		AIMP36SDK::IAIMPString *Str = AIMP::ObjectHelper::MakeAimpString(_core->GetAimpCore(), "DotNet Plugins");
		S = &Str;
		return S_OK;
	}

	virtual HWND WINAPI CreateFrame(HWND ParentWnd)
	{
		AIMP::SDK::Services::MUIManager::IMUIManager ^manager = gcnew AIMP::MIUManager(_core);
		_settingForm = gcnew AIMP::SDK::UI::SettingsForm(System::IntPtr(ParentWnd), manager);
		_serviceOptionsDialog = (AIMP36SDK::IAIMPServiceOptionsDialog*)_core->QueryInterface(IID_IAIMPServiceOptionsDialog);

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
			if (ID == AIMP36SDK::AIMP_SERVICE_OPTIONSDIALOG_NOTIFICATION_LOCALIZATION)
			{
				// TODO: Notify about new language.
				return;
			}
			else if (ID == AIMP36SDK::AIMP_SERVICE_OPTIONSDIALOG_NOTIFICATION_SAVE)
			{
				_main->SavePluginOptions();
			}
		}
	}

	void NotifyPlayer()
	{

	}
};

class PlaylistManagerListener : public AIMP36SDK::IUnknownInterfaceImpl<AIMP36SDK::IAIMPExtensionPlaylistManagerListener>
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

	virtual void WINAPI PlaylistActivated(AIMP36SDK::IAIMPPlaylist *playlist)
	{		
		_main->_managedCore->OnPlaylistActivated(playlist);
	}

	virtual void WINAPI PlaylistAdded(AIMP36SDK::IAIMPPlaylist *playlist)
	{
		_main->_managedCore->OnPlayListAdded(playlist);
	}

	virtual void WINAPI PlaylistRemoved(AIMP36SDK::IAIMPPlaylist *playlist)
	{
		_main->_managedCore->OnPlayListRemoved(playlist);
	}
};