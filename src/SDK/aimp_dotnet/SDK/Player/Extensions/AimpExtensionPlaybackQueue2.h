//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "AimpExtensionPlaybackQueue.h"

using namespace Player::Extensions;

class AimpExtensionPlaybackQueue2 :public IUnknownInterfaceImpl<IAIMPExtensionPlaybackQueue2>, AimpExtensionPlaybackQueue {
private:
    gcroot<IAimpExtensionPlaybackQueue2^> _managed;
public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionPlaybackQueue2> Base;
    typedef AimpExtensionPlaybackQueue BaseType;

    explicit AimpExtensionPlaybackQueue2(const gcroot<IAimpExtensionPlaybackQueue2^> extension)
        : AimpExtensionPlaybackQueue(static_cast<IAimpExtensionPlaybackQueue^>(extension)) {
        _managed = extension;
    }

    HRESULT WINAPI GetInfo(IUnknown* Current, int* position, int* size) override;

    HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject) override;

    ULONG WINAPI AddRef(void) override;

    ULONG WINAPI Release(void) override;

    HRESULT WINAPI GetNext(IUnknown* Current, DWORD Flags, IAIMPPlaybackQueueItem* QueueItem) override {
        return BaseType::GetNext(Current, Flags, QueueItem);
    }

    HRESULT WINAPI GetPrev(IUnknown* Current, DWORD Flags, IAIMPPlaybackQueueItem* QueueItem) override {
        return BaseType::GetPrev(Current, Flags, QueueItem);
    }

    void WINAPI OnSelect(IAIMPPlaylistItem* Item, IAIMPPlaybackQueueItem* QueueItem) override {
        return BaseType::OnSelect(Item, QueueItem);
    }
};