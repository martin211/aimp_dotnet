#pragma once
#include "..\..\..\..\AIMPSDK\apiGUI.h"
#include "..\AimpUIKeyboardEvents.h"
#include "..\AimpUIMouseWheelEvents.h"
//#include "..\AimpUIPopupMenuEvents.h"
#include "..\AimpUIPlacementEvents.h"
#include "..\AimpUIWndProcEvents.h"


class AimpUIFormEvents : 
    public IUnknownInterfaceImpl<IAIMPUIFormEvents>
{
private:
    AimpUIMouseEvents *_mouseEvents;
    AimpUIKeyboardEvents *_keyboardEvents;
    AimpUIMouseWheelEvents *_mouseWheelEvents;
    //AimpUIPopupMenuEvents *_popupMenuEvents;
    AimpUIPlacementEvents *_placementEvents;
    AimpUIWndProcEvents *_wndProcEvents;

public:
    typedef IUnknownInterfaceImpl<IAIMPUIFormEvents> Base;

public:
    AimpUIFormEvents()
    {
        _mouseEvents = new AimpUIMouseEvents(static_cast<AimpUIFormEvents::Base*>(this));
        _keyboardEvents = new AimpUIKeyboardEvents(static_cast<AimpUIFormEvents::Base*>(this));
        _mouseWheelEvents = new AimpUIMouseWheelEvents(static_cast<AimpUIFormEvents::Base*>(this));
        //_popupMenuEvents = new AimpUIPopupMenuEvents(static_cast<AimpUIFormEvents::Base*>(this));
        _placementEvents = new AimpUIPlacementEvents(static_cast<AimpUIFormEvents::Base*>(this));
        _wndProcEvents = new AimpUIWndProcEvents(static_cast<AimpUIFormEvents::Base*>(this));
    }

    virtual void WINAPI OnActivated(IAIMPUIForm* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnActivated");
    }

    virtual void WINAPI OnDeactivated(IAIMPUIForm* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnDeactivated");
    }

    virtual void WINAPI OnCreated(IAIMPUIForm* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnCreated");
    }

    virtual void WINAPI OnDestroyed(IAIMPUIForm* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnDestroyed");
    }

    virtual void WINAPI OnCloseQuery(IAIMPUIForm* Sende, BOOL* CanClose)
    {
        System::Diagnostics::Debug::WriteLine("OnCloseQuery");
    }

    virtual void WINAPI OnLocalize(IAIMPUIForm* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnLocalize");
    }

    virtual void WINAPI OnShortCut(IAIMPUIForm* Sender, WORD Key, WORD Modifiers, BOOL* Handled)
    {
        System::Diagnostics::Debug::WriteLine("OnShortCut");
    }

    virtual void WINAPI OnBoundsChanged(IUnknown* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnBoundsChanged");
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        HRESULT result = Base::QueryInterface(riid, ppvObject);

        if (result == S_OK)
        {
            return S_OK;
        }

        if (riid == IID_IAIMPUIFormEvents) 
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        if (riid == IID_IAIMPUIKeyboardEvents) {
            *ppvObject = _keyboardEvents;
            AddRef();
            return S_OK;
        }

        if (riid == IID_IAIMPUIMouseEvents) {
            *ppvObject = _mouseEvents;
            AddRef();
            return S_OK;
        }

        if (riid == IID_IAIMPUIMouseWheelEvents) {
            *ppvObject = _mouseWheelEvents;
            AddRef();
            return S_OK;
        }

        if (riid == IID_IAIMPUIPlacementEvents) {
            *ppvObject = _placementEvents;
            AddRef();
            return S_OK;
        }

        if (riid == IID_IAIMPUIWndProcEvents)
        {
            *ppvObject = _wndProcEvents;
            AddRef();
            return S_OK;
        }

       //if (riid == IID_IAIMPUIPopupMenuEvents) {
       //     *ppvObject = _popupMenuEvents;
       //     AddRef();
       //     return S_OK;
       // }

        return E_NOINTERFACE;
    }

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }
};
