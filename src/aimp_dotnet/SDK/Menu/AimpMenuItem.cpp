/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#include "Stdafx.h"
#include "AimpMenuItem.h"
#include "../Action/AimpActionEvent.h"

using namespace AIMP::SDK;
using namespace System;
using namespace System::Runtime::InteropServices;

#pragma region AimpMenuItem

AimpMenuItem::AimpMenuItem(IAIMPMenuItem *menuItem) : AimpObject(menuItem)
{}

AimpMenuItem::~AimpMenuItem()
{
    _onExecuteHandler = nullptr;
    _onExecuteHandler = nullptr;
    _showHandler.Free();
    _executeHandler.Free();
}


String ^AimpMenuItem::Custom::get()
{
    return String::Empty;
}

void AimpMenuItem::Custom::set(String ^value)
{}


IAimpAction ^AimpMenuItem::Action::get()
{
    return nullptr;
}

void AimpMenuItem::Action::set(IAimpAction ^value)
{}


String ^AimpMenuItem::Id::get()
{
    String^ str = nullptr;
    PropertyListExtension::GetString(InternalAimpObject, AIMP_MENUITEM_PROPID_ID, *&str);
    return str;
}

void AimpMenuItem::Id::set(String ^value)
{
    _id = value;
    PropertyListExtension::SetString(InternalAimpObject, AIMP_MENUITEM_PROPID_ID, value);
}


String ^AimpMenuItem::Name::get()
{
    String^ str = nullptr;
    PropertyListExtension::GetString(InternalAimpObject, AIMP_MENUITEM_PROPID_NAME, *&str);
    return str;
}

void AimpMenuItem::Name::set(String ^value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMP_MENUITEM_PROPID_NAME, value);
}


bool AimpMenuItem::Checked::get()
{
    bool val = false;
    PropertyListExtension::GetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_CHECKED, val);
    return val;
}

void AimpMenuItem::Checked::set(bool value)
{
    PropertyListExtension::SetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_CHECKED, value);
}


bool AimpMenuItem::Enabled::get()
{
    bool val = false;
    PropertyListExtension::GetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_ENABLED, val);
    return val;
}

void AimpMenuItem::Enabled::set(bool value)
{
    PropertyListExtension::SetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_ENABLED, value);
}


bool AimpMenuItem::Visible::get()
{
    bool val = false;
    PropertyListExtension::GetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_VISIBLE, val);
    return val;
}

void AimpMenuItem::Visible::set(bool value)
{
    PropertyListExtension::SetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_VISIBLE, value);
}


Bitmap ^AimpMenuItem::Glyph::get()
{
    return nullptr;
}

void AimpMenuItem::Glyph::set(Bitmap ^value)
{
    if (value != nullptr)
    {
        IAIMPImage *image = AimpConverter::ToAimpImage(value);
        InternalAimpObject->SetValueAsObject(AIMP_MENUITEM_PROPID_GLYPH, image);
        image->Release();
    }
}


IAimpMenuItem ^AimpMenuItem::Parent::get()
{
    IAIMPMenuItem *item;
    InternalAimpObject->GetValueAsObject(AIMP_MENUITEM_PROPID_PARENT, IID_IAIMPMenuItem, (void**)&item);
    AimpMenuItem ^parentIttem = gcnew AimpMenuItem(item);
    item->Release();

    return parentIttem;
}

void AimpMenuItem::Parent::set(IAimpMenuItem ^value)
{
    InternalAimpObject->SetValueAsObject(AIMP_MENUITEM_PROPID_PARENT, ((AimpMenuItem^)value)->InternalAimpObject);
}


AimpMenuItemStyle AimpMenuItem::Style::get()
{
    int val = 0;
    PropertyListExtension::GetInt32(InternalAimpObject, AIMP_MENUITEM_PROPID_STYLE, val);
    return (AimpMenuItemStyle)val;
}

void AimpMenuItem::Style::set(AimpMenuItemStyle value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMP_MENUITEM_PROPID_STYLE, (int)value);
}

void AimpMenuItem::OnExecute::add(EventHandler ^onEvent)
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

void AimpMenuItem::OnExecute::remove(EventHandler ^onEvent)
{
    if (_onExecuteHandler != nullptr)
    {
        _onExecuteHandler = (EventHandler^)Delegate::Remove(_onExecuteHandler, onEvent);
        _onExecuteEvent->Release();
        delete _onExecuteEvent;
        _executeHandler.Free();
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
        AIMP::SDK::AimpActionEventDelegate ^fp = gcnew AIMP::SDK::AimpActionEventDelegate(this->Show);
        _showHandler = GCHandle::Alloc(fp);
        IntPtr ip = Marshal::GetFunctionPointerForDelegate(fp);
        AIMP::SDK::AimpActionEventCallback callback = static_cast<AIMP::SDK::AimpActionEventCallback>(ip.ToPointer());
        _onShowEvent = new AimpActionEvent(this, callback);
        GC::Collect();
        _onShowHandler = (EventHandler^)Delegate::Combine(_onShowHandler, onEvent);
        InternalAimpObject->SetValueAsObject(AIMP_MENUITEM_PROPID_EVENT_ONSHOW, _onShowEvent);
    }
}

void AimpMenuItem::OnShow::remove(EventHandler ^onEvent)
{
    if (_onShowHandler != nullptr)
    {
        _onShowHandler = (EventHandler^)Delegate::Remove(_onShowHandler, onEvent);
        _onShowEvent->Release();
        delete _onShowEvent;
        _showHandler.Free();
    }
}

void AimpMenuItem::OnShow::raise(Object ^sender, EventArgs ^args)
{
    if (_onShowHandler != nullptr)
    {
        _onShowHandler(sender, args);
    }
}

#pragma endregion
