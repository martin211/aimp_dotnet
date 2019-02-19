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
        using namespace Playlist;

        public ref class AimpPlayListGroup : public AimpObject<IAIMPPlaylistGroup>, public IAimpPlaylistGroup
        {
        private:
            IAimpPlaylistItem ^_item;

        public:
            ~AimpPlayListGroup()
            {
                _item = nullptr;
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
                void set(double value);
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

            virtual IAimpPlaylistItem^ GetItem(int index);
        };
    }
}
