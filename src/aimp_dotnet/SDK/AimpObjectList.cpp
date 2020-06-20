// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpObjectList.h"

using namespace AIMP::SDK;

generic <typename T>
AimpObjectList<T>::AimpObjectList(IAIMPObjectList* nativeObject)
{
    _nativeObject = nativeObject;
}

generic <typename T>
ActionResultType AimpObjectList<T>::Add(T entry)
{
    return Utils::CheckResult(_nativeObject->Add(AimpConverter::ToAimpString((String^)entry)));
}

generic <typename T>
ActionResultType AimpObjectList<T>::Clear()
{
    return Utils::CheckResult(_nativeObject->Clear());
}

generic <typename T>
ActionResultType AimpObjectList<T>::Delete(int index)
{
    return Utils::CheckResult(_nativeObject->Delete(index));
}

generic <typename T>
ActionResultType AimpObjectList<T>::Insert(int index, T entry)
{
    return Utils::CheckResult(_nativeObject->Insert(index, AimpConverter::ToAimpString((String^)entry)));
}

generic <typename T>
int AimpObjectList<T>::Count::get()
{
    return _nativeObject->GetCount();
}

generic <typename T>
ActionResultType AimpObjectList<T>::GetObject(int index, T% item)
{
    IAIMPString* str;
    ActionResultType result = Utils::CheckResult(
        _nativeObject->GetObject(index, IID_IAIMPString, reinterpret_cast<void**>(&str)));

    if (result == ActionResultType::OK && str != nullptr)
    {
        item = (T)AimpConverter::ToManagedString(str);
        str->Release();
        str = nullptr;
    }

    return result;
}

generic <typename T>
ActionResultType AimpObjectList<T>::SetObject(int index, T item)
{
    return Utils::CheckResult(_nativeObject->SetObject(index, AimpConverter::ToAimpString((String^)item)));
}
