/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 */
 
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
