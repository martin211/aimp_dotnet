#include "..\..\Stdafx.h"
#include "AimpMenuItem.h"


namespace AIMP
{
    namespace SDK
    {
        void OnExecuteProxy(gcroot<AimpMenuItem^> sender)
        {
            sender->OnExecuteClick();
        }

        void OnBeforeShowProxy(gcroot<AimpMenuItem^> sender)
        {
            sender->OnBeforeShowClick();
        }

        void AimpMenuItem::OnExecute::add(EventHandler ^onEvent)
        {
            if (_onExecuteHandler == nullptr)
            {
                _onExecuteEvent = new MenuItemEvent();
                _onExecuteCallback = new EventCallback;
                *_onExecuteCallback = _onExecuteEvent->RegisterCallback(boost::bind(OnExecuteProxy, gcroot<AimpMenuItem^>(this)));
                _onExecuteHandler = (EventHandler^)Delegate::Combine(_onExecuteHandler, onEvent);
                InternalAimpObject->SetValueAsObject(AIMP_MENUITEM_PROPID_EVENT, _onExecuteEvent);
            }
        }

        void AimpMenuItem::OnExecute::remove(EventHandler ^onEvent)
        {
            if (_onExecuteHandler != nullptr)
            {
                _onExecuteHandler = (EventHandler^)Delegate::Remove(_onExecuteHandler, onEvent);
                _onExecuteEvent->UnregisterCallback(*_onExecuteCallback);
                delete _onExecuteCallback;
                delete _onExecuteEvent;
            }
        }

        void AimpMenuItem::OnExecute::raise(Object ^sender, EventArgs ^args)
        {
            if (_onExecuteHandler != nullptr)
            {
                _onExecuteHandler(sender, args);
            }
        }

        void AimpMenuItem::OnShow::add(EventHandler ^onEvent)
        {
            if (_onShowHandler == nullptr)
            {
                _onShowEvent = new MenuItemEvent();
                _onShowCallback = new EventCallback;
                *_onShowCallback = _onShowEvent->RegisterCallback(boost::bind(OnBeforeShowProxy, gcroot<AimpMenuItem^>(this)));
                _onShowHandler = (EventHandler^)Delegate::Combine(_onShowHandler, onEvent);
                InternalAimpObject->SetValueAsObject(AIMP_MENUITEM_PROPID_EVENT_ONSHOW, _onShowEvent);
            }
        }

        void AimpMenuItem::OnShow::remove(EventHandler ^onEvent)
        {
            if (_onShowHandler != nullptr)
            {
                _onShowHandler = (EventHandler^)Delegate::Remove(_onShowHandler, onEvent);
                _onShowEvent->UnregisterCallback(*_onShowCallback);
                delete _onShowCallback;
                delete _onShowEvent;
            }
        }

        void AimpMenuItem::OnShow::raise(Object ^sender, EventArgs ^args)
        {
            if (_onShowHandler != nullptr)
            {
                _onShowHandler(sender, args);
            }
        }
    }
}
