#pragma once

#include "SDK\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AlbumArtManager;

        public ref class AimpServiceAlbumArtCache :
            public BaseAimpService<IAIMPServiceAlbumArtCache>,
            public IAimpServiceAlbumArtCache
        {
        public:
            explicit AimpServiceAlbumArtCache(ManagedAimpCore^ core);

            virtual ActionResultType Flush(String^ album, String^ artist);

            virtual ActionResultType Flush2(String^ fileUri);

            virtual ActionResultType FlushAll();
        protected:
            IAIMPServiceAlbumArtCache* GetAimpService() override;
        };
    }
}