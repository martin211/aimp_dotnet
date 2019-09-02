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

#pragma once

#include "SDK\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace Playlist;
        using namespace Playback;

        public ref class AimpServicePlaybackQueue : public BaseAimpService<IAIMPServicePlaybackQueue>,
                                                    public IAimpPlaybackQueueService
        {
        private:
            AimpCheckUrl^ _checkUrlHandler;

        public:
            explicit AimpServicePlaybackQueue(ManagedAimpCore^ core);

            virtual IAimpPlaybackQueueItem^ GetNextTrack();

            virtual IAimpPlaybackQueueItem^ GetPrevTrack();

            virtual event AimpCheckUrl^ OnCheckURL
            {
                virtual void add(AimpCheckUrl^ onEvent);
                virtual void remove(AimpCheckUrl^ onEvent);
            }
        internal:
            bool RaiseCheckUrl(String^% url);
        protected:
            IAIMPServicePlaybackQueue* GetAimpService() override;
        };
    }
}
