// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpAction.h"
#include "../Action/AimpActionEvent.h"

using namespace AIMP::SDK;
using namespace Actions;
using namespace Actions::Objects;

AimpAction::AimpAction(IAIMPAction* action) : AimpObject(action) {
    _onExecuteEvent = nullptr;
}

String^ AimpAction::Id::get() {
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_ACTION_PROPID_ID);
}

void AimpAction::Id::set(String^ value) {
    PropertyListExtension::SetString(InternalAimpObject, AIMP_ACTION_PROPID_ID, value);
}

String^ AimpAction::CustomData::get() {
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_ACTION_PROPID_CUSTOM);
}

void AimpAction::CustomData::set(String^ value) {
    PropertyListExtension::SetString(InternalAimpObject, AIMP_ACTION_PROPID_CUSTOM, value);
}

String^ AimpAction::Name::get() {
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_ACTION_PROPID_NAME);
}

void AimpAction::Name::set(String^ value) {
    PropertyListExtension::SetString(InternalAimpObject, AIMP_ACTION_PROPID_NAME, value);
}

String^ AimpAction::GroupName::get() {
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_ACTION_PROPID_GROUPNAME);
}

void AimpAction::GroupName::set(String^ value) {
    PropertyListExtension::SetString(InternalAimpObject, AIMP_ACTION_PROPID_GROUPNAME, value);
}

bool AimpAction::Enabled::get() {
    int val;
    InternalAimpObject->GetValueAsInt32(AIMP_ACTION_PROPID_ENABLED, &val);
    return val != 0;
}

void AimpAction::Enabled::set(bool value) {
    PropertyListExtension::SetBool(InternalAimpObject, AIMP_ACTION_PROPID_ENABLED, value);
}

int AimpAction::DefaultLocalHotKey::get() {
    return PropertyListExtension::GetInt32(InternalAimpObject, AIMP_ACTION_PROPID_DEFAULTLOCALHOTKEY);
}

void AimpAction::DefaultLocalHotKey::set(int value) {
    PropertyListExtension::SetInt32(InternalAimpObject, AIMP_ACTION_PROPID_DEFAULTLOCALHOTKEY, value);
}

int AimpAction::DefaultGlobalHotKey::get() {
    return PropertyListExtension::GetInt32(InternalAimpObject, AIMP_ACTION_PROPID_DEFAULTGLOBALHOTKEY);
}

void AimpAction::DefaultGlobalHotKey::set(int value) {
    PropertyListExtension::SetInt32(InternalAimpObject, AIMP_ACTION_PROPID_DEFAULTGLOBALHOTKEY, value);
}

int AimpAction::AlternativeGlobalHotKey::get() {
    return PropertyListExtension::GetInt32(InternalAimpObject, AIMP_ACTION_PROPID_DEFAULTGLOBALHOTKEY2);
}

void AimpAction::AlternativeGlobalHotKey::set(int value) {
    PropertyListExtension::SetInt32(InternalAimpObject, AIMP_ACTION_PROPID_DEFAULTGLOBALHOTKEY2, value);
}

void AimpAction::OnExecute::add(EventHandler^ onEvent) {
    if (_onExecuteHandler == nullptr) {
        AimpActionEventDelegate^ fp = gcnew AimpActionEventDelegate(this->Execute);
        _executeHandler = GCHandle::Alloc(fp);
        IntPtr ip = Marshal::GetFunctionPointerForDelegate(fp);
        auto callback = static_cast<AimpActionEventCallback>(ip.ToPointer());
        _onExecuteEvent = new AimpActionEvent(this, callback);
        GC::Collect();
        _onExecuteHandler = static_cast<EventHandler^>(Delegate::Combine(_onExecuteHandler, onEvent));
        InternalAimpObject->SetValueAsObject(AIMP_ACTION_PROPID_EVENT, _onExecuteEvent);
    }
}

void AimpAction::OnExecute::remove(EventHandler^ onEvent) {
    if (_onExecuteHandler != nullptr) {
        _onExecuteHandler = static_cast<EventHandler^>(Delegate::Remove(_onExecuteHandler, onEvent));
        InternalAimpObject->SetValueAsObject(AIMP_ACTION_PROPID_EVENT, nullptr);
        _executeHandler.Free();
        _onExecuteEvent->Release();
        _onExecuteEvent = nullptr;
    }
}

void AimpAction::OnExecute::raise(Object^ sender, EventArgs^ args) {
    if (_onExecuteHandler != nullptr) {
        _onExecuteHandler(sender, args);
    }
}

void AimpAction::Execute(const gcroot<IAimpActionEvent^> sender, IUnknown* data) {
    Object^ obj = sender;
    AimpAction^ action = dynamic_cast<AimpAction^>(obj);
    action->OnExecute(obj, EventArgs::Empty);
}

void AimpAction::FreeResources() {
    if (_executeHandler.IsAllocated) {
        _executeHandler.Free();
    }
}
