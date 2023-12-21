//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpPlaylistPreimageFactory.h"

AimpPlaylistPreimageFactory::AimpPlaylistPreimageFactory(gcroot<IAimpExtensionPlaylistPreimageFactory^> managedObject) {
    _managedObject = managedObject;
}

HRESULT WINAPI AimpPlaylistPreimageFactory::CreatePreimage(IAIMPPlaylistPreimage** preimage) {
    return E_NOTIMPL;
}

HRESULT WINAPI AimpPlaylistPreimageFactory::GetID(IAIMPString** ID) {
    const auto result = _managedObject->GetId();
    *ID = AimpConverter::ToAimpString(result->Result);
    return static_cast<HRESULT>(result->ResultType);
}

HRESULT WINAPI AimpPlaylistPreimageFactory::GetName(IAIMPString** Name) {
    const auto result = _managedObject->GetName();
    *Name = AimpConverter::ToAimpString(result->Result);
    return static_cast<HRESULT>(result->ResultType);
}

DWORD WINAPI AimpPlaylistPreimageFactory::GetFlags() {
    return DWORD(_managedObject->GetFlags());
}

ULONG WINAPI AimpPlaylistPreimageFactory::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI AimpPlaylistPreimageFactory::Release(void) {
    return Base::Release();
}

HRESULT WINAPI AimpPlaylistPreimageFactory::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionPlaylistPreimageFactory) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return E_NOINTERFACE;
}
