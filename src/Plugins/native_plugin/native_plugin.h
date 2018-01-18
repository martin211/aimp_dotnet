#pragma once
#include <Windows.h>
#include <iostream>
#include <sstream>

#include "AIMP400/apiPlugin.h"
#include "AIMP400/apiThreading.h"
#include "TDemoExplorerViewDataStorage.h"
#include "IUnknownInterfaceImpl.h"


#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

class AimpTask : public IUnknownInterfaceImpl<IAIMPTask>
{
public:
    typedef IUnknownInterfaceImpl<IAIMPTask> Base;

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (!ppvObject)
        {
            return E_POINTER;
        }

        if (riid == IID_IAIMPTask) {
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

    virtual void WINAPI Execute(IAIMPTaskOwner* Owner)
    {
        DBOUT("Tasl execute");
    }
};

class AIMPMessageHook : public IUnknownInterfaceImpl<IAIMPMessageHook>
{
public:
    explicit AIMPMessageHook(IAIMPCore* core)
    {
        _core = core;
    }

    virtual void WINAPI CoreMessage(DWORD AMessage, int AParam1, void *AParam2, HRESULT *AResult)
    {
        if (AMessage == AIMP_MSG_EVENT_PLAYER_STATE && AParam1 == 2)
        {
            IAIMPServicePlayer *service = nullptr;
            _core->QueryInterface(IID_IAIMPServicePlayer, (void**)&service);
            if (service != nullptr)
            {
                IAIMPFileInfo *fi = nullptr;
                if (service->GetInfo(&fi) == S_OK && fi != nullptr)
                {
                    IAIMPImageContainer* container = nullptr;
                    HRESULT r = fi->GetValueAsObject(AIMP_FILEINFO_PROPID_ALBUMART, IID_IAIMPImageContainer, (void**)&container);
                    CheckResult(r);
                    if (r != S_OK || container == nullptr)
                    {
                        IAIMPImage *image = nullptr;
                        r = fi->GetValueAsObject(AIMP_FILEINFO_PROPID_ALBUMART, IID_IAIMPImage, (void**)&image);
                        CheckResult(r);

                        if (image != nullptr)
                        {
                            DBOUT("not null");
                        }
                    }
                }
            }
        }
    }

    void CheckResult(HRESULT r)
    {
        switch (r)
        {
        case E_ACCESSDENIED:
            DBOUT("E_ACCESSDENIED");
            break;
        case E_HANDLE:
            DBOUT("E_HANDLE");
            break;
        case E_INVALIDARG:
            DBOUT("E_INVALIDARG");
            break;
        case E_NOTIMPL:
            DBOUT("E_NOTIMPL");
            break;
        case E_UNEXPECTED:
            DBOUT("E_UNEXPECTED");
            break;
        case E_FAIL:
            DBOUT("E_FAIL");
            break;
        case S_OK:
            DBOUT("S_OK");
            break;
        }
    }

private:
    IAIMPCore *_core;
};

class NativePlugin : public IUnknownInterfaceImpl<IAIMPPlugin>
{
public:
    virtual PWCHAR WINAPI InfoGet(int Index)
    {
        switch (Index)
        {
        case AIMP_PLUGIN_INFO_NAME:
        {
            return L"AIMP native plugin";
        }
        case AIMP_PLUGIN_INFO_AUTHOR:
        {
            return L"Evgeniy Bogdan";
        }
        case AIMP_PLUGIN_INFO_SHORT_DESCRIPTION:
        {
            return L"AIMP native plugin";
        }
        case AIMP_PLUGIN_INFO_FULL_DESCRIPTION:
        {
            return L"AIMP native plugin";
        }
        }

        return NULL;
    }

    virtual DWORD WINAPI InfoGetCategories()
    {
        return AIMP_PLUGIN_CATEGORY_ADDONS;
    }

    // Initialization / Finalization
    virtual HRESULT WINAPI Initialize(IAIMPCore* Core)
    {
        //IAIMPServiceThreadPool *service;

        //HRESULT res = Core->QueryInterface(IID_IAIMPServiceThreadPool, (void**)&service);
        //DBOUT("QueryInterface result " << res);

        //IUnknown* demo = new AimpExtensionDataStorage(Core);
        //Core->RegisterExtension(IID_IAIMPServiceMusicLibrary, demo);

        IAIMPServiceMessageDispatcher* aimp_service_message_dispatcher;
        Core->QueryInterface(IID_IAIMPServiceMessageDispatcher, reinterpret_cast<void**>(&aimp_service_message_dispatcher));
        AIMPMessageHook* hook = new AIMPMessageHook(Core);
        aimp_service_message_dispatcher->Hook(hook);



        return S_OK;
    }

    virtual HRESULT WINAPI Finalize()
    {
        return S_OK;
    }

    // System Notifications
    virtual void WINAPI SystemNotification(int NotifyID, IUnknown* Data)
    {
        
    }
};