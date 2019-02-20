// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpGroupingPresetStandard.h"
#include "SDK/AimpObjectList.h"
#include "AimpDataFilterGroup.h"

using namespace AIMP::SDK;

AimpGroupingPresetStandard::AimpGroupingPresetStandard(IAIMPMLGroupingPresetStandard* aimpObject) : AimpGroupingPreset(aimpObject)
{}

IAimpObjectList<String^>^ AimpGroupingPresetStandard::Fields::get()
{
    IAIMPObjectList* fields = nullptr;

    if (CheckResult(InternalAimpObject->GetValueAsObject(AIMPML_GROUPINGPRESETSTD_PROPID_FIELDS, IID_IAIMPObjectList, reinterpret_cast<void**>(&fields))) == AimpActionResult::OK)
    {
        return gcnew AimpObjectList<String^>(fields);
    }

    // TODO: Check GetObject
    //if (PropertyListExtension::GetObject(InternalAimpObject, AIMPML_GROUPINGPRESETSTD_PROPID_FIELDS, IID_IAIMPObjectList, (void**)&fields) == AimpActionResult::OK)
    //{
    //    if (fields == nullptr)
    //    {
    //        //fields = AimpConverter::MakeObject<IAIMPObjectList>(IID_IAIMPObjectList);
    //        //PropertyListExtension::SetObject(InternalAimpObject, AIMPML_GROUPINGPRESETSTD_PROPID_FIELDS, fields);
    //    }
    //    return gcnew AimpObjectList<String^>(fields);
    //}

    return nullptr;
}

void AimpGroupingPresetStandard::Fields::set(IAimpObjectList<String^>^ value)
{
    Generic::IList<String^>^ result;
    IAIMPObjectList *fields = AimpConverter::CreateAimpObject<IAIMPObjectList>(IID_IAIMPObjectList);
    int count = value->Count;

    for (int i = 0; i < count; i++)
    {
        //fields->Add(AimpConverter::GetAimpString(value[i]));
    }

    PropertyListExtension::SetObject(InternalAimpObject, AIMPML_GROUPINGPRESETSTD_PROPID_FIELDS, fields);
}

AimpActionResult AimpGroupingPresetStandard::GetFilter(IAimpDataFilterGroup ^%filter)
{
    IAIMPMLDataFilterGroup* f = nullptr;
    filter = nullptr;

    const AimpActionResult result = CheckResult(static_cast<IAIMPMLGroupingPresetStandard*>(InternalAimpObject)->GetFilter(&f));

    if (result == AimpActionResult::OK)
    {
        filter = gcnew AimpDataFilterGroup(f);
    }

    return result;
}
