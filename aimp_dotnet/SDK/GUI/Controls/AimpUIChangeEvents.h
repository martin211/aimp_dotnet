#pragma once
#include "..\..\..\AIMPSDK\apiGUI.h"

class AimpUIChangeEvents : public IUnknownInterfaceImpl<IAIMPUIChangeEvents>
{
private:
    IUnknown *_base;
    //gcroot<AIMP::SDK::AimpUIControl^> _control;

public:
    AimpUIChangeEvents(IUnknown *base)
    {
        _base = base;
    }

    virtual void OnChanged(IUnknown* Sender)
    {
        
    }

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
        return _base->AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return _base->Release();
    }
};
