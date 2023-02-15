//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpObjectList.h"

using namespace AIMP::SDK;

generic <class T>
IAIMPObjectList* AimpObjectList<T>::AimpObject::get() {
    return _nativeObject;
}

generic <typename T>
AimpObjectList<T>::AimpObjectList(IAIMPObjectList* nativeObject) {
    _nativeObject = nativeObject;
    RegisterAtMemoryManager();
}

generic <typename T>
ActionResult AimpObjectList<T>::Add(T entry) {
    return ACTION_RESULT(Utils::CheckResult(_nativeObject->Add(AimpConverter::ToAimpString((String^)entry))));
}

generic <typename T>
ActionResult AimpObjectList<T>::Clear() {
    return ACTION_RESULT(Utils::CheckResult(_nativeObject->Clear()));
}

generic <typename T>
ActionResult AimpObjectList<T>::Delete(int index) {
    return ACTION_RESULT(Utils::CheckResult(_nativeObject->Delete(index)));
}

generic <typename T>
ActionResult AimpObjectList<T>::Insert(int index, T entry) {
    return ACTION_RESULT(Utils::CheckResult(_nativeObject->Insert(index, AimpConverter::ToAimpString((String^)entry))));
}

generic <typename T>
int AimpObjectList<T>::Count::get() {
    return _nativeObject->GetCount();
}

generic <typename T>
ActionResult AimpObjectList<T>::GetObject(int index, T% item) {
    IAIMPString* str;
    ActionResultType result = Utils::CheckResult(
        _nativeObject->GetObject(index, IID_IAIMPString, reinterpret_cast<void**>(&str)));

    if (result == ActionResultType::OK && str != nullptr) {
        item = (T)AimpConverter::ToManagedString(str);
        str->Release();
        str = nullptr;
    }

    return ACTION_RESULT(result);
}

generic <typename T>
ActionResult AimpObjectList<T>::SetObject(int index, T item) {
    return ACTION_RESULT(
        Utils::CheckResult(_nativeObject->SetObject(index, AimpConverter::ToAimpString((String^)item))));
}

generic <class TObject>
Collections::IEnumerator^ AimpObjectList<TObject>::GetEnumerator() {
    return nullptr;
}
