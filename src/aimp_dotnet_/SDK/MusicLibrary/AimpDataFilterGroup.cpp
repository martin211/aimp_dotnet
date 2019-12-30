// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpDataFilterGroup.h"
#include "AimpDataFieldFilter.h"
#include "AimpDataFieldFilterByArray.h"

using namespace AIMP::SDK;

AimpDataFilterGroup::AimpDataFilterGroup(IAIMPMLDataFilterGroup* filterGroup) : AimpObject(filterGroup)
{
}

FilterGroupOperationType AimpDataFilterGroup::Operation::get()
{
    return FilterGroupOperationType(PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FILTERGROUP_OPERATION));
}

void AimpDataFilterGroup::Operation::set(FilterGroupOperationType val)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FILTERGROUP_OPERATION, int(val));
}

AimpActionResult AimpDataFilterGroup::Add(
    String^ field,
    Object^ value1,
    Object^ value2,
    FieldFilterOperationType operation,
    IAimpDataFieldFilter^% filter)
{
    filter = nullptr;
    IAIMPMLDataFieldFilter* nativeFilter = nullptr;
    AimpActionResult result = AimpActionResult::Fail;

    VARIANT val1 = AimpConverter::ToNativeVariant(value1);
    VARIANT val2 = AimpConverter::ToNativeVariant(value2);


    VARIANT v1;
    VariantInit(&v1);

    auto sField = AimpConverter::ToAimpString(field);

    try
    {
        result = CheckResult(InternalAimpObject->Add(
            sField,
            &val1,
            &val2,
            int(operation),
            &nativeFilter));

        if (result == AimpActionResult::OK && nativeFilter != nullptr)
        {
            filter = gcnew AimpDataFieldFilter(nativeFilter);
        }
    }
    finally
    {
        if (sField != nullptr)
        {
            sField->Release();
            sField = nullptr;
        }
    }

    return result;
}

AimpActionResult AimpDataFilterGroup::Add(
    String^ field,
    array<Object^>^ values,
    int count,
    IAimpDataFieldFilterByArray^% filter)
{
    IAIMPMLDataFieldFilterByArray* nativeObj = nullptr;
    int cnt = values->Length;
    VARIANT* variants = new VARIANT[cnt];
    filter = nullptr;

    for (int i = 0; i < values->Length; i++)
    {
        variants[i] = AimpConverter::ToNativeVariant(values[i]);
    }

    const auto result = CheckResult(InternalAimpObject->Add2(
        AimpConverter::ToAimpString(field),
        &variants[0],
        count,
        &nativeObj));

    if (result == AimpActionResult::OK && nativeObj != nullptr)
    {
        filter = gcnew AimpDataFieldFilterByArray(nativeObj);
    }

    return result;
}

AimpActionResult AimpDataFilterGroup::AddGroup(IAimpDataFilterGroup^% group)
{
    IAIMPMLDataFilterGroup* nativeGroup = nullptr;
    const AimpActionResult result = CheckResult(InternalAimpObject->AddGroup(&nativeGroup));
    group = nullptr;

    if (result == AimpActionResult::OK && nativeGroup != nullptr)
    {
        group = gcnew AimpDataFilterGroup(nativeGroup);
    }

    return result;
}

AimpActionResult AimpDataFilterGroup::Clear()
{
    return CheckResult(InternalAimpObject->Clear());
}

AimpActionResult AimpDataFilterGroup::Delete(int index)
{
    return CheckResult(InternalAimpObject->Delete(index));
}

int AimpDataFilterGroup::GetChildCount()
{
    return InternalAimpObject->GetChildCount();
}

AimpActionResult AimpDataFilterGroup::GetChild(int index, IAimpDataFilterGroup^% group)
{
    group = nullptr;
    IAIMPMLDataFilterGroup* child = nullptr;
    const auto result = CheckResult(
        InternalAimpObject->GetChild(index, IID_IAIMPMLDataFilterGroup, reinterpret_cast<void**>(&child)));
    if (result == AimpActionResult::OK && child != nullptr)
    {
        group = gcnew AimpDataFilterGroup(child);
    }

    return result;
}

AimpActionResult AimpDataFilterGroup::GetChild(int index, IAimpDataFieldFilter^% fieldFilter)
{
    fieldFilter = nullptr;
    IAIMPMLDataFieldFilter* child = nullptr;
    const auto result = CheckResult(
        InternalAimpObject->GetChild(index, IID_IAIMPMLDataFieldFilter, reinterpret_cast<void**>(&child)));
    if (result == AimpActionResult::OK && child != nullptr)
    {
        fieldFilter = gcnew AimpDataFieldFilter(child);
    }

    return result;
}

void AimpDataFilterGroup::BeginUpdate()
{
    InternalAimpObject->BeginUpdate();
}

void AimpDataFilterGroup::EndUpdate()
{
    InternalAimpObject->EndUpdate();
}
