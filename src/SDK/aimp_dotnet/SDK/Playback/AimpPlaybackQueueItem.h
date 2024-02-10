//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace Player::Objects;
        using namespace Playlist::Objects;

        public ref class AimpPlaybackQueueItem : public AimpObject<IAIMPPlaybackQueueItem>,
                                                 public IAimpPlaybackQueueItem {
        public:
            explicit AimpPlaybackQueueItem(IAIMPPlaybackQueueItem* aimpItem);

            property double Offset {
                virtual double get();
                virtual void set(double offset);
            }

            virtual property Object^ UserData
            {
                Object^ get();
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
