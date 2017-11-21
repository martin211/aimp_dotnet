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

#pragma once

//public interface class IAimpExtensionPlaylistManagerListenerExecutor
//{
//    void OnPlaylistActivated(IAIMPPlaylist* playlist);
//    void OnPlaylistAdded(IAIMPPlaylist* playlist);
//    void OnPlaylistRemoved(IAIMPPlaylist* playlist);
//};

using namespace AIMP::SDK::Playlist;

class AimpExtensionPlaylistManagerListener : public IUnknownInterfaceImpl<IAIMPExtensionPlaylistManagerListener>
{
private:
    gcroot<IAimpExtensionPlaylistManagerListener^> _managedInstance;

public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionPlaylistManagerListener> Base;

    AimpExtensionPlaylistManagerListener(gcroot<IAimpExtensionPlaylistManagerListener^> instance);

    virtual void WINAPI PlaylistActivated(IAIMPPlaylist* Playlist);

    virtual void WINAPI PlaylistAdded(IAIMPPlaylist* Playlist);

    virtual void WINAPI PlaylistRemoved(IAIMPPlaylist* Playlist);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
