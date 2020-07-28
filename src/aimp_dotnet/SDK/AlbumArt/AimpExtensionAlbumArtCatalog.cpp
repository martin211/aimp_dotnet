// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpExtensionAlbumArtCatalog.h"
#include "SDK\FileManager\AimpFileInfo.h"

AimpExtensionAlbumArtCatalog::AimpExtensionAlbumArtCatalog(IAIMPCore* aimpCore,
                                                           gcroot<AlbumArtManager::IAimpExtensionAlbumArtCatalog^>
                                                           instance) {
    _managedinstance = instance;
    _aimpCore = aimpCore;
}

HRESULT WINAPI AimpExtensionAlbumArtCatalog::GetIcon(HICON** Image) {
    const auto result = _managedinstance->GetIcon();
    if (result->ResultType == ActionResultType::OK) {
        *Image = static_cast<HICON*>(result->Result->GetHicon().ToPointer());
    }

    return HRESULT(result->ResultType);
}

HRESULT WINAPI AimpExtensionAlbumArtCatalog::GetName(IAIMPString** Name) {
    const auto result = _managedinstance->GetName();

    if (result->ResultType == ActionResultType::OK) {
        IAIMPString* strObject = AimpConverter::ToAimpString(result->Result);
        *Name = strObject;
    }

    return HRESULT(result->ResultType);
}

HRESULT WINAPI AimpExtensionAlbumArtCatalog::Show(IAIMPString* FileURI, IAIMPString* Artist, IAIMPString* Album,
                                                  IAIMPImageContainer** Image) {
    auto r = _managedinstance->Show(
        AimpConverter::ToManagedString(FileURI),
        AimpConverter::ToManagedString(Artist),
        AimpConverter::ToManagedString(Album));

    if (r->ResultType == ActionResultType::OK && r->Result != nullptr) {
        const auto container = AimpConverter::ToAimpImageContainer(r->Result);
        if (container == nullptr) {
            return E_UNEXPECTED;
        }

        *Image = container;
        return S_OK;
    }

    return E_UNEXPECTED;
}

HRESULT WINAPI AimpExtensionAlbumArtCatalog::Show2(IAIMPFileInfo* FileInfo, IAIMPImageContainer** Image) {
    IAimpFileInfo^ fi = gcnew AimpFileInfo(FileInfo);
    auto r = _managedinstance->Show(fi);
    if (r->ResultType == ActionResultType::OK && r->Result != nullptr) {
        IAIMPImageContainer* container = AimpConverter::ToAimpImageContainer(r->Result);
        if (container == nullptr) {
            return E_UNEXPECTED;
        }

        *Image = container;
        return S_OK;
    }

    return E_UNEXPECTED;
}

HRESULT WINAPI AimpExtensionAlbumArtCatalog::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionAlbumArtCatalog) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }
    if (riid == IID_IAIMPExtensionAlbumArtCatalog2) {
        *ppvObject = static_cast<IAIMPExtensionAlbumArtCatalog2*>(this);
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}

ULONG WINAPI AimpExtensionAlbumArtCatalog::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI AimpExtensionAlbumArtCatalog::Release(void) {
    return Base::Release();
}
