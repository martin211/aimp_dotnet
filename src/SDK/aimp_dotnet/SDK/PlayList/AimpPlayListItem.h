// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

namespace AIMP {
    namespace SDK {
        using namespace System;

        using namespace SDK;
        using namespace Playlist;
        using namespace Playlist::Objects;
        using namespace FileManager;

        public ref class AimpPlaylistItem : public AimpObject<IAIMPPlaylistItem>, public IAimpPlaylistItem {
        private:
            IAimpPlaylistGroup^ _group;
            bool _disposed;
        internal:
            AimpPlaylistItem(IAIMPPlaylistItem* aimpItem) : AimpObject(aimpItem) {
            }

            AimpPlaylistItem(IAimpPlaylistItem^ item);
        public:
            AimpPlaylistItem();

            virtual property String^ DisplayText
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ FileName
            {
                String^ get();
                void set(String^ value);
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

            virtual ActionResult ReloadInfo();

        protected:
            void RegisterAtMemoryManager() override;

            void ReleaseFromMemoryManager() override;
        };
    }
}
