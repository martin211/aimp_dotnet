#include "Stdafx.h"
#include "InternalAimpGroupingTreeDataProviderSelection.h"

using namespace AIMP::SDK;

InternalAimpGroupingTreeDataProviderSelection::InternalAimpGroupingTreeDataProviderSelection(gcroot<IAimpGroupingTreeDataProviderSelection^> managedInstance)
{
    _managedInstance = managedInstance;
}

HRESULT WINAPI InternalAimpGroupingTreeDataProviderSelection::GetDisplayValue(IAIMPString** S)
{
    String^ str;
    AimpActionResult result = _managedInstance->GetDisplayValue(str);

    if (result == AimpActionResult::Ok)
    {
        *S = AimpConverter::ToAimpString(str);
    }

    return (HRESULT)result;
}

DWORD WINAPI InternalAimpGroupingTreeDataProviderSelection::GetFlags()
{
    return (DWORD)_managedInstance->GetFlags();
}

HRESULT WINAPI InternalAimpGroupingTreeDataProviderSelection::GetImageIndex(int* Index)
{
    FieldImageIndex index;
    AimpActionResult result = _managedInstance->GetImageIndex(index);

    if (result == AimpActionResult::Ok)
    {
        *Index = (int)index;
    }

    return (HRESULT)result;
}

HRESULT WINAPI InternalAimpGroupingTreeDataProviderSelection::GetValue(IAIMPString** FieldName, VARIANT* Value)
{
    String^ fieldName;
    Object^ val;

    AimpActionResult result = _managedInstance->GetValue(fieldName, val);

    if (result == AimpActionResult::Ok)
    {
        *FieldName = AimpConverter::ToAimpString(fieldName);
        VARIANT v = AimpConverter::ToNativeVariant(val);
        VariantCopyInd(Value, &v);
    }

    return (HRESULT)result;
}

BOOL WINAPI InternalAimpGroupingTreeDataProviderSelection::NextRow()
{
    return (BOOL)_managedInstance->NextRow();
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

    *ppvObject = NULL;
    return res;
}
