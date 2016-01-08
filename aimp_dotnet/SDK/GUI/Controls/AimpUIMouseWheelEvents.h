#pragma once
#include "..\..\..\AIMPSDK\apiGUI.h"

class AimpUIMouseWheelEvents : IUnknownInterfaceImpl<IAIMPUIMouseWheelEvents>
{
private:
    IUnknown* _base;

public:
    AimpUIMouseWheelEvents(IUnknown *base)
    {
        _base = base;
    }

    virtual BOOL WINAPI OnMouseWheel(IUnknown* Sender, int WheelDelta, int X, int Y, WORD Modifiers)
    {
        System::Diagnostics::Debug::WriteLine("OnMouseWheel");
        return false;
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
