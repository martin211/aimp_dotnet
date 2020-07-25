// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpMenuItem.h"
#include "../Action/AimpActionEvent.h"
#include "../Action/AimpAction.h"

using namespace AIMP::SDK;
using namespace System;
using namespace Runtime::InteropServices;

AimpMenuItem::AimpMenuItem(IAIMPMenuItem* menuItem) : AimpObject(menuItem) {
    _onExecuteEvent = nullptr;
    _onShowEvent = nullptr;
}

void AimpMenuItem::FreeResources() {
    AimpObject::FreeResources();
    _onExecuteHandler = nullptr;
    _onExecuteEvent = nullptr;
}

String^ AimpMenuItem::Custom::get() {
    return String::Empty;
}

void AimpMenuItem::Custom::set(String^ value) {
}


IAimpAction^ AimpMenuItem::Action::get() {
    IAIMPAction* action;
    if (PropertyListExtension::GetObject(InternalAimpObject, AIMP_MENUITEM_PROPID_ACTION, IID_IAIMPAction,
                                         reinterpret_cast<void**>(&action)) == ActionResultType::OK) {
        return gcnew AimpAction(action);
    }

    return nullptr;
}

void AimpMenuItem::Action::set(IAimpAction^ value) {
    PropertyListExtension::SetObject(InternalAimpObject, AIMP_MENUITEM_PROPID_ACTION,
                                     static_cast<AimpAction^>(value)->InternalAimpObject);
}


String^ AimpMenuItem::Id::get() {
    String^ str = nullptr;
    PropertyListExtension::GetString(InternalAimpObject, AIMP_MENUITEM_PROPID_ID, *&str);
    return str;
}

void AimpMenuItem::Id::set(String^ value) {
    _id = value;
    PropertyListExtension::SetString(InternalAimpObject, AIMP_MENUITEM_PROPID_ID, value);
}


String^ AimpMenuItem::Name::get() {
    String^ str = nullptr;
    PropertyListExtension::GetString(InternalAimpObject, AIMP_MENUITEM_PROPID_NAME, *&str);
    return str;
}

void AimpMenuItem::Name::set(String^ value) {
    PropertyListExtension::SetString(InternalAimpObject, AIMP_MENUITEM_PROPID_NAME, value);
}


bool AimpMenuItem::Checked::get() {
    bool val = false;
    PropertyListExtension::GetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_CHECKED, val);
    return val;
}

void AimpMenuItem::Checked::set(bool value) {
    PropertyListExtension::SetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_CHECKED, value);
}


bool AimpMenuItem::Enabled::get() {
    bool val = false;
    PropertyListExtension::GetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_ENABLED, val);
    return val;
}

void AimpMenuItem::Enabled::set(bool value) {
    PropertyListExtension::SetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_ENABLED, value);
}


bool AimpMenuItem::Visible::get() {
    bool val = false;
    PropertyListExtension::GetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_VISIBLE, val);
    return val;
}

void AimpMenuItem::Visible::set(bool value) {
    PropertyListExtension::SetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_VISIBLE, value);
}


Bitmap^ AimpMenuItem::Glyph::get() {
    return nullptr;
}

void AimpMenuItem::Glyph::set(Bitmap^ value) {
    if (value != nullptr) {
        IAIMPImage* image = AimpConverter::ToAimpImage(value);
        InternalAimpObject->SetValueAsObject(AIMP_MENUITEM_PROPID_GLYPH, image);
        image->Release();
    }
}


IAimpMenuItem^ AimpMenuItem::Parent::get() {
    if (_parent == nullptr) {
        IAIMPMenuItem* item = nullptr;
        const auto result = CheckResult(InternalAimpObject->GetValueAsObject(
            AIMP_MENUITEM_PROPID_PARENT, IID_IAIMPMenuItem,
            reinterpret_cast<void**>(&item)));
        if (result == ActionResultType::OK) {
            _parent = gcnew AimpMenuItem(item);
        }
    }

    return _parent;
}

void AimpMenuItem::Parent::set(IAimpMenuItem^ value) {
    const auto result = CheckResult(InternalAimpObject->SetValueAsObject(AIMP_MENUITEM_PROPID_PARENT,
                                                                         static_cast<AimpMenuItem^>(value)->
                                                                         InternalAimpObject));
    if (result != ActionResultType::OK) {
        throw gcnew AimpActionException(result, "Unable to set parent.");
    }
}


MenuItemStyle AimpMenuItem::Style::get() {
    int val = 0;
    const auto result = CheckResult(InternalAimpObject->GetValueAsInt32(AIMP_MENUITEM_PROPID_STYLE, &val));
    //PropertyListExtension::GetInt32(InternalAimpObject, AIMP_MENUITEM_PROPID_STYLE, val);
    return static_cast<MenuItemStyle>(val);
}

void AimpMenuItem::Style::set(MenuItemStyle value) {
    PropertyListExtension::SetInt32(InternalAimpObject, AIMP_MENUITEM_PROPID_STYLE, static_cast<int>(value));
}


bool AimpMenuItem::IsDefault::get() {
    bool val = false;
    PropertyListExtension::GetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_DEFAULT, val);
    return val;
}

void AimpMenuItem::IsDefault::set(bool value) {
    PropertyListExtension::SetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_DEFAULT, value);
}


int AimpMenuItem::Shortcut::get() {
    int val = 0;
    PropertyListExtension::GetInt32(InternalAimpObject, AIMP_MENUITEM_PROPID_SHORTCUT, val);
    return val;
}

void AimpMenuItem::Shortcut::set(int val) {
    PropertyListExtension::SetInt32(InternalAimpObject, AIMP_MENUITEM_PROPID_SHORTCUT, val);
}


void AimpMenuItem::OnExecute::add(EventHandler^ onEvent) {
    if (_onExecuteHandler == nullptr) {
        AimpActionEventDelegate^ fp = gcnew AimpActionEventDelegate(this->Execute);
        _executeHandler = GCHandle::Alloc(fp);
        IntPtr ip = Marshal::GetFunctionPointerForDelegate(fp);
        auto callback = static_cast<AimpActionEventCallback>(ip.ToPointer());
        _onExecuteEvent = new AimpActionEvent(this, callback);
        GC::Collect();
        _onExecuteHandler = static_cast<EventHandler^>(Delegate::Combine(_onExecuteHandler, onEvent));
        InternalAimpObject->SetValueAsObject(AIMP_MENUITEM_PROPID_EVENT, _onExecuteEvent);
    }
}

void AimpMenuItem::OnExecute::remove(EventHandler^ onEvent) {
    if (_onExecuteHandler != nullptr) {
        _onExecuteHandler = static_cast<EventHandler^>(Delegate::Remove(_onExecuteHandler, onEvent));
        _onExecuteEvent->Release();
        _onExecuteEvent = nullptr;
        delete _onExecuteEvent;
        _executeHandler.Free();
    }
}

void AimpMenuItem::OnExecute::raise(Object^ sender, EventArgs^ args) {
    if (_onExecuteHandler != nullptr) {
        _onExecuteHandler(sender, args);
    }
}

void AimpMenuItem::OnShow::add(EventHandler^ onEvent) {
    if (_onShowHandler == nullptr) {
        AimpActionEventDelegate^ fp = gcnew AimpActionEventDelegate(this->Show);
        _showHandler = GCHandle::Alloc(fp);
        IntPtr ip = Marshal::GetFunctionPointerForDelegate(fp);
        auto callback = static_cast<AimpActionEventCallback>(ip.ToPointer());
        _onShowEvent = new AimpActionEvent(this, callback);
        GC::Collect();
        _onShowHandler = static_cast<EventHandler^>(Delegate::Combine(_onShowHandler, onEvent));
        InternalAimpObject->SetValueAsObject(AIMP_MENUITEM_PROPID_EVENT_ONSHOW, _onShowEvent);
    }
}

void AimpMenuItem::OnShow::remove(EventHandler^ onEvent) {
    if (_onShowHandler != nullptr) {
        _onShowHandler = static_cast<EventHandler^>(Delegate::Remove(_onShowHandler, onEvent));
        _onShowEvent->Release();
        _onShowEvent = nullptr;
        delete _onShowEvent;
        _showHandler.Free();
    }
}

void AimpMenuItem::OnShow::raise(Object^ sender, EventArgs^ args) {
    if (_onShowHandler != nullptr) {
        _onShowHandler(sender, args);
    }
}
