#pragma once
#include "AimpUIMouseEvents.h"

class AimpUIKeyboardEvents : public IAIMPUIKeyboardEvents
{
private:
    IUnknown *_main;
    gcroot<AIMP::SDK::AimpUIWinControl^> _control;

public:
    AimpUIKeyboardEvents(IUnknown *main)
    {
        _main = main;
    }

    void SetControl(AIMP::SDK::AimpUIWinControl ^control)
    {
        _control = control;
    }

    virtual void WINAPI OnEnter(IUnknown* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnEnter");
        if (static_cast<AIMP::SDK::AimpUIWinControl^>(_control) != nullptr)
        {
            _control->OnEnterEvent((IAIMPUIWinControl*)Sender);
        }
    }

    virtual void WINAPI OnExit(IUnknown* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnExit");
        if (static_cast<AIMP::SDK::AimpUIWinControl^>(_control) != nullptr)
        {
            _control->OnExitEvent((IAIMPUIWinControl*)Sender);
        }
    }

    virtual void WINAPI OnKeyDown(IUnknown* Sender, WORD* Key, WORD Modifiers)
    {
        System::Diagnostics::Debug::WriteLine("OnKeyDown");
        if (static_cast<AIMP::SDK::AimpUIWinControl^>(_control) != nullptr)
        {
            _control->OnKeyDownEvent((IAIMPUIWinControl*)Sender, Key, Modifiers);
        }
    }

    virtual void WINAPI OnKeyPress(IUnknown* Sender, WCHAR* Key)
    {
        System::Diagnostics::Debug::WriteLine("OnKeyPress");
        if (static_cast<AIMP::SDK::AimpUIWinControl^>(_control) != nullptr)
        {
            _control->OnKeyPressEvent((IAIMPUIWinControl*)Sender, Key);
        }
    }

    virtual void WINAPI OnKeyUp(IUnknown* Sender, WORD* Key, WORD Modifiers)
    {
        System::Diagnostics::Debug::WriteLine("OnKeyUp");
        if (static_cast<AIMP::SDK::AimpUIWinControl^>(_control) != nullptr)
        {
            _control->OnKeyUpEvent((IAIMPUIWinControl*)Sender, Key, Modifiers);
        }
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        return _main->QueryInterface(riid, ppvObject);
    }

    virtual ULONG WINAPI AddRef(void)
    {
        return _main->AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return _main->Release();
    }
};
