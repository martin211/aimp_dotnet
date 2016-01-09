#pragma once
#include "..\..\..\AIMPSDK\apiGUI.h"

class AimpUIMouseEvents : public IUnknownInterfaceImpl<IAIMPUIMouseEvents>
{
private:
    IUnknown *_base;
    gcroot<AIMP::SDK::AimpUIControl^> _control;

public:
    AimpUIMouseEvents(IUnknown *base)
    {
        _base = base;
    }

public:
    void SetControl(AIMP::SDK::AimpUIControl ^control)
    {
        _control = control;
    }

    virtual void WINAPI OnMouseDoubleClick(IUnknown* Sender, TAIMPUIMouseButton Button, int X, int Y, WORD Modifiers)
    {
        System::Diagnostics::Debug::WriteLine("OnMouseDoubleClick");
        if (static_cast<AIMP::SDK::GUI::Controls::IAimpUIControl^>(_control) != nullptr)
        {
            _control->OnMouseDoubleClickEvent((IAIMPUIControl*)Sender, Button, X, Y, Modifiers);
        }
    }

    virtual void WINAPI OnMouseDown(IUnknown* Sender, TAIMPUIMouseButton Button, int X, int Y, WORD Modifiers)
    {
        System::Diagnostics::Debug::WriteLine("OnMouseDown");
        if (static_cast<AIMP::SDK::GUI::Controls::IAimpUIControl^>(_control) != nullptr)
        {
            _control->OnMouseDownEvent((IAIMPUIControl*)Sender, Button, X, Y, Modifiers);
        }
    }

    virtual void WINAPI OnMouseLeave(IUnknown* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnMouseLeave");
        if (static_cast<AIMP::SDK::GUI::Controls::IAimpUIControl^>(_control) != nullptr)
        {
            _control->OnMouseLeaveEvent((IAIMPUIControl*)Sender);
        }
    }

    virtual void WINAPI OnMouseMove(IUnknown* Sender, int X, int Y, WORD Modifiers)
    {
        System::Diagnostics::Debug::WriteLine("OnMouseMove");
        if (static_cast<AIMP::SDK::AimpUIControl^>(_control) != nullptr)
        {
            _control->OnMouseMoveEvent((IAIMPUIControl*)Sender, X, Y, Modifiers);
        }
    }

    virtual void WINAPI OnMouseUp(IUnknown* Sender, TAIMPUIMouseButton Button, int X, int Y, WORD Modifiers)
    {
        System::Diagnostics::Debug::WriteLine("OnMouseUp");
        if (static_cast<AIMP::SDK::AimpUIControl^>(_control) != nullptr)
        {
            _control->OnMouseUpEvent((IAIMPUIControl*)Sender, Button, X, Y, Modifiers);
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
