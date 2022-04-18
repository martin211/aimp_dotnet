// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpExtensionAlbumArtProvider.h"
#include "SDK\FileManager\AimpFileInfo.h"
#include "SDK\AlbumArt\AimpAlbumArtSearchOptions.h"

HRESULT WINAPI AimpExtensionAlbumArtProvider::Get(IAIMPString* FileURI, IAIMPString* Artist, IAIMPString* Album,
                                                  IAIMPPropertyList* Options, IAIMPImageContainer** Image) {
    IAimpAlbumArtSearchOptions^ searchOptions = gcnew AimpAlbumArtSearchOptions(Options);
    const auto r = _managedinstance->Get(
        gcnew String(FileURI->GetData()),
        gcnew String(Artist->GetData()),
        gcnew String(Album->GetData()),
        searchOptions);

    if (r->ResultType == ActionResultType::OK && r->Result != nullptr) {
        const auto container = AimpConverter::ToAimpImageContainer(r->Result);
        if (container == nullptr) {
            return E_UNEXPECTED;
        }

        *Image = container;
        return S_OK;
    }

    return E_FAIL;
}

DWORD WINAPI AimpExtensionAlbumArtProvider::GetCategory() {
    return DWORD(_managedinstance->GetCategory());
}

HRESULT WINAPI AimpExtensionAlbumArtProvider::Get2(IAIMPFileInfo* FileInfo, IAIMPPropertyList* Options,
                                                   IAIMPImageContainer** Image) {
    IAimpFileInfo^ fi = gcnew AimpFileInfo(FileInfo);
    IAimpAlbumArtSearchOptions^ searchOptions = gcnew AimpAlbumArtSearchOptions(Options);
    const auto r = ((IAimpExtensionAlbumArtProvider2^)_managedinstance)->Get(fi, searchOptions);
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
