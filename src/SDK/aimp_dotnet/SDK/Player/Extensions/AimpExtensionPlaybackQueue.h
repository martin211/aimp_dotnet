//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

using namespace Player::Extensions;

class AimpExtensionPlaybackQueue :
    public IUnknownInterfaceImpl<IAIMPExtensionPlaybackQueue> {
private:
    gcroot<IAimpExtensionPlaybackQueue^> _managed;
public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionPlaybackQueue> Base;

    explicit AimpExtensionPlaybackQueue() {
    }

    explicit AimpExtensionPlaybackQueue(gcroot<IAimpExtensionPlaybackQueue^> extension);

    virtual HRESULT WINAPI GetNext(IUnknown* current, DWORD flags, IAIMPPlaybackQueueItem* queueItem);

    virtual HRESULT WINAPI GetPrev(IUnknown* current, DWORD flags, IAIMPPlaybackQueueItem* queueItem);

    virtual void WINAPI OnSelect(IAIMPPlaylistItem* item, IAIMPPlaybackQueueItem* queueItem);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
