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
#include "AimpPlaylistPreimageFactory.h"

AimpPlaylistPreimageFactory::AimpPlaylistPreimageFactory(gcroot<Playlist::IAimpExtensionPlaylistPreimageFactory^> managedObject)
{
    _managedObject = managedObject;
}

HRESULT WINAPI AimpPlaylistPreimageFactory::CreatePreimage(IAIMPPlaylistPreimage** preimage)
{
    return S_OK;
}

HRESULT WINAPI AimpPlaylistPreimageFactory::GetID(IAIMPString** ID)
{
    System::String^ id;
    _managedObject->GetId(id);
    *ID = AimpConverter::ToAimpString(id);
    return S_OK;
}

HRESULT WINAPI AimpPlaylistPreimageFactory::GetName(IAIMPString** Name)
{
    System::String^ name;
    _managedObject->GetName(name);
    *Name = AimpConverter::ToAimpString(name);
    return S_OK;
}

DWORD WINAPI AimpPlaylistPreimageFactory::GetFlags()
{
    return (DWORD)_managedObject->GetFlags();
}

ULONG WINAPI AimpPlaylistPreimageFactory::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI AimpPlaylistPreimageFactory::Release(void)
{
    return Base::Release();
}

HRESULT WINAPI AimpPlaylistPreimageFactory::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionPlaylistPreimageFactory)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = NULL;
    return E_NOINTERFACE;
}
