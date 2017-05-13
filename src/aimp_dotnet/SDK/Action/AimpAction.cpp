/*
* AIMP DotNet SDK
*
* (C) 2017
* Mail: mail4evgeniy@gmail.com
* https://github.com/martin211/aimp_dotnet
*
*/
#include "Stdafx.h"
#include "AimpAction.h"
#include "../Action/AimpActionEvent.h"

using namespace AIMP::SDK;

AimpAction::AimpAction(IAIMPAction *action) : AimpObject(action)
{
}

String ^AimpAction::Id::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_ACTION_PROPID_ID);
}

void AimpAction::Id::set(String ^value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMP_ACTION_PROPID_ID, value);
}

String ^AimpAction::CustomData::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_ACTION_PROPID_CUSTOM);
}

void AimpAction::CustomData::set(String ^value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMP_ACTION_PROPID_CUSTOM, value);
}

String ^AimpAction::Name::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_ACTION_PROPID_NAME);
}

void AimpAction::Name::set(String ^value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMP_ACTION_PROPID_NAME, value);
}

String ^AimpAction::GroupName::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_ACTION_PROPID_GROUPNAME);
}

void AimpAction::GroupName::set(String ^value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMP_ACTION_PROPID_GROUPNAME, value);
}

bool AimpAction::Enabled::get()
{
    return PropertyListExtension::GetBool(InternalAimpObject, AIMP_ACTION_PROPID_ENABLED);
}

void AimpAction::Enabled::set(bool value)
{
    PropertyListExtension::SetBool(InternalAimpObject, AIMP_ACTION_PROPID_ENABLED, value);
}

int AimpAction::DefaultLocalHotKey::get()
{
    return PropertyListExtension::GetInt32(InternalAimpObject, AIMP_ACTION_PROPID_DEFAULTLOCALHOTKEY);
}

void AimpAction::DefaultLocalHotKey::set(int value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMP_ACTION_PROPID_DEFAULTLOCALHOTKEY, value);
}

int AimpAction::DefaultGlobalHotKey::get()
{
    return PropertyListExtension::GetInt32(InternalAimpObject, AIMP_ACTION_PROPID_DEFAULTGLOBALHOTKEY);
}

void AimpAction::DefaultGlobalHotKey::set(int value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMP_ACTION_PROPID_DEFAULTGLOBALHOTKEY, value);
}

int AimpAction::AlternativeGlobalHotKey::get()
{
    return PropertyListExtension::GetInt32(InternalAimpObject, AIMP_ACTION_PROPID_DEFAULTGLOBALHOTKEY2);
}

void AimpAction::AlternativeGlobalHotKey::set(int value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMP_ACTION_PROPID_DEFAULTGLOBALHOTKEY2, value);
}

void AimpAction::OnExecute::add(EventHandler ^onEvent)
{
    if (_onExecuteHandler == nullptr)
    {
        AIMP::SDK::AimpActionEventDelegate ^fp = gcnew AIMP::SDK::AimpActionEventDelegate(this->Execute);
        _executeHandler = GCHandle::Alloc(fp);
        IntPtr ip = Marshal::GetFunctionPointerForDelegate(fp);
        AIMP::SDK::AimpActionEventCallback callback = static_cast<AIMP::SDK::AimpActionEventCallback>(ip.ToPointer());
        _onExecuteEvent = new AimpActionEvent(this, callback);
        GC::Collect();
        _onExecuteHandler = (EventHandler^)Delegate::Combine(_onExecuteHandler, onEvent);
        InternalAimpObject->SetValueAsObject(AIMP_MENUITEM_PROPID_EVENT, _onExecuteEvent);
    }
}

void AimpAction::OnExecute::remove(EventHandler ^onEvent)
{
    if (_onExecuteHandler != nullptr)
    {
        _onExecuteHandler = (EventHandler^)Delegate::Remove(_onExecuteHandler, onEvent);
        InternalAimpObject->SetValueAsObject(AIMP_MENUITEM_PROPID_EVENT, NULL);
        _executeHandler.Free();
        _onExecuteEvent->Release();
        _onExecuteEvent = NULL;
    }
}

void AimpAction::OnExecute::raise(Object ^sender, EventArgs ^args)
{
    if (_onExecuteHandler != nullptr)
    {
        _onExecuteHandler(sender, args);
    }
}

AIMP::SDK::AimpAction::~AimpAction()
{
    _executeHandler.Free();
}
