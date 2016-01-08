#pragma once
#include "..\..\..\AIMPSDK\apiGUI.h"

class AimpUIPopupMenuEvents : IUnknownInterfaceImpl<IAIMPUIPopupMenuEvents>
{
private:
    IUnknown *_base;
public:
    AimpUIPopupMenuEvents(IUnknown *base)
    {
        _base = base;
    }

    virtual BOOL WINAPI OnContextPopup(IUnknown* Sender, int X, int Y)
    {
        //System::Diagnostics::Debug::WriteLine("OnContextPopup");
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
