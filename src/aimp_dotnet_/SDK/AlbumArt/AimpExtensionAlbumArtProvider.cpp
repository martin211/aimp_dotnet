// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpExtensionAlbumArtProvider.h"
#include "SDK\FileManager\AimpFileInfo.h"
#include "SDK\AlbumArt\AimpAlbumArtSearchOptions.h"

HRESULT WINAPI AimpExtensionAlbumArtProvider::Get(IAIMPString* FileURI, IAIMPString* Artist, IAIMPString* Album,
                                                  IAIMPPropertyList* Options, IAIMPImageContainer** Image)
{
    // todo
    //Drawing::Bitmap^ bitmap;
    //AlbumArtManager::IAimpAlbumArtSearchOptions^ searchOptions = gcnew AimpAlbumArtSearchOptions(
    //    Options, ManagedAimpCore::GetAimpCore());
    //const auto r = _managedinstance->Get(
    //    gcnew String(FileURI->GetData()),
    //    gcnew String(Artist->GetData()),
    //    gcnew String(Album->GetData()),
    //    searchOptions,
    //    bitmap);

    //if (r == AimpActionResult::OK && bitmap != nullptr)
    //{
    //    const auto container = AimpConverter::ToAimpImageContainer(bitmap);
    //    if (container == nullptr)
    //    {
    //        return E_UNEXPECTED;
    //    }

    //    *Image = container;
    //    return S_OK;
    //}

    return E_FAIL;
}

DWORD WINAPI AimpExtensionAlbumArtProvider::GetCategory()
{
    return DWORD(_managedinstance->GetCategory());
}

HRESULT WINAPI AimpExtensionAlbumArtProvider::Get2(IAIMPFileInfo* FileInfo, IAIMPPropertyList* Options,
                                                   IAIMPImageContainer** Image)
{
    //todo
    //Drawing::Bitmap^ bitmap;
    //IAimpFileInfo^ fi = gcnew AimpFileInfo(FileInfo);
    //AlbumArtManager::IAimpAlbumArtSearchOptions^ searchOptions = gcnew AimpAlbumArtSearchOptions(
    //    Options, ManagedAimpCore::GetAimpCore());
    //const auto r = _managedinstance->Get(fi, searchOptions, bitmap);
    //if (r == AimpActionResult::OK && bitmap != nullptr)
    //{
    //    const auto container = AimpConverter::ToAimpImageContainer(bitmap);
    //    if (container == nullptr)
    //    {
    //        return E_UNEXPECTED;
    //    }

    //    *Image = container;
    //    return S_OK;
    //}

    return E_UNEXPECTED;
}
