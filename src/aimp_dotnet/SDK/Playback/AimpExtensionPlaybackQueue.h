#pragma once

class AimpExtensionPlaybackQueue :
    public IUnknownInterfaceImpl<IAIMPExtensionPlaybackQueue>
{
private:
    gcroot<Playback::IAimpExtensionPlaybackQueue^> _managed;
public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionPlaybackQueue> Base;

    explicit AimpExtensionPlaybackQueue(gcroot<Playback::IAimpExtensionPlaybackQueue^> extension);

    virtual BOOL WINAPI GetNext(IUnknown* current, DWORD flags, IAIMPPlaybackQueueItem* queueItem);

    virtual BOOL WINAPI GetPrev(IUnknown* current, DWORD flags, IAIMPPlaybackQueueItem* queueItem);

    virtual void WINAPI OnSelect(IAIMPPlaylistItem* item, IAIMPPlaybackQueueItem* queueItem);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
