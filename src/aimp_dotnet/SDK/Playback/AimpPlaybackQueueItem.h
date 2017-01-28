#pragma once
#include "..\PlayList\AimpPlayListItem.h"

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

            virtual property IAimpPlayListItem^ PlayListItem
            {
                IAimpPlayListItem^ get();
                void set(IAimpPlayListItem^ value);
            }
        };
    }
}