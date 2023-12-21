//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpExtensionPlaylistPreimageFactory.h"
#include "InternalAimpPlaylistPreimage.h"
#include "SDK/Threading/AimpTaskOwner.h"
#include "InternalAimpMLPlaylistPreimage.h"

using namespace AIMP::SDK;

InternalAimpExtensionPlaylistPreimageFactory::InternalAimpExtensionPlaylistPreimageFactory(
    gcroot<IAimpExtensionPlaylistPreimageFactory^> managedInstance) {
    _managedInstance = managedInstance;
}

HRESULT InternalAimpExtensionPlaylistPreimageFactory::CreatePreimage(IAIMPPlaylistPreimage** preimage) {
    IAimpPlaylistPreimage^ preImage = nullptr;

    const auto res = _managedInstance->CreatePreimage();
    const auto mlPreimage = dynamic_cast<MusicLibrary::IAimpMusicLibraryPlaylistPreimage^>(res->Result);
    if (mlPreimage != nullptr) {
        *preimage = new InternalAimpMLPlaylistPreimage(mlPreimage);
    }
    else {
        *preimage = new InternalAimpPlaylistPreimage(preImage);
    }

    return HRESULT(res->ResultType);
}

HRESULT WINAPI InternalAimpExtensionPlaylistPreimageFactory::GetID(IAIMPString** ID) {
    const auto res = _managedInstance->GetId();
    if (res->ResultType == ActionResultType::OK) {
        *ID = AimpConverter::ToAimpString(res->Result);
    }

    return HRESULT(res->ResultType);
}

HRESULT WINAPI InternalAimpExtensionPlaylistPreimageFactory::GetName(IAIMPString** Name) {
    const auto res = _managedInstance->GetName();
    if (res->ResultType == ActionResultType::OK) {
        *Name = AimpConverter::ToAimpString(res->Result);
    }

    return HRESULT(res->ResultType);
}

DWORD WINAPI InternalAimpExtensionPlaylistPreimageFactory::GetFlags() {
    return DWORD(_managedInstance->GetFlags());
}

ULONG WINAPI InternalAimpExtensionPlaylistPreimageFactory::Release(void) {
    return Base::Release();
}

ULONG WINAPI InternalAimpExtensionPlaylistPreimageFactory::AddRef(void) {
    return Base::AddRef();
}

HRESULT WINAPI InternalAimpExtensionPlaylistPreimageFactory::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionPlaylistPreimageFactory) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPPlaylistPreimageDataProvider) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}
