#pragma once
#include "..\..\..\AIMPSDK\apiGUI.h"

class AimpUIPlacementEvents : IUnknownInterfaceImpl<IAIMPUIPlacementEvents>
{
private:
    IUnknown* _base;

public:
    AimpUIPlacementEvents(IUnknown *base)
    {
        _base = base;
    }

    virtual void WINAPI OnBoundsChanged(IUnknown* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnBoundsChanged");
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        return _base->QueryInterface(riid, ppvObject);
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
