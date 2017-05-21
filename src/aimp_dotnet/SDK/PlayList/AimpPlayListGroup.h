/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#pragma once

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::Playlist;

        public ref class AimpPlayListGroup : public AimpObject<IAIMPPlaylistGroup>, public IAimpPlayListGroup
        {
        private:
            IAimpPlaylistItem ^_item;

        public:
            ~AimpPlayListGroup()
            {
                _item = nullptr;
            }
            AimpPlayListGroup();

            explicit AimpPlayListGroup(IAIMPPlaylistGroup *item);

            virtual property System::String^ Name
            {
                System::String^ get();
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

            virtual IAimpPlaylistItem ^GetItem(int index);
        };
    }
}
