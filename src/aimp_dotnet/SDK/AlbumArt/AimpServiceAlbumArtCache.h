// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

#include "SDK\BaseAimpService.h"

namespace AIMP {
    namespace SDK {
        using namespace AlbumArtManager;

        public ref class AimpServiceAlbumArtCache :
            public BaseAimpService<IAIMPServiceAlbumArtCache>,
            public IAimpServiceAlbumArtCache {
        public:
            explicit AimpServiceAlbumArtCache(ManagedAimpCore^ core);

            virtual AimpActionResult^ Flush(String^ album, String^ artist);

            virtual AimpActionResult^ Flush2(String^ fileUri);

            virtual AimpActionResult^ FlushAll();
        protected:
            IAIMPServiceAlbumArtCache* GetAimpService() override;
        };
    }
}
