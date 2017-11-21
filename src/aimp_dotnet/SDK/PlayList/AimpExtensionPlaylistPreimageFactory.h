// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once
 #include "SDK\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::Playlist;

        public ref class AimpExtensionPlaylistPreimageFactory :
            public AimpObject<IAIMPExtensionPlaylistPreimageFactory>,
            public AIMP::SDK::Playlist::IAimpExtensionPlaylistPreimageFactory
        {
        public:
            explicit AimpExtensionPlaylistPreimageFactory(IAIMPExtensionPlaylistPreimageFactory *aimpObject);

            virtual AimpActionResult CreatePreimage(IAimpPlaylistPreimage ^%preimage);

            virtual AimpActionResult GetName(String ^%name);

            virtual AimpActionResult GetId(String ^%id);

            virtual PreimageFactoryFlags GetFlags();
        };
    }
}
