// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once

#include "SDK\BaseManager.h"
#include "AimpPlaybackQueueItem.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::Playlist;
        using namespace AIMP::SDK::Playback;

        [System::Serializable]
        public ref class AimpServicePlaybackQueue : public AimpBaseManager<IAIMPServicePlaybackQueue>, public IAimpPlaybackQueueService
        {
        private:
            AimpCheckUrl ^_checkUrlHandler;

        public:
            explicit AimpServicePlaybackQueue(ManagedAimpCore ^core);

            virtual IAimpPlaybackQueueItem^ GetNextTrack();

            virtual IAimpPlaybackQueueItem^ GetPrevTrack();

            virtual event AimpCheckUrl ^OnCheckURL
            {
                virtual void add(AimpCheckUrl ^onEvent);
                virtual void remove(AimpCheckUrl ^onEvent);
            }
        internal:
            bool RaiseCheckUrl(String^ %url);
        };
    }
}
