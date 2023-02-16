//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpExtensionPlaylistManagerListener.h"
#include "AimpPlayList.h"

AimpExtensionPlaylistManagerListener::AimpExtensionPlaylistManagerListener(
    gcroot<IAimpExtensionPlaylistManagerListener^> instance) {
    _managedInstance = instance;
}

void WINAPI AimpExtensionPlaylistManagerListener::PlaylistActivated(IAIMPPlaylist* Playlist) {
    _managedInstance->OnPlaylistActivated(gcnew AimpPlayList(Playlist, false));
}

void WINAPI AimpExtensionPlaylistManagerListener::PlaylistAdded(IAIMPPlaylist* Playlist) {
    _managedInstance->OnPlaylistAdded(gcnew AimpPlayList(Playlist, false));
}

void WINAPI AimpExtensionPlaylistManagerListener::PlaylistRemoved(IAIMPPlaylist* Playlist) {
    _managedInstance->OnPlaylistRemoved(gcnew AimpPlayList(Playlist, false));
}

HRESULT WINAPI AimpExtensionPlaylistManagerListener::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionPlaylistManagerListener) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    ppvObject = nullptr;
    return res;
}

ULONG WINAPI AimpExtensionPlaylistManagerListener::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI AimpExtensionPlaylistManagerListener::Release(void) {
    return Base::Release();
}
