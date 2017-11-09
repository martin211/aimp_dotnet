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
#include "AimpExtensionPlaylistManagerListener.h"


AimpExtensionPlaylistManagerListener::AimpExtensionPlaylistManagerListener(gcroot<IAimpExtensionPlaylistManagerListener^> instance)
{
    _managedInstance = instance;
}

void WINAPI AimpExtensionPlaylistManagerListener::PlaylistActivated(IAIMPPlaylist* Playlist)
{
    //_managedInstance->On();
    //System::Diagnostics::Debugger::Break();
}

void WINAPI AimpExtensionPlaylistManagerListener::PlaylistAdded(IAIMPPlaylist* Playlist)
{
    System::Diagnostics::Debugger::Break();
}

void WINAPI AimpExtensionPlaylistManagerListener::PlaylistRemoved(IAIMPPlaylist* Playlist)
{
    System::Diagnostics::Debugger::Break();
}

HRESULT WINAPI AimpExtensionPlaylistManagerListener::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionPlaylistManagerListener) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    ppvObject = NULL;
    return res;
}

ULONG WINAPI AimpExtensionPlaylistManagerListener::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI AimpExtensionPlaylistManagerListener::Release(void)
{
    return Base::Release();
}
