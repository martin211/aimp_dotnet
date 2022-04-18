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
        using namespace Services;

        public ref class AimpServiceAlbumArtCache :
            public BaseAimpService<IAIMPServiceAlbumArtCache>,
            public IAimpServiceAlbumArtCache {
        public:
            explicit AimpServiceAlbumArtCache(ManagedAimpCore^ core);

            virtual AimpActionResult^ Flush();

            virtual AimpActionResult<IAimpImageContainer^>^ Get(String^ key);

            virtual AimpActionResult^ Put(String^ key, IAimpImageContainer^ image);

            virtual AimpActionResult^ Remove(String^ key);

            virtual AimpActionResult<Tuple<int, int>^>^ Stat();

        protected:
            IAIMPServiceAlbumArtCache* GetAimpService() override;
        };
    }
}
