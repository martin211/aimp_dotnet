// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

#include "SDK\BaseAimpService.h"

namespace AIMP {
    namespace SDK {
        using namespace Playlist;
        using namespace Playback;

        public ref class AimpServicePlaybackQueue : public BaseAimpService<IAIMPServicePlaybackQueue>,
                                                    public IAimpServicePlaybackQueue {
        public:
            explicit AimpServicePlaybackQueue(ManagedAimpCore^ core);

            virtual AimpActionResult<IAimpPlaybackQueueItem^>^ GetNextTrack();

            virtual AimpActionResult<IAimpPlaybackQueueItem^>^ GetPrevTrack();

        protected:
            IAIMPServicePlaybackQueue* GetAimpService() override;
        };
    }
}
