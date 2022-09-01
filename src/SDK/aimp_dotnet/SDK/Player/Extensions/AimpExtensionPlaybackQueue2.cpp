//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "stdafx.h"

#include "AimpExtensionPlaybackQueue2.h"
#include "SDK/PlayList/AimpPlayListItem.h"


AimpExtensionPlaybackQueue2::AimpExtensionPlaybackQueue2(gcroot<IAimpExtensionPlaybackQueue2^> extension) {
    _managed = extension;
}

HRESULT AimpExtensionPlaybackQueue2::GetInfo(IUnknown* Current, int* position, int* size) {
    const auto item = gcnew AimpPlaylistItem(dynamic_cast<IAIMPPlaylistItem*>(Current));
    const auto result = _managed->GetInfo(item);

    if (result->ResultType == ActionResultType::OK) {
        *position = result->Result->Position;
        *size = result->Result->Size;
    }

    return static_cast<HRESULT>(result->ResultType);
}

HRESULT AimpExtensionPlaybackQueue2::QueryInterface(const IID& riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPServicePlaybackQueue2) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}

ULONG AimpExtensionPlaybackQueue2::AddRef() {
    return Base::AddRef();
}

ULONG AimpExtensionPlaybackQueue2::Release() {
    return Base::Release();
}
