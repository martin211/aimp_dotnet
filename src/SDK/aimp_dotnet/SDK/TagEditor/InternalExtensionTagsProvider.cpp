//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "stdafx.h"
#include "InternalExtensionTagsProvider.h"

#include "SDK/AimpErrorInfo.h"
#include "SDK/AimpObjectList.h"
#include "SDK/FileManager/AimpFileInfo.h"
#include "SDK/Threading/AimpTaskOwner.h"

HRESULT InternalExtensionTagsProvider::GetName(IAIMPString** source) {
    const auto result = _managed->GetName();

    if (result->ResultType == ActionResultType::OK) {
        auto str = AimpConverter::ToAimpString(result->Result);
        *source = str;
    }

    return static_cast<HRESULT>(result->ResultType);
}

HRESULT InternalExtensionTagsProvider::GetSupportedFields(int* fields, int* count) {
    const auto result = _managed->GetSupportedFields();

    if (result->ResultType == ActionResultType::OK) {

    }

    return static_cast<HRESULT>(result->ResultType);
}

HRESULT InternalExtensionTagsProvider::FindAlbums(IAIMPString* query, IAIMPTaskOwner* owner, IAIMPErrorInfo* errorInfo,
    TAIMPServiceFindTagsOnlineAlbumInfoReceiveProc* receiveProc, void* receiveProcData) {
    const auto result = _managed->FindAlbums(
        AimpConverter::ToManagedString(query),
        gcnew AimpTaskOwner(owner),
        gcnew AimpErrorInfo(errorInfo),
        nullptr,
        AimpConverter::ToManagedString(static_cast<IAIMPString*>(receiveProcData)));

    return static_cast<HRESULT>(result->ResultType);
}

HRESULT InternalExtensionTagsProvider::FindTracks(IAIMPFileInfo* albumInfo, IAIMPTaskOwner* owner,
    IAIMPErrorInfo* errorInfo, IAIMPObjectList** tracksInfo) {
    //const auto result = _managed->FindTracks(
    //    gcnew AimpFileInfo(albumInfo),
    //    gcnew AimpTaskOwner(owner),
    //    gcnew AimpErrorInfo(errorInfo));

    //if (result->ResultType == ActionResultType::OK) {
    //    //*tracksInfo = ((AimpObjectList<IAimpFileInfo^ >> ^)result->Result).AimpObject;
    //}

    //return static_cast<HRESULT>(result->ResultType);

    return S_OK;
}

HRESULT InternalExtensionTagsProvider::QueryInterface(const IID& riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionTagsProvider) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}

ULONG InternalExtensionTagsProvider::AddRef() {
    return Base::AddRef();
}

ULONG InternalExtensionTagsProvider::Release() {
    return Base::Release();
}
