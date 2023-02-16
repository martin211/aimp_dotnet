//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "stdafx.h"
#include "AimpOrderedObjectList.h"
#include "OrderedListItem.h"

using namespace MusicLibrary;
using namespace AIMP::SDK::Collections;

AimpOrderedObjectList::AimpOrderedObjectList(IAIMPObjectList* list) : AimpObject<IAIMPObjectList>(list) {
    //_items = gcnew System::Collections::Generic::IList<IAimpOrderedItem^>();
}

IAimpOrderedItem^ AimpOrderedObjectList::Create(String^ name, SortDirectionType sortDirection) {
    return gcnew OrderedListItem(name, sortDirection);
}

AimpActionResult^ AimpOrderedObjectList::Add(IAimpOrderedItem^ entry) {
    //_items->Add(entry);
    const auto res = CheckResult(InternalAimpObject->Add(GET_IUNKNOWN(OrderedListItem, entry)));
    return gcnew AimpActionResult(res);
}

AimpActionResult^ AimpOrderedObjectList::Insert(int index, IAimpOrderedItem^ item) {
    //_items->Insert(index, item);
    const auto res = CheckResult(InternalAimpObject->Insert(index, GET_IUNKNOWN(OrderedListItem, item)));
    return gcnew AimpActionResult(res);
}

AimpActionResult^ AimpOrderedObjectList::GetObject(int index, IAimpOrderedItem^% item) {
    //const auto obj = _items[index];
    //item = obj;
    //return gcnew AimpActionResult(ActionResultType::OK);
    return gcnew AimpActionResult(ActionResultType::NotImplemented);
}

AimpActionResult^ AimpOrderedObjectList::SetObject(int index, IAimpOrderedItem^ item) {
    const auto res = CheckResult(InternalAimpObject->SetObject(index, GET_IUNKNOWN(OrderedListItem, item)));
    return gcnew AimpActionResult(res);
}

int AimpOrderedObjectList::Count::get() {
    return InternalAimpObject->GetCount();
}

AimpActionResult^ AimpOrderedObjectList::Clear() {
    const auto res = CheckResult(InternalAimpObject->Clear());
    return gcnew AimpActionResult(res);
}

AimpActionResult^ AimpOrderedObjectList::Delete(int index) {
    const auto res = CheckResult(InternalAimpObject->Delete(index));
    return gcnew AimpActionResult(res);
}
