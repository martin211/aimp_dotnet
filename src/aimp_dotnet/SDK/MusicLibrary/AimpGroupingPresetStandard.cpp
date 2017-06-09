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

using namespace AIMP::SDK;

AimpGroupingPresetStandard::AimpGroupingPresetStandard(IAIMPMLGroupingPresetStandard *aimpObject) : AimpGroupingPreset(aimpObject)
{}

IAimpObjectList<String^>^ AimpGroupingPresetStandard::Fields::get()
{
    IAIMPObjectList* fields = NULL;

    if (CheckResult(InternalAimpObject->GetValueAsObject(AIMPML_GROUPINGPRESETSTD_PROPID_FIELDS, IID_IAIMPObjectList, (void**)&fields)) == AimpActionResult::Ok)
    {
        return gcnew AimpObjectList<String^>(fields);
    }

    // TODO: Check GetObject
    //if (PropertyListExtension::GetObject(InternalAimpObject, AIMPML_GROUPINGPRESETSTD_PROPID_FIELDS, IID_IAIMPObjectList, (void**)&fields) == AimpActionResult::Ok)
    //{
    //    if (fields == NULL)
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
    System::Collections::Generic::IList<String^>^ result;
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
    IAIMPMLDataFilterGroup *f;
    filter = nullptr;

    AimpActionResult result = CheckResult(((IAIMPMLGroupingPresetStandard*)InternalAimpObject)->GetFilter(&f));

    if (result == AimpActionResult::Ok)
    {
        filter = gcnew AimpDataFilterGroup(f);
    }

    return result;
}
