#pragma once
#include "..\..\..\AIMPSDK\apiGUI.h"

class AimpUIWndProcEvents : public IAIMPUIWndProcEvents
{
private:
    IUnknown* _base;
    gcroot<AIMP::SDK::AimpUIWinControl^> _control;

public:
    AimpUIWndProcEvents(IUnknown *base)
    {
        _base = base;
    }

    void SetControl(AIMP::SDK::AimpUIWinControl ^control)
    {
        _control = control;
    }

    virtual BOOL WINAPI OnBeforeWndProc(DWORD Message, WPARAM ParamW, LPARAM ParamL, LRESULT* Result)
    {
        if (static_cast<AIMP::SDK::AimpUIWinControl^>(_control) != nullptr)
        {
            return _control->OnBeforeWndProcEvent(Message, ParamW, ParamL, Result);
        }

        return false;
    }

    virtual void WINAPI OnAfterWndProc(DWORD Message, WPARAM ParamW, LPARAM ParamL, LRESULT* Result)
    {
        if (static_cast<AIMP::SDK::AimpUIWinControl^>(_control) != nullptr)
        {
            _control->OnAfterWndProcEvent(Message, ParamW, ParamL, Result);
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
