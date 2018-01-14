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
#include "AimpExtensionAlbumArtCatalog.h"
#include "SDK\FileManager\AimpFileInfo.h"

AimpExtensionAlbumArtCatalog::AimpExtensionAlbumArtCatalog(IAIMPCore *aimpCore, gcroot<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtCatalog^> instance)
{
    _managedinstance = instance;
    _aimpCore = aimpCore;
}

HRESULT WINAPI AimpExtensionAlbumArtCatalog::GetIcon(HICON **Image)
{
    System::Drawing::Bitmap^ bitmap = _managedinstance->GetIcon();
    *Image = static_cast<HICON*>(bitmap->GetHicon().ToPointer());
    return S_OK;
}

HRESULT WINAPI AimpExtensionAlbumArtCatalog::GetName(IAIMPString **Name)
{
    IAIMPString *strObject = AimpConverter::ToAimpString(_managedinstance->GetName());
    *Name = strObject;
    return S_OK;
}

HRESULT WINAPI AimpExtensionAlbumArtCatalog::Show(IAIMPString *FileURI, IAIMPString *Artist, IAIMPString *Album, IAIMPImageContainer **Image)
{
    System::Drawing::Bitmap^ bitmap = nullptr;
    AIMP::AimpActionResult r = _managedinstance->Show(
        AimpConverter::ToManagedString(FileURI),
        AimpConverter::ToManagedString(Artist),
        AimpConverter::ToManagedString(Album),
        bitmap);

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

HRESULT WINAPI AimpExtensionAlbumArtCatalog::Show2(IAIMPFileInfo *FileInfo, IAIMPImageContainer **Image)
{
    System::Drawing::Bitmap^ bitmap = nullptr;
    AIMP::SDK::FileManager::IAimpFileInfo ^fi = gcnew AIMP::SDK::AimpFileInfo(FileInfo);
    AIMP::AimpActionResult r = _managedinstance->Show(fi, bitmap);
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

HRESULT WINAPI AimpExtensionAlbumArtCatalog::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
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

    ppvObject = nullptr;
    return res;
}

ULONG WINAPI AimpExtensionAlbumArtCatalog::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI AimpExtensionAlbumArtCatalog::Release(void)
{
    return Base::Release();
}
