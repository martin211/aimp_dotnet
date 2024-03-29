//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpExtensionPlaybackQueue.h"

#include "SDK/Playback/AimpPlaybackQueueItem.h"
#include "SDK/PlayList/AimpPlayList.h"
#include "SDK/PlayList/AimpPlayListItem.h"

AimpExtensionPlaybackQueue::AimpExtensionPlaybackQueue(gcroot<IAimpExtensionPlaybackQueue^> extension) {
    _managed = extension;
}

HRESULT AimpExtensionPlaybackQueue::QueryInterface(const IID& riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionPlaybackQueue) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}

ULONG AimpExtensionPlaybackQueue::AddRef() {
    return Base::AddRef();
}

ULONG AimpExtensionPlaybackQueue::Release() {
    return Base::Release();
}

HRESULT AimpExtensionPlaybackQueue::GetNext(IUnknown* current, DWORD flags, IAIMPPlaybackQueueItem* queueItem) {
    switch (flags) {
    case AIMP_PLAYBACKQUEUE_FLAGS_START_FROM_BEGINNING:
    case AIMP_PLAYBACKQUEUE_FLAGS_START_FROM_CURSOR:
        return static_cast<HRESULT>(_managed->GetNext(gcnew AimpPlayList(static_cast<IAIMPPlaylist*>(current)),
            static_cast<PlaybackQueueFlags>(flags),
            gcnew AimpPlaybackQueueItem(queueItem))->ResultType);
    case AIMP_PLAYBACKQUEUE_FLAGS_START_FROM_ITEM:
        return static_cast<HRESULT>(_managed->GetNext(gcnew AimpPlaylistItem(static_cast<IAIMPPlaylistItem*>(current)),
            static_cast<PlaybackQueueFlags>(flags),
            gcnew AimpPlaybackQueueItem(queueItem))->ResultType);
    }

    return false;
}

HRESULT AimpExtensionPlaybackQueue::GetPrev(IUnknown* current, DWORD flags, IAIMPPlaybackQueueItem* queueItem) {
    switch (flags) {
    case AIMP_PLAYBACKQUEUE_FLAGS_START_FROM_BEGINNING:
    case AIMP_PLAYBACKQUEUE_FLAGS_START_FROM_CURSOR:
    {
        const auto res = _managed->GetPrev(
            gcnew AimpPlayList(static_cast<IAIMPPlaylist*>(current)),
            static_cast<PlaybackQueueFlags>(flags),
            gcnew AimpPlaybackQueueItem(queueItem));

        return static_cast<HRESULT>(res->ResultType);
    }
    case AIMP_PLAYBACKQUEUE_FLAGS_START_FROM_ITEM:
        const auto res = _managed->GetPrev(gcnew AimpPlaylistItem(
            static_cast<IAIMPPlaylistItem*>(current)),
            static_cast<PlaybackQueueFlags>(flags),
            gcnew AimpPlaybackQueueItem(queueItem));

        return static_cast<HRESULT>(res->ResultType);
    }

    return false;
}

void AimpExtensionPlaybackQueue::OnSelect(IAIMPPlaylistItem* item, IAIMPPlaybackQueueItem* queueItem) {
    _managed->OnSelect(gcnew AimpPlaylistItem(item), gcnew AimpPlaybackQueueItem(queueItem));
}
