// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpGroupingTreeDataProviderSelection.h"

#include <string>

using namespace AIMP::SDK;

InternalAimpGroupingTreeDataProviderSelection::InternalAimpGroupingTreeDataProviderSelection(
    gcroot<IAimpGroupingTreeDataProviderSelection^> managedInstance) {
    _managedInstance = managedInstance;
}

HRESULT WINAPI InternalAimpGroupingTreeDataProviderSelection::GetDisplayValue(IAIMPString** S) {
    auto result = _managedInstance->GetDisplayValue();

    if (result->ResultType == ActionResultType::OK) {
        *S = AimpConverter::ToAimpString(result->Result);
    }

    return HRESULT(result->ResultType);
}

DWORD WINAPI InternalAimpGroupingTreeDataProviderSelection::GetFlags() {
    return DWORD(_managedInstance->GetFlags());
}

HRESULT WINAPI InternalAimpGroupingTreeDataProviderSelection::GetImageIndex(int* Index) {
    auto result = _managedInstance->GetImageIndex();

    if (result->ResultType == ActionResultType::OK) {
        *Index = static_cast<int>(result->Result);
    }

    return HRESULT(result->ResultType);
}

HRESULT WINAPI InternalAimpGroupingTreeDataProviderSelection::GetValue(IAIMPString** FieldName, VARIANT* Value) {
    auto result = _managedInstance->GetValue();

    if (result->ResultType == ActionResultType::OK) {
        *FieldName = AimpConverter::ToAimpString(result->Item1);
        VARIANT v = AimpConverter::ToNativeVariant(result->Item2);
        VariantCopyInd(Value, &v);
    }

    return HRESULT(result->ResultType);
}

BOOL WINAPI InternalAimpGroupingTreeDataProviderSelection::NextRow() {
    return BOOL(_managedInstance->NextRow());
}

ULONG WINAPI InternalAimpGroupingTreeDataProviderSelection::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI InternalAimpGroupingTreeDataProviderSelection::Release(void) {
    return Base::Release();
}

HRESULT WINAPI InternalAimpGroupingTreeDataProviderSelection::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPMLGroupingTreeDataProviderSelection) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}
