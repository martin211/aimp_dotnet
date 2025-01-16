//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpGroupingTreeDataProvider.h"

#include "SDK/MusicLibrary/AimpGroupingTreeSelection.h"
#include "SDK/MusicLibrary/DataFilter/AimpDataFilterGroup.h"

namespace AIMP::SDK {
    ref class AimpDataFilterGroup;
}

using namespace AIMP::SDK;

InternalAimpGroupingTreeDataProvider::InternalAimpGroupingTreeDataProvider(
    gcroot<IAimpGroupingTreeDataProvider^> managedInstance) {
    _managedInstance = managedInstance;
}

HRESULT WINAPI InternalAimpGroupingTreeDataProvider::AppendFilter(IAIMPMLDataFilterGroup* Filter,
                                                                  IAIMPMLGroupingTreeSelection* Selection) {
    AimpDataFilterGroup^ dataFilterGroup = nullptr;
    IAimpGroupingTreeSelection^ selection = nullptr;

    try {
        dataFilterGroup = gcnew AimpDataFilterGroup(Filter);
        selection = gcnew AimpGroupingTreeSelection(Selection);
        _managedInstance->AppendFilter(dataFilterGroup, selection);
    }
    finally {
        delete dataFilterGroup;
        delete selection;
    }

    return HRESULT(S_OK);
}

DWORD WINAPI InternalAimpGroupingTreeDataProvider::GetCapabilities() {
    return DWORD(_managedInstance->GetCapabilities());
}

HRESULT WINAPI InternalAimpGroupingTreeDataProvider::GetData(IAIMPMLGroupingTreeSelection* Selection,
                                                             IAIMPMLGroupingTreeDataProviderSelection** Data) {
    ActionResultType result = ActionResultType::Fail;

    try {
        const auto selection = gcnew AimpGroupingTreeSelection(Selection);
        const auto dataResult = _managedInstance->GetData(selection);
        result = dataResult->ResultType;

        if (result == ActionResultType::OK) {
            *Data = new InternalAimpGroupingTreeDataProviderSelection(dataResult->Result);
        }
    }
    finally {
    }

    return HRESULT(result);
}

HRESULT WINAPI InternalAimpGroupingTreeDataProvider::GetFieldForAlphabeticIndex(IAIMPString** FieldName) {
    auto result = _managedInstance->GetFieldForAlphabeticIndex();
    if (result->ResultType == ActionResultType::OK) {
        *FieldName = AimpConverter::ToAimpString(result->Result);
    }

    return HRESULT(result->ResultType);
}

ULONG WINAPI InternalAimpGroupingTreeDataProvider::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI InternalAimpGroupingTreeDataProvider::Release(void) {
    return Base::Release();
}

HRESULT WINAPI InternalAimpGroupingTreeDataProvider::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPMLGroupingTreeDataProvider) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    ppvObject = nullptr;
    return res;
}
