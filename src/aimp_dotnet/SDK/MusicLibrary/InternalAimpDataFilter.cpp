// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpDataFilter.h"
#include "DataFilter/AimpDataFilter.h"

using namespace AIMP::SDK;
using namespace MusicLibrary;

InternalAimpDataFilter::InternalAimpDataFilter(gcroot<IAimpDataFilter^> managedInstance) : InternalAimpDataFilterGroup(
    static_cast<IAimpDataFilterGroup^>(managedInstance)) {
    _managedInstance = managedInstance;
}

HRESULT InternalAimpDataFilter::Assign(IAIMPMLDataFilter* Source) {
    return HRESULT(_managedInstance->Assign(gcnew AimpDataFilter(Source))->ResultType);
}

HRESULT InternalAimpDataFilter::Clone(void** Filter) {
    auto res = _managedInstance->Clone();

    if (res->ResultType == ActionResultType::OK) {
        *Filter = new InternalAimpDataFilter(res->Result);
    }

    return HRESULT(res->ResultType);
}

HRESULT WINAPI InternalAimpDataFilter::GetValueAsInt32(int PropertyID, int* Value) {
    InternalAimpDataFilterGroup::GetValueAsInt32(PropertyID, Value);

    if (PropertyID == AIMPML_FILTER_OFFSET)
        *Value = _managedInstance->Offset;

    if (PropertyID == AIMPML_FILTER_LIMIT)
        *Value = _managedInstance->Limit;

    if (PropertyID == AIMPML_FILTER_SORTDIRECTION)
        *Value = int(_managedInstance->SortDirection);

    if (PropertyID == AIMPML_FILTER_ALPHABETICINDEX)
        *Value = _managedInstance->AlphaBeticIndex;

    return S_OK;
}

HRESULT WINAPI InternalAimpDataFilter::SetValueAsInt32(int PropertyID, int Value) {
    InternalAimpDataFilterGroup::SetValueAsInt32(PropertyID, Value);

    if (PropertyID == AIMPML_FILTER_OFFSET)
        _managedInstance->Offset = Value;

    if (PropertyID == AIMPML_FILTER_LIMIT)
        _managedInstance->Limit = Value;

    if (PropertyID == AIMPML_FILTER_SORTDIRECTION)
        _managedInstance->SortDirection = SortDirectionType(Value);

    if (PropertyID == AIMPML_FILTER_ALPHABETICINDEX)
        _managedInstance->AlphaBeticIndex = Value;

    return S_OK;
}

HRESULT WINAPI InternalAimpDataFilter::GetValueAsObject(int PropertyID, REFIID IID, void** Value) {
    if (PropertyID == AIMPML_FILTER_SORTBY) {
        IAIMPString* str = AimpConverter::ToAimpString(_managedInstance->SortBy);
        *Value = str;
        str->Release();
        str = nullptr;
    }

    if (PropertyID == AIMPML_FILTER_SEARCHSTRING) {
        IAIMPString* str = AimpConverter::ToAimpString(_managedInstance->SearchString);
        *Value = str;
        str->Release();
        str = nullptr;
    }

    return S_OK;
}

HRESULT WINAPI InternalAimpDataFilter::SetValueAsObject(int PropertyID, IUnknown* Value) {
    if (PropertyID == AIMPML_FILTER_SORTBY)
        _managedInstance->SortBy = AimpConverter::ToManagedString(static_cast<IAIMPString*>(Value));

    if (PropertyID == AIMPML_FILTER_SEARCHSTRING)
        _managedInstance->SearchString = AimpConverter::ToManagedString(static_cast<IAIMPString*>(Value));

    return S_OK;
}

ULONG WINAPI InternalAimpDataFilter::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI InternalAimpDataFilter::Release(void) {
    return Base::Release();
}

HRESULT WINAPI InternalAimpDataFilter::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPMLDataFilter) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}
