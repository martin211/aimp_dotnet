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

            virtual AimpActionResult Flush(String^ album, String^ artist);

            virtual AimpActionResult Flush2(String^ fileUri);

            virtual AimpActionResult FlushAll();
        protected:
            IAIMPServiceAlbumArtCache* GetAimpService() override;
        };
    }
}