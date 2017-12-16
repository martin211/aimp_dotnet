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

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::Playlist;

        public ref class AimpPlaylistPreimageListener :
            public AimpObject<IAIMPPlaylistPreimageListener>,
            public IAimpPlaylistPreimageListener
        {
        private:
            AimpPlaylistPreimageListenerHandler ^_dataChangedHandler;
            AimpPlaylistPreimageListenerHandler ^_settingsChangedHandler;
        public:
            explicit AimpPlaylistPreimageListener(IAIMPPlaylistPreimageListener *aimpObject);

            virtual event AimpPlaylistPreimageListenerHandler ^DataChanged
            {
                void add(AimpPlaylistPreimageListenerHandler ^onEvent);
                void remove(AimpPlaylistPreimageListenerHandler ^onEvent);
                void raise();
            }

            virtual event AimpPlaylistPreimageListenerHandler ^SettingsChanged
            {
                void add(AimpPlaylistPreimageListenerHandler ^onEvent);
                void remove(AimpPlaylistPreimageListenerHandler ^onEvent);
                void raise();
            }
        };
    }
}
