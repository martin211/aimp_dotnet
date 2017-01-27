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
        ref class AimpAlbumArtSearchOptions : public AIMP::SDK::AlbumArtManager::IAimpAlbumArtSearchOptions
        {
        private:
            bool _findInFiles;
            IAIMPPropertyList *_properties;
            IAIMPCore *_core;

        public:
            AimpAlbumArtSearchOptions(IAIMPPropertyList *properties, IAIMPCore* core);

            virtual property bool FindInFiles
            {
                bool get();
                void set(bool value);
            }

            virtual property bool FindInInternet
            {
                bool get();
                void set(bool value);
            }

            virtual property array<System::String^>^ FileMasks
            {
                array<System::String^>^ get();
                void set(array<System::String^>^ value);
            }

            virtual property array<System::String^>^ FileExtensions
            {
                array<System::String^>^ get();
                void set(array<System::String^>^ value);
            }

            virtual property int MaxFileSize
            {
                int get();
                void set(int value);
            }
        };
    }
}
