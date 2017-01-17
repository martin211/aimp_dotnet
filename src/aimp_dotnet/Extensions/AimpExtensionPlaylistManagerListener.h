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

    AimpExtensionPlaylistManagerListener(gcroot<IAimpExtensionPlaylistManagerListenerExecutor^> instance)
    {
        _managedInstance = instance;
    }

    virtual void WINAPI PlaylistActivated(IAIMPPlaylist* Playlist)
    {
        _managedInstance->OnPlaylistActivated(Playlist);
    }

    virtual void WINAPI PlaylistAdded(IAIMPPlaylist* Playlist)
    {
        _managedInstance->OnPlaylistAdded(Playlist);
    }

    virtual void WINAPI PlaylistRemoved(IAIMPPlaylist* Playlist)
    {
        _managedInstance->OnPlaylistRemoved(Playlist);
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (!ppvObject)
        {
            return E_POINTER;
        }

        if (riid == IID_IAIMPExtensionPlaylistManagerListener) {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }
};
