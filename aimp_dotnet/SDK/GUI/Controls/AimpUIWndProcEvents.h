#pragma once
#include "..\..\..\AIMPSDK\apiGUI.h"

class AimpUIWndProcEvents : public IAIMPUIWndProcEvents
{
private:
    IUnknown* _base;
public:
    AimpUIWndProcEvents(IUnknown *base)
    {
        _base = base;
    }

    virtual BOOL WINAPI OnBeforeWndProc(DWORD Message, WPARAM ParamW, LPARAM ParamL, LRESULT* Result)
    {
        //System::Diagnostics::Debug::WriteLine("OnBeforeWndProc");
        return false;
    }

    virtual void WINAPI OnAfterWndProc(DWORD Message, WPARAM ParamW, LPARAM ParamL, LRESULT* Result)
    {
        //System::Diagnostics::Debug::WriteLine("OnAfterWndProc");
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
