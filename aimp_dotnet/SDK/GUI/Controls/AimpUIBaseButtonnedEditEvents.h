#pragma once
#include "..\..\..\AIMPSDK\apiGUI.h"
#include "AimpUIChangeEvents.h"

class AimpUIBaseButtonnedEditEvents : public IUnknownInterfaceImpl<IAIMPUIChangeEvents>
{
private:
    AimpUIChangeEvents *_changedEvents;

public:
    typedef IUnknownInterfaceImpl<IAIMPUIChangeEvents> Base;

    AimpUIBaseButtonnedEditEvents()
    {
        //_changedEvents = new AimpUIChangeEvents(this);
    }

    virtual void OnChanged(IUnknown* Sender)
    {
        
    };

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (riid == IID_IUnknown)
        {
            return S_OK;
        }

        if (riid == IID_IAIMPUIChangeEvents)
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
