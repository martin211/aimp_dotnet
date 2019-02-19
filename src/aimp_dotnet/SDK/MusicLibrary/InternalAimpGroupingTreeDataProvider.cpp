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
#include "InternalAimpGroupingTreeDataProvider.h"

using namespace AIMP::SDK;

InternalAimpGroupingTreeDataProvider::InternalAimpGroupingTreeDataProvider(gcroot<IAimpGroupingTreeDataProvider^> managedInstance)
{
    _managedInstance = managedInstance;
}

HRESULT WINAPI InternalAimpGroupingTreeDataProvider::AppendFilter(IAIMPMLDataFilterGroup* Filter, IAIMPMLGroupingTreeSelection* Selection)
{
    AimpDataFilterGroup^ dataFilterGroup = nullptr;
    IAimpGroupingTreeSelection^ selection = nullptr;

    try
    {
        dataFilterGroup = gcnew AimpDataFilterGroup(Filter);
        selection = gcnew AimpGroupingTreeSelection(Selection);
        _managedInstance->AppendFilter(dataFilterGroup, selection);
    }
    finally
    {
        delete dataFilterGroup;
        delete selection;
    }

    return HRESULT(S_OK);
}

DWORD WINAPI InternalAimpGroupingTreeDataProvider::GetCapabilities()
{
    return DWORD(_managedInstance->GetCapabilities());
}

HRESULT WINAPI InternalAimpGroupingTreeDataProvider::GetData(IAIMPMLGroupingTreeSelection* Selection, IAIMPMLGroupingTreeDataProviderSelection** Data)
{
    IAimpGroupingTreeSelection^ selection = nullptr;
    IAimpGroupingTreeDataProviderSelection^ dataProviderSelection = nullptr;
    AimpActionResult result = AimpActionResult::Fail;


    try
    {
        selection = gcnew AimpGroupingTreeSelection(Selection);
        result = _managedInstance->GetData(selection, dataProviderSelection);

        if (result == AimpActionResult::OK)
        {
            *Data = new InternalAimpGroupingTreeDataProviderSelection(dataProviderSelection);
        }
    }
    finally
    {
    }

    return HRESULT(result);
}

HRESULT WINAPI InternalAimpGroupingTreeDataProvider::GetFieldForAlphabeticIndex(IAIMPString** FieldName)
{
    String^ str;

    AimpActionResult result = _managedInstance->GetFieldForAlphabeticIndex(str);

    if (result == AimpActionResult::OK)
    {
        *FieldName = AimpConverter::ToAimpString(str);
    }

    return HRESULT(result);
}

ULONG WINAPI InternalAimpGroupingTreeDataProvider::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI InternalAimpGroupingTreeDataProvider::Release(void)
{
    return Base::Release();
}

HRESULT WINAPI InternalAimpGroupingTreeDataProvider::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPMLGroupingTreeDataProvider)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    ppvObject = nullptr;
    return E_NOINTERFACE;
}
