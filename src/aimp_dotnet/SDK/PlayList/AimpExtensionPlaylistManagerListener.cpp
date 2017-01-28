/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#include "Stdafx.h"
#include "AimpExtensionPlaylistManagerListener.h"


AimpExtensionPlaylistManagerListener::AimpExtensionPlaylistManagerListener(gcroot<IAimpExtensionPlaylistManagerListenerExecutor^> instance)
{
    _managedInstance = instance;
}

void WINAPI AimpExtensionPlaylistManagerListener::PlaylistActivated(IAIMPPlaylist* Playlist)
{
    _managedInstance->OnPlaylistActivated(Playlist);
}

void WINAPI AimpExtensionPlaylistManagerListener::PlaylistAdded(IAIMPPlaylist* Playlist)
{
    _managedInstance->OnPlaylistAdded(Playlist);
}

void WINAPI AimpExtensionPlaylistManagerListener::PlaylistRemoved(IAIMPPlaylist* Playlist)
{
    _managedInstance->OnPlaylistRemoved(Playlist);
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
