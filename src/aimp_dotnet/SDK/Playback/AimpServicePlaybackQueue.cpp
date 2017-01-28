/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#include "Stdafx.h"
#include "AimpServicePlaybackQueue.h"

using namespace AIMP::SDK;
using namespace AIMP::SDK::PlayList;
using namespace AIMP::SDK::Playback;

AimpServicePlaybackQueue::AimpServicePlaybackQueue(ManagedAimpCore ^core) : AimpBaseManager<IAIMPServicePlaybackQueue>(core)
{

}

IAimpPlaybackQueueItem^ AimpServicePlaybackQueue::GetNextTrack()
{
    IAIMPPlaybackQueueItem *item = NULL;
    IAIMPServicePlaybackQueue *service = NULL;
    try
    {
        if (CheckResult(_core->GetService(IID_IAIMPServicePlaybackQueue, (void**)&service)) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                if (CheckResult(service->GetNextTrack(&item)) == AimpActionResult::Ok)
                {
                    return gcnew AimpPlaybackQueueItem(item);
                }
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }

        if (item != NULL)
        {
            item->Release();
            item = NULL;
        }
    }

    return nullptr;
}

IAimpPlaybackQueueItem^ AimpServicePlaybackQueue::GetPrevTrack()
{
    IAIMPPlaybackQueueItem *item = NULL;
    IAIMPServicePlaybackQueue *service = NULL;

    try
    {
        if (CheckResult(_core->GetService(IID_IAIMPServicePlaybackQueue, (void**)&service)) == AimpActionResult::Ok)
        {
            if (service == NULL)
            {
                return nullptr;
            }

            if (CheckResult(service->GetPrevTrack(&item)) == AimpActionResult::Ok)
            {
                return gcnew AimpPlaybackQueueItem(item);
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }

        if (item != NULL)
        {
            item->Release();
            item = NULL;
        }
    }

    return nullptr;
}

void AimpServicePlaybackQueue::OnCheckURL::add(AimpCheckUrl ^onEvent)
{
    bool tmp = _checkUrlHandler == nullptr;
    if (tmp)
    {
        _checkUrlHandler = (AimpCheckUrl^)System::Delegate::Combine(_checkUrlHandler, onEvent);
    }
}

void AimpServicePlaybackQueue::OnCheckURL::remove(AimpCheckUrl ^onEvent)
{
    bool tmp = _checkUrlHandler != nullptr;
    if (tmp)
    {
        _checkUrlHandler = (AimpCheckUrl^)System::Delegate::Remove(_checkUrlHandler, onEvent);
    }
}

bool AimpServicePlaybackQueue::RaiseCheckUrl(String^ %url)
{
    bool tmp = this->_checkUrlHandler != nullptr;
    if (tmp)
    {
        return _checkUrlHandler(url);
    }

    return false;
}
