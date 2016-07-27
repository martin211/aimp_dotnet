#pragma once

#include "AIMP400/apiPlugin.h"

template <typename T>
class IUnknownInterfaceImpl : public T
{
public:

    IUnknownInterfaceImpl()
    {
        _LinkCounter = 1;
    }

    virtual ~IUnknownInterfaceImpl() {}

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (riid == IID_IUnknown)
        {
            return S_OK;
        }
        return E_NOTIMPL;
    }

    virtual ULONG WINAPI AddRef(void)
    {
        _LinkCounter++;
        return _LinkCounter;
    }

    virtual ULONG WINAPI Release(void) {
        _LinkCounter--;

        if (_LinkCounter == 0) {
            delete this;
            return 0;
        }

        return _LinkCounter;
    }

private:
    ULONG _LinkCounter;
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
            return L"AIMP DotNet proxy";
        }
        case AIMP_PLUGIN_INFO_AUTHOR:
        {
            return L"Evgeniy Bogdan";
        }
        case AIMP_PLUGIN_INFO_SHORT_DESCRIPTION:
        {
            return L"AIMP DotNet proxy plugin";
        }
        case AIMP_PLUGIN_INFO_FULL_DESCRIPTION:
        {
            return L"AIMP DotNet proxy plugin";
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