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

InternalAimpGroupingTreeDataProvider::InternalAimpGroupingTreeDataProvider(gcroot<AIMP::SDK::MusicLibrary::DataStorage::IAimpGroupingTreeDataProvider^> managedInstance)
{
    _managedInstance = managedInstance;
    _linkCount = 1;
}

HRESULT WINAPI InternalAimpGroupingTreeDataProvider::AppendFilter(IAIMPMLDataFilterGroup* Filter, IAIMPMLGroupingTreeSelection* Selection)
{
    AimpDataFilterGroup^ dataFilterGroup = nullptr;
    IAimpGroupingTreeSelection^ selection = nullptr;

    try
    {
        dataFilterGroup = gcnew AimpDataFilterGroup(Filter);
        selection = gcnew AimpGroupingTreeSelection(Selection);

        AIMP::SDK::AimpActionResult result = _managedInstance->AppendFilter(dataFilterGroup, selection);
        return (HRESULT)S_OK;
    }
    finally
    {
        delete dataFilterGroup;
        delete selection;
    }
}

DWORD WINAPI InternalAimpGroupingTreeDataProvider::GetCapabilities()
{
    return (DWORD)_managedInstance->GetCapabilities();
}

HRESULT WINAPI InternalAimpGroupingTreeDataProvider::GetData(IAIMPMLGroupingTreeSelection* Selection, IAIMPMLGroupingTreeDataProviderSelection** Data)
{
    IAimpGroupingTreeSelection^ selection = nullptr;
    IAimpGroupingTreeDataProviderSelection^ dataProviderSelection = nullptr;

    try
    {
        selection = gcnew AimpGroupingTreeSelection(Selection);
        AimpActionResult result = _managedInstance->GetData(selection, dataProviderSelection);

        if (result == AimpActionResult::Ok)
        {
            *Data = new InternalAimpGroupingTreeDataProviderSelection(dataProviderSelection);
        }

        return (HRESULT)result;
    }
    finally
    {
    }
}

HRESULT WINAPI InternalAimpGroupingTreeDataProvider::GetFieldForAlphabeticIndex(IAIMPString** FieldName)
{
    System::String^ str;

    AimpActionResult result = _managedInstance->GetFieldForAlphabeticIndex(str);

    if (result == AimpActionResult::Ok)
    {
        *FieldName = AIMP::SDK::AimpConverter::ToAimpString(str);
    }

    return (HRESULT)result;
}

ULONG WINAPI InternalAimpGroupingTreeDataProvider::AddRef(void)
{
    this->_linkCount++;
    return this->_linkCount;
}

ULONG WINAPI InternalAimpGroupingTreeDataProvider::Release(void)
{
    this->_linkCount--;

    if (this->_linkCount == 0)
    {
        delete this;
    }

    return this->_linkCount;
}

HRESULT WINAPI InternalAimpGroupingTreeDataProvider::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    if (!ppvObject)
    {
        return E_POINTER;
    }

    if (riid == IID_IAIMPMLGroupingTreeDataProvider)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}
