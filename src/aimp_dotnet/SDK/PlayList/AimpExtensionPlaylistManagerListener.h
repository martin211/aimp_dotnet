/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#pragma once

public interface class IAimpExtensionPlaylistManagerListenerExecutor
{
    void OnPlaylistActivated(IAIMPPlaylist* playlist);
    void OnPlaylistAdded(IAIMPPlaylist* playlist);
    void OnPlaylistRemoved(IAIMPPlaylist* playlist);
};


class AimpExtensionPlaylistManagerListener : public IUnknownInterfaceImpl<IAIMPExtensionPlaylistManagerListener>
{
private:
    gcroot<IAimpExtensionPlaylistManagerListenerExecutor^> _managedInstance;

public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionPlaylistManagerListener> Base;

    AimpExtensionPlaylistManagerListener(gcroot<IAimpExtensionPlaylistManagerListenerExecutor^> instance);

    virtual void WINAPI PlaylistActivated(IAIMPPlaylist* Playlist);

    virtual void WINAPI PlaylistAdded(IAIMPPlaylist* Playlist);

    virtual void WINAPI PlaylistRemoved(IAIMPPlaylist* Playlist);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
