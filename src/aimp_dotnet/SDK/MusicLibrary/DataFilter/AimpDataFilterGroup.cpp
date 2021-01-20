// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpDataFilterGroup.h"
#include "AimpDataFieldFilter.h"
#include "AimpDataFieldFilterByArray.h"

using namespace AIMP::SDK;

// TODO: #18
AimpDataFilterGroup::AimpDataFilterGroup(IAIMPMLDataFilterGroup* filterGroup) : AimpObject(filterGroup, false) {
}

FilterGroupOperationType AimpDataFilterGroup::Operation::get() {
    return FilterGroupOperationType(PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FILTERGROUP_OPERATION));
}

void AimpDataFilterGroup::Operation::set(FilterGroupOperationType val) {
    PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FILTERGROUP_OPERATION, static_cast<int>(val));
}

AimpActionResult<IAimpDataFieldFilter^>^ AimpDataFilterGroup::Add(
    String^ field,
    Object^ value1,
    Object^ value2,
    FieldFilterOperationType operation) {
    IAimpDataFieldFilter^ filter = nullptr;
    IAIMPMLDataFieldFilter* nativeFilter = nullptr;
    ActionResultType result = ActionResultType::Fail;

    VARIANT val1 = AimpConverter::ToNativeVariant(value1);
    VARIANT val2 = AimpConverter::ToNativeVariant(value2);


    VARIANT v1;
    VariantInit(&v1);

    auto sField = AimpConverter::ToAimpString(field);

    try {
        result = CheckResult(InternalAimpObject->Add(
            sField,
            &val1,
            &val2,
            static_cast<int>(operation),
            &nativeFilter));

        if (result == ActionResultType::OK && nativeFilter != nullptr) {
            filter = gcnew AimpDataFieldFilter(nativeFilter);
        }
    }
    finally {
        if (sField != nullptr) {
            sField->Release();
            sField = nullptr;
        }
    }

    return gcnew AimpActionResult<IAimpDataFieldFilter^>(result, filter);
}

AimpActionResult<IAimpDataFieldFilterByArray^>^ AimpDataFilterGroup::Add(
    String^ field,
    array<Object^>^ values,
    int count) {
    IAIMPMLDataFieldFilterByArray* nativeObj = nullptr;
    auto cnt = values->Length;
    VARIANT* variants = new VARIANT[cnt];
    IAimpDataFieldFilterByArray^ filter = nullptr;

    for (int i = 0; i < values->Length; i++) {
        variants[i] = AimpConverter::ToNativeVariant(values[i]);
    }

    const auto result = CheckResult(InternalAimpObject->Add2(
        AimpConverter::ToAimpString(field),
        &variants[0],
        count,
        &nativeObj));

    if (result == ActionResultType::OK && nativeObj != nullptr) {
        filter = gcnew AimpDataFieldFilterByArray(nativeObj);
    }

    return gcnew AimpActionResult<IAimpDataFieldFilterByArray^>(result, filter);
}

AimpActionResult<IAimpDataFilterGroup^>^ AimpDataFilterGroup::AddGroup() {
    IAIMPMLDataFilterGroup* nativeGroup = nullptr;
    const ActionResultType result = CheckResult(InternalAimpObject->AddGroup(&nativeGroup));
    IAimpDataFilterGroup^ group = nullptr;

    if (result == ActionResultType::OK && nativeGroup != nullptr) {
        group = gcnew AimpDataFilterGroup(nativeGroup);
    }

    return gcnew AimpActionResult<IAimpDataFilterGroup^>(result, group);
}

ActionResult AimpDataFilterGroup::Clear() {
    return ACTION_RESULT(CheckResult(InternalAimpObject->Clear()));
}

ActionResult AimpDataFilterGroup::Delete(int index) {
    return ACTION_RESULT(CheckResult(InternalAimpObject->Delete(index)));
}

int AimpDataFilterGroup::GetChildCount() {
    return InternalAimpObject->GetChildCount();
}

AimpActionResult<IAimpDataFilterGroup^>^ AimpDataFilterGroup::GetFilterGroup(int index) {
    IAimpDataFilterGroup^ group = nullptr;
    IAIMPMLDataFilterGroup* child = nullptr;
    const auto result = CheckResult(
        InternalAimpObject->GetChild(index, IID_IAIMPMLDataFilterGroup, reinterpret_cast<void**>(&child)));
    if (result == ActionResultType::OK && child != nullptr) {
        group = gcnew AimpDataFilterGroup(child);
    }

    return gcnew AimpActionResult<IAimpDataFilterGroup^>(result, group);
}

AimpActionResult<IAimpDataFieldFilter^>^ AimpDataFilterGroup::GetFieldFilter(int index) {
    IAimpDataFieldFilter^ fieldFilter = nullptr;
    IAIMPMLDataFieldFilter* child = nullptr;
    const auto result = CheckResult(
        InternalAimpObject->GetChild(index, IID_IAIMPMLDataFieldFilter, reinterpret_cast<void**>(&child)));
    if (result == ActionResultType::OK && child != nullptr) {
        fieldFilter = gcnew AimpDataFieldFilter(child);
    }

    return gcnew AimpActionResult<IAimpDataFieldFilter^>(result, fieldFilter);
}

void AimpDataFilterGroup::BeginUpdate() {
    InternalAimpObject->BeginUpdate();
}

void AimpDataFilterGroup::EndUpdate() {
    InternalAimpObject->EndUpdate();
}
