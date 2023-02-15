//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpDataFilterGroup.h"

#include "InternalDataFieldFilter.h"
#include "DataFilter/InternalAimpDataFieldFilterByArray.h"

using namespace AIMP::SDK;
using namespace MusicLibrary;
using namespace DataFilter;

InternalAimpDataFilterGroup::InternalAimpDataFilterGroup(gcroot<IAimpDataFilterGroup^> managed) {
    _managed = managed;
}

HRESULT WINAPI InternalAimpDataFilterGroup::Add(IUnknown* Field, VARIANT* Value1, VARIANT* Value2, int Operation,
                                                IAIMPMLDataFieldFilter** Filter) {
    IAimpDataFieldFilter^ filter = nullptr;
    auto result = _managed->Add(AimpConverter::ToManagedString(static_cast<IAIMPString*>(Field)),
                                AimpConverter::FromVariant(Value1), AimpConverter::FromVariant(Value2),
                                FieldFilterOperationType(Operation));

    if (result->ResultType == ActionResultType::OK) {
        // todo implement internal IAIMPMLDataFieldFilter
    }

    return HRESULT(result->ResultType);
}

HRESULT WINAPI InternalAimpDataFilterGroup::Add2(IUnknown* Field, VARIANT* Values, int Count,
                                                 IAIMPMLDataFieldFilterByArray** Filter) {
    array<Object^>^ values = gcnew array<Object^>(Count);
    IAimpDataFieldFilterByArray^ filter;
    auto result = _managed->Add(AimpConverter::ToManagedString(static_cast<IAIMPString*>(Field)), values, Count);

    if (result->ResultType == ActionResultType::OK) {
        // todo implement IAIMPMLDataFieldFilterByArray
    }

    return HRESULT(result->ResultType);
}

HRESULT WINAPI InternalAimpDataFilterGroup::AddGroup(IAIMPMLDataFilterGroup** Group) {
    auto result = _managed->AddGroup();
    if (result->ResultType == ActionResultType::OK) {
        *Group = new InternalAimpDataFilterGroup(result->Result);
    }

    return HRESULT(result->ResultType);
}

HRESULT WINAPI InternalAimpDataFilterGroup::Clear() {
    return HRESULT(_managed->Clear()->ResultType);
}

HRESULT WINAPI InternalAimpDataFilterGroup::Delete(int Index) {
    return HRESULT(_managed->Delete(Index)->ResultType);
}

HRESULT WINAPI InternalAimpDataFilterGroup::GetChild(int Index, REFIID IID, void** Obj) {
    ActionResultType res = ActionResultType::Fail;
    if (IID == IID_IAIMPMLDataFieldFilter) {
        const auto result = _managed->GetChild<IAimpDataFieldFilter^>(Index);

        if (result->ResultType == ActionResultType::OK) {
            *Obj = new InternalDataFieldFilter(result->Result);
        }

        res = result->ResultType;
    }

    if (IID == IID_IAIMPMLDataFieldFilter) {
        IAimpDataFieldFilter^ filter = nullptr;
        const auto result = _managed->GetChild<IAimpDataFieldFilterByArray^>(Index);

        if (result->ResultType == ActionResultType::OK) {
            *Obj = new InternalAimpDataFieldFilterByArray(result->Result);
        }

        res = result->ResultType;
    }

    return HRESULT(res);
}

int WINAPI InternalAimpDataFilterGroup::GetChildCount() {
    return _managed->GetChildCount();
}

ULONG WINAPI InternalAimpDataFilterGroup::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI InternalAimpDataFilterGroup::Release(void) {
    return Base::Release();
}

HRESULT WINAPI InternalAimpDataFilterGroup::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    const HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPMLDataFilterGroup) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}

HRESULT WINAPI InternalAimpDataFilterGroup::GetValueAsInt32(int PropertyID, int* Value) {
    if (PropertyID == AIMPML_FILTERGROUP_OPERATION)
        *Value = static_cast<int>(_managed->Operation);

    return S_OK;
}

HRESULT WINAPI InternalAimpDataFilterGroup::SetValueAsInt32(int PropertyID, int Value) {
    if (PropertyID == AIMPML_FILTERGROUP_OPERATION)
        _managed->Operation = static_cast<FilterGroupOperationType>(Value);

    return S_OK;
}
