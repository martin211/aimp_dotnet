#pragma once

#include "..\BaseManager.h"
#include "AimpPlaybackQueueItem.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::PlayList;
        using namespace AIMP::SDK::Playback;

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