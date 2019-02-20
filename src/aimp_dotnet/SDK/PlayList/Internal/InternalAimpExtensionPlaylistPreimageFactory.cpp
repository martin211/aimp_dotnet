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
#include "InternalAimpExtensionPlaylistPreimageFactory.h"
#include "InternalAimpPlaylistPreimage.h"
#include "SDK/Threading/AimpTaskOwner.h"
#include "InternalAimpMLPlaylistPreimage.h"

using namespace AIMP::SDK;

InternalAimpExtensionPlaylistPreimageFactory::InternalAimpExtensionPlaylistPreimageFactory(gcroot<IAimpExtensionPlaylistPreimageFactory^> managedInstance)
{
    _managedInstance = managedInstance;
}

HRESULT InternalAimpExtensionPlaylistPreimageFactory::CreatePreimage(IAIMPPlaylistPreimage** preimage)
{
    IAimpPlaylistPreimage^ preImage = nullptr;

    AimpActionResult res = _managedInstance->CreatePreimage(preImage);
    const auto mlPreimage = dynamic_cast<MusicLibrary::IAimpMusicLibraryPlaylistPreimage^>(preImage);
    if (mlPreimage != nullptr)
    {
        *preimage = new InternalAimpMLPlaylistPreimage(mlPreimage);
    }
    else
    {
        *preimage = new InternalAimpPlaylistPreimage(preImage);
    }

    return HRESULT(res);
}

HRESULT WINAPI InternalAimpExtensionPlaylistPreimageFactory::GetID(IAIMPString** ID)
{
    System::String^ id;
    AimpActionResult res = _managedInstance->GetId(id);
    if (res == AimpActionResult::OK)
    {
        *ID = AimpConverter::ToAimpString(id);
    }

    return HRESULT(res);
}

HRESULT WINAPI InternalAimpExtensionPlaylistPreimageFactory::GetName(IAIMPString** Name)
{
    String^ name;
    AimpActionResult res = _managedInstance->GetName(name);
    if (res == AimpActionResult::OK)
    {
        *Name = AimpConverter::ToAimpString(name);
    }

    return HRESULT(res);
}

DWORD WINAPI InternalAimpExtensionPlaylistPreimageFactory::GetFlags()
{
    return DWORD(_managedInstance->GetFlags());
}

ULONG WINAPI InternalAimpExtensionPlaylistPreimageFactory::Release(void)
{
    return Base::Release();
}

ULONG WINAPI InternalAimpExtensionPlaylistPreimageFactory::AddRef(void)
{
    return Base::AddRef();
}

HRESULT WINAPI InternalAimpExtensionPlaylistPreimageFactory::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionPlaylistPreimageFactory)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPPlaylistPreimageDataProvider)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}
