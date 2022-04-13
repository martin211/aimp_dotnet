#pragma once
// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

namespace AIMP {
    namespace SDK {
        using namespace AlbumArt;

        ref class AimpAlbumArtRequest :
            public AimpObject<IAIMPAlbumArtRequest>,
            public IAimpAlbumArtRequest {

        public:
            explicit AimpAlbumArtRequest(IAIMPAlbumArtRequest* properties);

            virtual property bool FindInFiles
            {
                bool get();
                void set(bool value);
            }

            property array<String^>^ FindInFileMasks
            {
                virtual array<String^>^ get();
                virtual void set(array<String^>^ value);
            }

            property array<String^>^ FindInFileExtensions
            {
                virtual array<String^>^ get();
                virtual void set(array<String^>^ value);
            }

            virtual property bool FindInInternet
            {
                bool get();
                void set(bool value);
            }

            property int FindInInternetMaxFileSize
            {
                virtual int get();
                virtual void set(int value);
            }

            property bool FindInTags {
                virtual bool get();
                virtual void set(bool value);
            }

            virtual AimpActionResult<IAimpImageContainer^>^ CacheGet(String^ key);

            virtual AimpActionResult^ CachePut(String^ key, IAimpImageContainer^ image);

            virtual AimpActionResult<IAimpImageContainer^>^ Download(String^ url);

            virtual bool IsCanceled();
        };
    }
}
