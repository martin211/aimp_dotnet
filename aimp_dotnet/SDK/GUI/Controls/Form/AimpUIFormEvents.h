#pragma once
#include "..\..\..\..\AIMPSDK\apiGUI.h"
#include "..\AimpUIKeyboardEvents.h"
#include "..\AimpUIMouseWheelEvents.h"
//#include "..\AimpUIPopupMenuEvents.h"
#include "..\AimpUIPlacementEvents.h"
#include "..\AimpUIWndProcEvents.h"
#include <gcroot.h>


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
    gcroot<AIMP::SDK::AimpUIForm^> _control;

public:
    typedef IUnknownInterfaceImpl<IAIMPUIFormEvents> Base;

public:
    AimpUIFormEvents()
    {
        _mouseEvents = new AimpUIMouseEvents(this);
        _keyboardEvents = new AimpUIKeyboardEvents(this);
        _mouseWheelEvents = new AimpUIMouseWheelEvents(this);
        //_popupMenuEvents = new AimpUIPopupMenuEvents(static_cast<AimpUIFormEvents::Base*>(this));
        _placementEvents = new AimpUIPlacementEvents(this);
        _wndProcEvents = new AimpUIWndProcEvents(this);
    }

    virtual void SetFormControl(AIMP::SDK::AimpUIForm ^control)
    {
        System::Diagnostics::Debug::WriteLine("SetFormControl");
        _control = control;

        _mouseEvents->SetControl(control);
        _keyboardEvents->SetControl(control);
        _mouseWheelEvents->SetControl(control);
        _placementEvents->SetControl(control);
        _wndProcEvents->SetControl(control);
    }

    virtual void WINAPI OnActivated(IAIMPUIForm* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnActivated");
        if (static_cast<AIMP::SDK::AimpUIForm^>(_control) != nullptr)
        {
            _control->OnActivatedEvent(Sender);
        }
    }

    virtual void WINAPI OnDeactivated(IAIMPUIForm* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnDeactivated");
        if (static_cast<AIMP::SDK::AimpUIForm^>(_control) != nullptr)
        {
            _control->OnDeactivatedEvent(Sender);
        }
    }

    virtual void WINAPI OnCreated(IAIMPUIForm* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnCreated");
        if (static_cast<AIMP::SDK::AimpUIForm^>(_control) != nullptr)
        {
            _control->OnCreatedEvent(Sender);
        }
    }

    virtual void WINAPI OnDestroyed(IAIMPUIForm* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnDestroyed");
        if (static_cast<AIMP::SDK::AimpUIForm^>(_control) != nullptr)
        {
            _control->OnDestroyedEvent(Sender);
        }
    }

    virtual void WINAPI OnCloseQuery(IAIMPUIForm* Sender, BOOL* CanClose)
    {
        System::Diagnostics::Debug::WriteLine("OnCloseQuery");
        if (static_cast<AIMP::SDK::AimpUIForm^>(_control) != nullptr)
        {
            _control->OnCloseQueryEvent(Sender, CanClose);
        }
    }

    virtual void WINAPI OnLocalize(IAIMPUIForm* Sender)
    {
        System::Diagnostics::Debug::WriteLine("OnLocalize");
        if (static_cast<AIMP::SDK::AimpUIForm^>(_control) != nullptr)
        {
            _control->OnLocalizeEvent(Sender);
        }
    }

    virtual void WINAPI OnShortCut(IAIMPUIForm* Sender, WORD Key, WORD Modifiers, BOOL* Handled)
    {
        System::Diagnostics::Debug::WriteLine("OnShortCut");
        if (static_cast<AIMP::SDK::AimpUIForm^>(_control) != nullptr)
        {
            *Handled = _control->OnShortCutEvent(Sender, Key, Modifiers, Handled);
        }
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
