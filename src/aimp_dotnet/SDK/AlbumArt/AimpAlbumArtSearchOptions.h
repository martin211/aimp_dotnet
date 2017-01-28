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
