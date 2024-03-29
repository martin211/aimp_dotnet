//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

namespace AIMP {
    namespace SDK {
        using namespace AlbumArt;

        ref class AimpAlbumArtSearchOptions : public IAimpAlbumArtSearchOptions {
        private:
            bool _findInFiles;
            IAIMPPropertyList* _properties;

        public:
            AimpAlbumArtSearchOptions(IAIMPPropertyList* properties);

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

            virtual property array<String^>^ FileMasks
            {
                array<String^>^ get();
                void set(array<String^>^ value);
            }

            virtual property array<String^>^ FileExtensions
            {
                array<String^>^ get();
                void set(array<String^>^ value);
            }

            virtual property int MaxFileSize
            {
                int get();
                void set(int value);
            }
        };
    }
}
