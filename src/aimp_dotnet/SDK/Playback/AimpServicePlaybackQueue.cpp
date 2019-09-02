// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServicePlaybackQueue.h"
#include "AimpPlaybackQueueItem.h"

using namespace AIMP::SDK;
using namespace Playlist;
using namespace Playback;

AimpServicePlaybackQueue::
AimpServicePlaybackQueue(ManagedAimpCore^ core) : BaseAimpService<IAIMPServicePlaybackQueue>(core)
{
}

IAimpPlaybackQueueItem^ AimpServicePlaybackQueue::GetNextTrack()
{
    IAIMPPlaybackQueueItem* item = nullptr;
    IAIMPServicePlaybackQueue* service = GetAimpService();
    try
    {
        if (service != nullptr)
        {
            if (CheckResult(service->GetNextTrack(&item)) == AimpActionResult::OK)
            {
                return gcnew AimpPlaybackQueueItem(item);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(item);
    }

    return nullptr;
}

IAimpPlaybackQueueItem^ AimpServicePlaybackQueue::GetPrevTrack()
{
    IAIMPPlaybackQueueItem* item = nullptr;
    IAIMPServicePlaybackQueue* service = GetAimpService();

    try
    {
        if (service != nullptr)
        {
            if (CheckResult(service->GetPrevTrack(&item)) == AimpActionResult::OK)
            {
                return gcnew AimpPlaybackQueueItem(item);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(item);
    }

    return nullptr;
}

void AimpServicePlaybackQueue::OnCheckURL::add(AimpCheckUrl^ onEvent)
{
    const bool tmp = _checkUrlHandler == nullptr;
    if (tmp)
    {
        _checkUrlHandler = static_cast<AimpCheckUrl^>(Delegate::Combine(_checkUrlHandler, onEvent));
    }
}

void AimpServicePlaybackQueue::OnCheckURL::remove(AimpCheckUrl^ onEvent)
{
    const bool tmp = _checkUrlHandler != nullptr;
    if (tmp)
    {
        _checkUrlHandler = static_cast<AimpCheckUrl^>(Delegate::Remove(_checkUrlHandler, onEvent));
    }
}

bool AimpServicePlaybackQueue::RaiseCheckUrl(String^% url)
{
    const bool tmp = this->_checkUrlHandler != nullptr;
    if (tmp)
    {
        return _checkUrlHandler(url);
    }

    return false;
}

IAIMPServicePlaybackQueue* AimpServicePlaybackQueue::GetAimpService()
{
    IAIMPServicePlaybackQueue* service = nullptr;
    GetService(IID_IAIMPServicePlaybackQueue, &service);
    return service;
}
