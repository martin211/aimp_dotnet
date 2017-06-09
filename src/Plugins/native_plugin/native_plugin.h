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

        IUnknown* demo = new AimpExtensionDataStorage(Core);
        Core->RegisterExtension(IID_IAIMPServiceMusicLibrary, demo);

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