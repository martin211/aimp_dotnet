#pragma once
#include "..\..\..\AIMPSDK\apiGUI.h"

class AimpUIPlacementEvents : IUnknownInterfaceImpl<IAIMPUIPlacementEvents>
{
private:
    IUnknown* _base;
    gcroot<AIMP::SDK::AimpUIControl^> _control;

public:
    AimpUIPlacementEvents(IUnknown *base)
    {
        _base = base;
    }

    void SetControl(AIMP::SDK::AimpUIControl ^control)
    {
        _control = control;
    }

    virtual void WINAPI OnBoundsChanged(IUnknown* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnBoundsChanged");
        if (static_cast<AIMP::SDK::AimpUIControl^>(_control) != nullptr)
        {
            _control->OnBoundsChangedEvent((IAIMPUIControl*)Sender);
        }
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
