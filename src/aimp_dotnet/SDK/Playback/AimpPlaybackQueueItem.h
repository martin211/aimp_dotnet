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
#include "SDK\PlayList\AimpPlayListItem.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;

        public ref class AimpPlaybackQueueItem : public AimpObject<IAIMPPlaybackQueueItem>, public AIMP::SDK::Playback::IAimpPlaybackQueueItem
        {
        public:
            explicit AimpPlaybackQueueItem(IAIMPPlaybackQueueItem *aimpItem);

            virtual property Object ^UserData
            {
                Object ^get();
                void set(Object^ value);
            }

            virtual property IAimpPlaylistItem^ PlaylistItem
            {
                IAimpPlaylistItem^ get();
                void set(IAimpPlaylistItem^ value);
            }
        };
    }
}
