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

namespace AIMP
{
    namespace SDK
    {
        using namespace System;

        using namespace AIMP::SDK;
        using namespace AIMP::SDK::PlayList;
        using namespace AIMP::SDK::FileManager;

        public ref class AimpPlayListItem : public AimpObject<IAIMPPlaylistItem>, public IAimpPlayListItem
        {
        private:
            IAimpPlayListGroup^ _group;
            bool _disposed;

        internal:
            AimpPlayListItem(IAIMPPlaylistItem *aimpItem) : AimpObject(aimpItem)
            {
            }

            AimpPlayListItem(IAimpPlayListItem ^item);
        public:
            AimpPlayListItem();

            ~AimpPlayListItem();

            !AimpPlayListItem();

            virtual property System::String^ DisplayText
            {
                System::String^ get();
                void set(System::String^ value);
            }

            virtual property System::String^ FileName
            {
                System::String^ get();
                void set(System::String ^value);
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

            virtual property IAimpPlayListGroup^ Group
            {
                IAimpPlayListGroup^ get();
            }

            virtual property IAimpPlayList^ PlayList
            {
                IAimpPlayList^ get();
                void set(IAimpPlayList^ val);
            }

            virtual AimpActionResult ReloadInfo();
        };
    }
}
