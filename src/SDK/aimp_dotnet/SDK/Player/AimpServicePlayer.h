//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "SDK\BaseAimpService.h"

namespace AIMP {
    namespace SDK {
        using namespace Player;
        using namespace Player::Objects;
        using namespace Playlist::Objects;

        public ref class AimpServicePlayer :
            public BaseAimpService<IAIMPServicePlayer2>,
            public IAimpServicePlayer {
        public:
            explicit AimpServicePlayer(ManagedAimpCore^ core);

            property AimpPlayerState State {
                virtual AimpPlayerState get();
            }

            property double Duration {
                virtual double get();
            }

            property double Position {
                virtual double get();
                virtual void set(double position);
            }

            property float Volume { virtual float get(); virtual void set(float volume); }
            property bool IsMute { virtual bool get(); virtual void set(bool value); }
            property IAimpFileInfo^ CurrentFileInfo { virtual IAimpFileInfo^ get(); }
            property IAimpPlaylistItem^ CurrentPlaylistItem { virtual IAimpPlaylistItem^ get(); }
            property ActionOnTrackEnd ActionOnEndOfTrack
            {
                virtual ActionOnTrackEnd get();
                virtual void set(ActionOnTrackEnd value);
            }
            property bool AutoJumpToNextTrack {
                virtual bool get();
                virtual void set(bool value);
            }
            property bool AutoSwitching {
                virtual bool get();
                virtual void set(bool value);
            }
            property int AutoSwitchingPauseBetweenTracks
            {
                virtual int get();
                virtual void set(int value);
            }
            property int AutoSwitchingCrossFade {
                virtual int get();
                virtual void set(int value);
            }
            property int AutoSwitchingFadeIn {
                virtual int get();
                virtual void set(int value);
            }
            property int AutoSwitchingFadeOut {
                virtual int get();
                virtual void set(int value);
            }
            property bool ManualSwitching {
                virtual bool get();
                virtual void set(bool value);
            }
            property int ManualSwitchingCrossFade
            {
                virtual int get();
                virtual void set(int value);
            }
            property int ManualSwitchingFadeIn {
                virtual int get();
                virtual void set(int value);
            }
            property int ManualSwitchingFadeOut {
                virtual int get();
                virtual void set(int value);
            }

            virtual AimpActionResult^ Play(IAimpPlaybackQueueItem^ item, int offset, Player::PlayFlags flags);

            virtual AimpActionResult^ Play(IAimpPlaylistItem^ item, int offset, Player::PlayFlags flags);

            virtual AimpActionResult^ Play(String^ fileUri, int offset, Player::PlayFlags flags);

            virtual AimpActionResult^ Play(IAimpPlaybackQueueItem^ queueItem);

            virtual AimpActionResult^ Play(IAimpPlaylistItem^ playlistItem);

            virtual AimpActionResult^ Play(IAimpPlaylist^ playList);

            virtual AimpActionResult^ Play(String^ fileUri, Player::PlayFlags flags);

            virtual AimpActionResult^ GoToNext();

            virtual AimpActionResult^ GoToPrev();

            virtual AimpActionResult^ Pause();

            virtual AimpActionResult^ Resume();

            virtual AimpActionResult^ Stop();

            virtual AimpActionResult^ StopAfterTrack();
        protected:
            IAIMPServicePlayer2* GetAimpService() override;

            IAIMPServicePlayer* GetService();
        };
    }
}


