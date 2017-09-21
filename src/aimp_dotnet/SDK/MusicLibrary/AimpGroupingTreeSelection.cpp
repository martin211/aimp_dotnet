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
#include "AimpGroupingTreeSelection.h"

using namespace AIMP::SDK;

AimpGroupingTreeSelection::AimpGroupingTreeSelection(IAIMPMLGroupingTreeSelection* aimpObject) : AimpObject(aimpObject)
{

}

AimpGroupingTreeSelection::~AimpGroupingTreeSelection()
{
    this->!AimpGroupingTreeSelection();
}

AimpGroupingTreeSelection::!AimpGroupingTreeSelection()
{
    _aimpObject->Release();
}

int AimpGroupingTreeSelection::GetCount()
{
    return InternalAimpObject->GetCount();
}

AimpActionResult AimpGroupingTreeSelection::GetValue(int index, System::String^% fieldName, System::Object^% value)
{
    IAIMPString* str = NULL;
    VARIANT val;

    fieldName = nullptr;
    value = nullptr;

    AimpActionResult result = CheckResult(InternalAimpObject->GetValue(index, &str, &val));

    try
    {
        if (result == AimpActionResult::Ok)
        {
            if (str != NULL)
                fieldName = AimpConverter::ToManagedString(str);

            value = AimpConverter::FromVaiant(&val);
        }
    }
    finally
    {
        if (str != NULL)
        {
            str->Release();
            str = NULL;
        }
    }

    return result;
}
