//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpPlaybackQueueItem.h"
#include "SDK/PlayList/AimpPlayListItem.h"

using namespace AIMP::SDK;

AimpPlaybackQueueItem::AimpPlaybackQueueItem(IAIMPPlaybackQueueItem* aimpItem) : AimpObject(aimpItem) {
}

Object^ AimpPlaybackQueueItem::UserData::get() {
    IUnknown* item = nullptr;
    InternalAimpObject->GetValueAsObject(AIMP_PLAYBACKQUEUEITEM_PROPID_CUSTOM, IID_IUnknown,
                                         reinterpret_cast<void**>(&item));
    return Runtime::InteropServices::Marshal::GetObjectForIUnknown(IntPtr(item));
}

void AimpPlaybackQueueItem::UserData::set(Object^ value) {
    // TODO complete it
    throw gcnew NotImplementedException("Not implemented");
}

IAimpPlaylistItem^ AimpPlaybackQueueItem::PlaylistItem::get() {
    IAIMPPlaylistItem* item = nullptr;
    InternalAimpObject->GetValueAsObject(AIMP_PLAYBACKQUEUEITEM_PROPID_PLAYLISTITEM, IID_IAIMPPlaylistItem,
                                         reinterpret_cast<void**>(&item));
    return gcnew AimpPlaylistItem(item);
}

void AimpPlaybackQueueItem::PlaylistItem::set(IAimpPlaylistItem^ value) {
    InternalAimpObject->SetValueAsObject(AIMP_PLAYBACKQUEUEITEM_PROPID_PLAYLISTITEM,
                                         static_cast<AimpPlaylistItem^>(value)->InternalAimpObject);
}
