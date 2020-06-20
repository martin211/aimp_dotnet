// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

namespace AIMP
{
    namespace SDK
    {
        using namespace System;

        using namespace AIMP::SDK;
        using namespace AIMP::SDK::Playlist;
        using namespace AIMP::SDK::FileManager;

        public ref class AimpPlaylistItem : public AimpObject<IAIMPPlaylistItem>, public IAimpPlaylistItem
        {
        private:
            IAimpPlaylistGroup^ _group;
            bool _disposed;
        internal:
            AimpPlaylistItem(IAIMPPlaylistItem* aimpItem) : AimpObject(aimpItem)
            {
            }

            AimpPlaylistItem(IAimpPlaylistItem^ item);
        public:
            AimpPlaylistItem();

            virtual property System::String^ DisplayText
            {
                System::String^ get();
                void set(System::String^ value);
            }

            virtual property System::String^ FileName
            {
                System::String^ get();
                void set(System::String^ value);
            }

            virtual property int Index
            {
                int get();
                void set(int value);
            }

            virtual property double Mark
            {
                double get();
                void set(double value);
            }

            virtual property int PlaybackIndex
            {
                int get();
            }

            virtual property bool PlaybackSwitch
            {
                bool get();
                void set(bool value);
            }

            virtual property bool Selected
            {
                bool get();
                void set(bool value);
            }

            virtual property IAimpFileInfo^ FileInfo
            {
                IAimpFileInfo^ get();
            }

            virtual property IAimpPlaylistGroup^ Group
            {
                IAimpPlaylistGroup^ get();
            }

            virtual property IAimpPlaylist^ PlayList
            {
                IAimpPlaylist^ get();
                void set(IAimpPlaylist^ val);
            }

            virtual ActionResultType ReloadInfo();

        protected:
            void RegisterAtMemoryManager() override;

            void ReleaseFromMemoryManager() override;
        };
    }
}
