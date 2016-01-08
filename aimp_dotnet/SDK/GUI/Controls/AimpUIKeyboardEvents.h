#pragma once
#include "AimpUIMouseEvents.h"

class AimpUIKeyboardEvents : public IAIMPUIKeyboardEvents
{
private:
    IUnknown *_main;

public:
    AimpUIKeyboardEvents(IUnknown *main)
    {
        _main = main;
    }

    virtual void WINAPI OnEnter(IUnknown* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnEnter");
    }

    virtual void WINAPI OnExit(IUnknown* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnExit");
    }

    virtual void WINAPI OnKeyDown(IUnknown* Sender, WORD* Key, WORD Modifiers)
    {
        System::Diagnostics::Debug::WriteLine("OnKeyDown");
    }

    virtual void WINAPI OnKeyPress(IUnknown* Sender, WCHAR* Key)
    {
        System::Diagnostics::Debug::WriteLine("OnKeyPress");
    }

    virtual void WINAPI OnKeyUp(IUnknown* Sender, WORD* Key, WORD Modifiers)
    {
        System::Diagnostics::Debug::WriteLine("OnKeyUp");
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
