//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServicePlaybackQueue.h"
#include "AimpPlaybackQueueItem.h"

using namespace AIMP::SDK;
using namespace Playlist;

AimpServicePlaybackQueue::
AimpServicePlaybackQueue(ManagedAimpCore^ core) : BaseAimpService<IAIMPServicePlaybackQueue>(core) {
}

AimpActionResult<IAimpPlaybackQueueItem^>^ AimpServicePlaybackQueue::GetNextTrack() {
    IAIMPPlaybackQueueItem* aimpItem = nullptr;
    IAIMPServicePlaybackQueue* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    AimpPlaybackQueueItem^ item = nullptr;

    try {
        if (service != nullptr) {
            result = CheckResult(service->GetNextTrack(&aimpItem));
            if (result == ActionResultType::OK) {
                item = gcnew AimpPlaybackQueueItem(aimpItem);
            }
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<IAimpPlaybackQueueItem^>(result, item);
}

AimpActionResult<IAimpPlaybackQueueItem^>^ AimpServicePlaybackQueue::GetPrevTrack() {
    IAIMPPlaybackQueueItem* aimpItem = nullptr;
    IAIMPServicePlaybackQueue* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    AimpPlaybackQueueItem^ item = nullptr;

    try {
        if (service != nullptr) {
            result = CheckResult(service->GetNextTrack(&aimpItem));
            if (result == ActionResultType::OK) {
                item = gcnew AimpPlaybackQueueItem(aimpItem);
            }
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<IAimpPlaybackQueueItem^>(result, item);
}

AimpActionResult^ AimpServicePlaybackQueue::NotifyChanged() {
    // TODO
    return ACTION_RESULT(ActionResultType::OK);
}

IAIMPServicePlaybackQueue* AimpServicePlaybackQueue::GetAimpService() {
    IAIMPServicePlaybackQueue* service = nullptr;
    GetService(IID_IAIMPServicePlaybackQueue, &service);
    return service;
}
