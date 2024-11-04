//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "stdafx.h"
#include "OrderedListItem.h"

using namespace AIMP::SDK::Collections;
using namespace MusicLibrary;

OrderedListItem::OrderedListItem(String^ name, SortDirectionType sortDirection) {
    const auto aimpName = AimpConverter::ToAimpString(name);
    AimpMemoryManager::getInstance().AddObject(this->GetHashCode(), aimpName, "OrderedListItem");
    _item = new InternalOrderedListItem(aimpName, sortDirection);
    _item->AddRef();
}

OrderedListItem::~OrderedListItem() {
    _item->Release();
    AimpMemoryManager::getInstance().Release(this->GetHashCode());
}

SortDirectionType OrderedListItem::Value::get() {
    //IAIMPMLSortDirection* obj = nullptr;
    int val = 0;

    //_item->QueryInterface(IID_IAIMPMLSortDirection, reinterpret_cast<void**>(obj));
    const auto res = Utils::CheckResult(_item->GetValue(&val));
    if (res == ActionResultType::OK) {
        return static_cast<SortDirectionType>(val);
    }

    return SortDirectionType::Undefined;
}

void OrderedListItem::Value::set(SortDirectionType value) {
    //IAIMPMLSortDirection* obj = nullptr;
    //_item->QueryInterface(IID_IAIMPMLSortDirection, reinterpret_cast<void**>(obj));
    _item->SetValue(static_cast<int>(value));
}

IAimpString^ OrderedListItem::Name::get() {
    //_item->QueryInterface(IID_IAIMPString, reinterpret_cast<void**>(obj));
    return gcnew AimpString(_item);
}

IUnknown* OrderedListItem::InternalAimpObject::get() {
    return nullptr;
}
