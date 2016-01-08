#pragma once
#include "..\..\..\AIMPSDK\apiGUI.h"

class AimpUIMouseEvents : public IUnknownInterfaceImpl<IAIMPUIMouseEvents>
{
private:
    IUnknown *_base;

public:
    AimpUIMouseEvents(IUnknown *base)
    {
        _base = base;
    }

public:
    virtual void WINAPI OnMouseDoubleClick(IUnknown* Sender, TAIMPUIMouseButton Button, int X, int Y, WORD Modifiers)
    {
        System::Diagnostics::Debug::WriteLine("OnMouseDoubleClick");
    }

    virtual void WINAPI OnMouseDown(IUnknown* Sender, TAIMPUIMouseButton Button, int X, int Y, WORD Modifiers)
    {
        System::Diagnostics::Debug::WriteLine("OnMouseDown");
    }

    virtual void WINAPI OnMouseLeave(IUnknown* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnMouseLeave");
    }

    virtual void WINAPI OnMouseMove(IUnknown* Sender, int X, int Y, WORD Modifiers)
    {
        System::Diagnostics::Debug::WriteLine("OnMouseMove");
    }

    virtual void WINAPI OnMouseUp(IUnknown* Sender, TAIMPUIMouseButton Button, int X, int Y, WORD Modifiers)
    {
        System::Diagnostics::Debug::WriteLine("OnMouseUp");
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
