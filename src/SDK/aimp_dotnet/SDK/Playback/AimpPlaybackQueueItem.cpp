//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
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

double AimpPlaybackQueueItem::Offset::get() {
    double val = 0;
    const auto res = Utils::CheckResult(InternalAimpObject->GetValueAsFloat(AIMP_PLAYBACKQUEUEITEM_PROPID_OFFSET, &val));

    if (res == ActionResultType::OK)
        return val;

    return val;
}

void AimpPlaybackQueueItem::Offset::set(double offset) {
    const auto res = Utils::CheckResult(InternalAimpObject->SetValueAsFloat(AIMP_PLAYBACKQUEUEITEM_PROPID_OFFSET, offset));

    if (res != ActionResultType::OK)
        throw gcnew AimpActionException(res, "Unable to set Offset value");
}

Object^ AimpPlaybackQueueItem::UserData::get() {
    IUnknown* item = nullptr;
    const auto res = Utils::CheckResult(InternalAimpObject->GetValueAsObject(AIMP_PLAYBACKQUEUEITEM_PROPID_CUSTOM, IID_IUnknown, reinterpret_cast<void**>(&item)));

    if (res != ActionResultType::OK)
        return nullptr;

    return Runtime::InteropServices::Marshal::GetObjectForIUnknown(IntPtr(item));
}

void AimpPlaybackQueueItem::UserData::set(Object^ value) {
    // TODO complete it
    throw gcnew NotImplementedException("Not implemented");
}

IAimpPlaylistItem^ AimpPlaybackQueueItem::PlaylistItem::get() {
    IAIMPPlaylistItem* item = nullptr;
    const auto res = Utils::CheckResult(InternalAimpObject->GetValueAsObject(AIMP_PLAYBACKQUEUEITEM_PROPID_PLAYLISTITEM, IID_IAIMPPlaylistItem, reinterpret_cast<void**>(&item)));

    if (res != ActionResultType::OK)
        return nullptr;

    return gcnew AimpPlaylistItem(item);
}

void AimpPlaybackQueueItem::PlaylistItem::set(IAimpPlaylistItem^ value) {
    const auto res = Utils::CheckResult(InternalAimpObject->SetValueAsObject(AIMP_PLAYBACKQUEUEITEM_PROPID_PLAYLISTITEM, static_cast<AimpPlaylistItem^>(value)->InternalAimpObject));

    if (res != ActionResultType::OK)
        throw gcnew AimpActionException(res, "Unable to set PlaylistItem");
}
