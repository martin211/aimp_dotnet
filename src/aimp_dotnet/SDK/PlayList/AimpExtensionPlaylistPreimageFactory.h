// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "SDK\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace SDK;
        using namespace Playlist;

        public ref class AimpExtensionPlaylistPreimageFactory :
            public AimpObject<IAIMPExtensionPlaylistPreimageFactory>,
            public IAimpExtensionPlaylistPreimageFactory
        {
        public:
            explicit AimpExtensionPlaylistPreimageFactory(IAIMPExtensionPlaylistPreimageFactory* aimpObject);

            virtual ActionResultType CreatePreimage(IAimpPlaylistPreimage^% preimage);

            virtual ActionResultType GetName(String^% name);

            virtual ActionResultType GetId(String^% id);

            virtual PreimageFactoryFlags GetFlags();
        };
    }
}
