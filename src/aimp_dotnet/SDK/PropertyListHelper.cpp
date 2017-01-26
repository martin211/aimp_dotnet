#pragma once
#include "Stdafx.h"
#include "PropertyListHelper.h"

using namespace AIMP::SDK;

AimpActionResult PropertyListExtension::SetObject(IAIMPPropertyList* propertyList, int propertyId, IUnknown *value)
{
    return Utils::CheckResult(propertyList->SetValueAsObject(propertyId, value));
}

AimpActionResult PropertyListExtension::SetString(IAIMPPropertyList* propertyList, int propertyId, String ^value)
{
    // No need to process empty value
    if (String::IsNullOrWhiteSpace(value))
    {
        return AimpActionResult::InvalidArguments;
    }

    IAIMPString *str = NULL;
    try
    {
        str = AimpConverter::ToAimpString(value);
        return SetObject(propertyList, propertyId, str);
    }
    finally
    {
        str->Release();
        str = NULL;
    }

    return AimpActionResult::Unexpected;
}

AimpActionResult PropertyListExtension::SetInt32(IAIMPPropertyList* propertyList, int propertyId, int value)
{
    return Utils::CheckResult(propertyList->SetValueAsInt32(propertyId, value));
}

AimpActionResult PropertyListExtension::SetInt64(IAIMPPropertyList* propertyList, int propertyId, Int64 value)
{
    return Utils::CheckResult(propertyList->SetValueAsInt64(propertyId, value));
}

AimpActionResult PropertyListExtension::SetFloat(IAIMPPropertyList* propertyList, int propertyId, double value)
{
    return Utils::CheckResult(propertyList->SetValueAsFloat(propertyId, value));
}

AimpActionResult PropertyListExtension::SetBool(IAIMPPropertyList* propertyList, int propertyId, bool value)
{
    return SetInt32(propertyList, propertyId, value ? 1 : 0);
}

AimpActionResult PropertyListExtension::GetString(IAIMPPropertyList* propertyList, int propertyId, String^% value)
{
    IAIMPString* str = NULL;
    String ^val = String::Empty;

    try
    {
        AimpActionResult result = Utils::CheckResult(propertyList->GetValueAsObject(propertyId, IID_IAIMPString, (void**)&str));
        if (result != AimpActionResult::Ok)
        {
            value = String::Empty;
            return result;
        }

        if (str != NULL)
        {
            result = GetString(str, val);
            value = val;
            return result;
        }
    }
    catch (System::Exception ^ex)
    {
        return AimpActionResult::Fail;
    }
    finally
    {
        if (str != NULL)
        {
            str->Release();
            str = NULL;
        }
    }

    return AimpActionResult::Unexpected;
}

AimpActionResult PropertyListExtension::GetString(IAIMPString* aimpString, String^% value)
{
    value = gcnew String(aimpString->GetData());
    return AimpActionResult::Ok;
}

AimpActionResult PropertyListExtension::GetObject(IAIMPPropertyList* propertyList, int propertyId, REFIID objectId, void** value)
{
    AimpActionResult result = Utils::CheckResult(propertyList->GetValueAsObject(propertyId, objectId, value));
    return result;
}

AimpActionResult PropertyListExtension::GetInt32(IAIMPPropertyList* propertyList, int propertyId, int %value)
{
    int val = 0;
    AimpActionResult result = Utils::CheckResult(propertyList->GetValueAsInt32(propertyId, &val));
    value = val;
    return result;
}

AimpActionResult PropertyListExtension::GetInt64(IAIMPPropertyList* propertyList, int propertyId, Int64 %value)
{
    Int64 val = 0;
    AimpActionResult result = Utils::CheckResult(propertyList->GetValueAsInt64(propertyId, &val));
    value = val;
    return result;
}

AimpActionResult PropertyListExtension::GetFloat(IAIMPPropertyList* propertyList, int propertyId, double %value)
{
    double val = 0;
    AimpActionResult result = Utils::CheckResult(propertyList->GetValueAsFloat(propertyId, &val));
    value = val;
    return result;
}

AimpActionResult PropertyListExtension::GetBool(IAIMPPropertyList* propertyList, int propertyId, bool %value)
{
    int *val = 0;
    AimpActionResult result = GetInt32(propertyList, propertyId, *val);
    value = val > 0;
    return result;
}

String^ PropertyListExtension::GetString(IAIMPPropertyList *propertyList, int propertyId)
{
    String^ val = String::Empty;
    if (GetString(propertyList, propertyId, *&val) == AimpActionResult::Ok)
    {
        return val;
    }

    return val;
}

int PropertyListExtension::GetInt32(IAIMPPropertyList *propertyList, int propertyId)
{
    int val = 0;
    if (GetInt32(propertyList, propertyId, val) == AimpActionResult::Ok)
    {
        return val;
    }

    return 0;
}

Int64 PropertyListExtension::GetInt64(IAIMPPropertyList *propertyList, int propertyId)
{
    Int64 val;
    if (GetInt64(propertyList, propertyId, val) == AimpActionResult::Ok)
    {
        return val;
    }

    return 0;
}

double PropertyListExtension::GetFloat(IAIMPPropertyList *propertyList, int propertyId)
{
    double val;
    if (GetFloat(propertyList, propertyId, val) == AimpActionResult::Ok)
    {
        return val;
    }

    return 0;
}

bool PropertyListExtension::GetBool(IAIMPPropertyList *propertyList, int propertyId)
{
    bool val;
    if (GetBool(propertyList, propertyId, val) == AimpActionResult::Ok)
    {
        return val;
    }

    return false;
}

AimpActionResult PropertyListExtension::GetVariant(IAIMPPropertyList2 *propertyList, int propertyId, Object^% value)
{
    VARIANT *val = NULL;
    AimpActionResult result = Utils::CheckResult(propertyList->GetValueAsVariant(propertyId, val));
    value = AimpConverter::FromVaiant(val);
    return result;
}

AimpActionResult PropertyListExtension::SetVariant(IAIMPPropertyList2 *propertyList, int propertyId, Object^% val)
{
    return AimpActionResult::NotImplemented;
}