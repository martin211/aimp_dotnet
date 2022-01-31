// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

namespace AIMP {
    namespace SDK {
        using namespace Playlist;
        using namespace Playlist::Objects;

        public ref class AimpPlayListGroup : public AimpObject<IAIMPPlaylistGroup>, public IAimpPlaylistGroup {
        public:
            ~AimpPlayListGroup() {
            }

            AimpPlayListGroup();

            explicit AimpPlayListGroup(IAIMPPlaylistGroup* item);

            virtual property String^ Name
            {
                String^ get();
            }

            virtual property bool Expanded
            {
                bool get();
                void set(bool value);
            }

            virtual property double Duration
            {
                double get();
            }

            virtual property int Index
            {
                int get();
            }

            virtual property bool Selected
            {
                bool get();
                void set(bool value);
            }

            virtual property int Count
            {
                int get();
            }

            virtual AimpActionResult<IAimpPlaylistItem^>^ GetItem(int index);
        };
    }
}
