/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#include "Stdafx.h"
#include "AimpExtensionAlbumArtProvider.h"
#include "..\FileManager\AimpFileInfo.h"
#include "..\AlbumArt\AimpAlbumArtSearchOptions.h"

HRESULT WINAPI AimpExtensionAlbumArtProvider::Get(IAIMPString *FileURI, IAIMPString *Artist, IAIMPString *Album, IAIMPPropertyList *Options, IAIMPImageContainer **Image)
{
    System::Drawing::Bitmap ^bitmap;
    AIMP::SDK::AlbumArtManager::IAimpAlbumArtSearchOptions ^searchOptions = gcnew AIMP::SDK::AimpAlbumArtSearchOptions(Options, AIMP::SDK::ManagedAimpCore::GetAimpCore());
    AIMP::AimpActionResult r = _managedinstance->Get(
        gcnew System::String(FileURI->GetData()),
        gcnew System::String(Artist->GetData()),
        gcnew System::String(Album->GetData()),
        searchOptions,
        bitmap);
    {
        IAIMPImageContainer *container = AIMP::SDK::AimpConverter::ToAimpImageContainer(bitmap);
        if (container == NULL)
        {
            return E_UNEXPECTED;
        }

        *Image = container;
        return S_OK;
    }

    return E_UNEXPECTED;
}

DWORD WINAPI AimpExtensionAlbumArtProvider::GetCategory()
{
    return (DWORD)_managedinstance->GetCategory();
}

HRESULT WINAPI AimpExtensionAlbumArtProvider::Get2(IAIMPFileInfo *FileInfo, IAIMPPropertyList *Options, IAIMPImageContainer **Image)
{
    System::Drawing::Bitmap^ bitmap;
    AIMP::SDK::FileManager::IAimpFileInfo ^fi = gcnew AIMP::SDK::AimpFileInfo(FileInfo);
    AIMP::SDK::AlbumArtManager::IAimpAlbumArtSearchOptions ^searchOptions = gcnew AIMP::SDK::AimpAlbumArtSearchOptions(Options, AIMP::SDK::ManagedAimpCore::GetAimpCore());
    AIMP::AimpActionResult r = _managedinstance->Get(fi, searchOptions, bitmap);
    if (r == AIMP::AimpActionResult::Ok && bitmap != nullptr)
    {
        IAIMPImageContainer *container = AIMP::SDK::AimpConverter::ToAimpImageContainer(bitmap);
        if (container == NULL)
        {
            return E_UNEXPECTED;
        }

        *Image = container;
        return S_OK;
    }

    return E_UNEXPECTED;
}
