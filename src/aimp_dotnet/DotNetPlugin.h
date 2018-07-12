// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once

#include <gcroot.h>
#include "IUnknownInterfaceImpl.h"
#include "SDK\AimpPlayer.h"

[System::Serializable]
public ref class ManagedFunctionality
{
public:
    ManagedFunctionality(IAIMPCore* core)
    {
        _core = core;
        _managedCore = nullptr;
    }

    ~ManagedFunctionality()
    {
        delete _managedCore;
    }

    void PluginLoadEventReaction(AIMP::SDK::PluginInformation^ sender)
    {
        _managedCore = gcnew AIMP::SDK::ManagedAimpCore(_core);

        AIMP::AimpPlayer^ instance = nullptr;
        if (sender->PluginAppDomainInfo != nullptr)
        {
            instance = gcnew AIMP::AimpPlayer(_managedCore, sender->LoadedPlugin->PluginId, sender->PluginAppDomainInfo->Id, true);
        }
        else
        {
            instance = gcnew AIMP::AimpPlayer(_managedCore, sender->LoadedPlugin->PluginId, System::AppDomain::CurrentDomain->Id, false);
        }

        sender->Initialize(instance);
    }

    void PluginUnloadEventReaction(AIMP::SDK::PluginInformation^ sender)
    {

    }
private:
    IAIMPCore* _core;
    AIMP::SDK::ManagedAimpCore ^_managedCore;
};

class AimpExternalSettingsDialog : public IUnknownInterfaceImpl<IAIMPExternalSettingsDialog>
{
private:
    gcroot<AIMP::SDK::IAimpExternalSettingsDialog^> _instance;
    typedef IUnknownInterfaceImpl<IAIMPExternalSettingsDialog> Base;
public:
    AimpExternalSettingsDialog(gcroot<AIMP::SDK::IAimpExternalSettingsDialog^> instance)
    {
        _instance = instance;
    }

    virtual void WINAPI Show(HWND ParentWindow)
    {
        _instance->Show(IntPtr(ParentWindow));
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        *ppvObject = NULL;
        if (riid == IID_IAIMPExternalSettingsDialog)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }
};

/// <summary>
/// 
/// </summary>
class DotNetPlugin : public IUnknownInterfaceImpl<IAIMPPlugin>, IAIMPExternalSettingsDialog
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

    virtual void WINAPI Show(HWND ParentWindow);

private:
    HRESULT LoadExtensions(IAIMPCore* core);

private:
    bool inSetFormIntited;
    bool _optionsLoaded;
    gcroot<ManagedFunctionality^> _managedExtension;
    gcroot<AIMP::SDK::AimpDotNetPlugin^> _dotNetPlugin;
    IAIMPServiceConfig *_configService = NULL;
    IAIMPExtensionPlayerHook *_playerHook = NULL;
    AimpExternalSettingsDialog *_externalSettingsDialog = NULL;
    typedef IUnknownInterfaceImpl<IAIMPPlugin> Base;
};
