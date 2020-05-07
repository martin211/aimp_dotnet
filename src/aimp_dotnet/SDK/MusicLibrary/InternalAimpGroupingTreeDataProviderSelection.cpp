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
#include "InternalAimpGroupingTreeDataProviderSelection.h"

using namespace AIMP::SDK;

InternalAimpGroupingTreeDataProviderSelection::InternalAimpGroupingTreeDataProviderSelection(
    gcroot<IAimpGroupingTreeDataProviderSelection^> managedInstance)
{
    _managedInstance = managedInstance;
}

HRESULT WINAPI InternalAimpGroupingTreeDataProviderSelection::GetDisplayValue(IAIMPString** S)
{
    String^ str;
    ActionResultType result = _managedInstance->GetDisplayValue(str);

    if (result == ActionResultType::OK)
    {
        *S = AimpConverter::ToAimpString(str);
    }

    return HRESULT(result);
}

DWORD WINAPI InternalAimpGroupingTreeDataProviderSelection::GetFlags()
{
    return DWORD(_managedInstance->GetFlags());
}

HRESULT WINAPI InternalAimpGroupingTreeDataProviderSelection::GetImageIndex(int* Index)
{
    FieldImageIndex index;
    ActionResultType result = _managedInstance->GetImageIndex(index);

    if (result == ActionResultType::OK)
    {
        *Index = int(index);
    }

    return HRESULT(result);
}

HRESULT WINAPI InternalAimpGroupingTreeDataProviderSelection::GetValue(IAIMPString** FieldName, VARIANT* Value)
{
    String^ fieldName;
    Object^ val;

    ActionResultType result = _managedInstance->GetValue(fieldName, val);

    if (result == ActionResultType::OK)
    {
        *FieldName = AimpConverter::ToAimpString(fieldName);
        VARIANT v = AimpConverter::ToNativeVariant(val);
        VariantCopyInd(Value, &v);
    }

    return HRESULT(result);
}

BOOL WINAPI InternalAimpGroupingTreeDataProviderSelection::NextRow()
{
    return BOOL(_managedInstance->NextRow());
}

ULONG WINAPI InternalAimpGroupingTreeDataProviderSelection::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI InternalAimpGroupingTreeDataProviderSelection::Release(void)
{
    return Base::Release();
}

HRESULT WINAPI InternalAimpGroupingTreeDataProviderSelection::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPMLGroupingTreeDataProviderSelection)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}
