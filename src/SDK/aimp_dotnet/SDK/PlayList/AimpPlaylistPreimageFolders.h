//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "AimpPlaylistPreimage.h"

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace AIMP::SDK::Playlist;

        public ref class AimpPlaylistPreimageFolders :
            public AimpPlaylistPreimage,
            public IAimpPlaylistPreimageFolders {
        public:
            explicit AimpPlaylistPreimageFolders(IAIMPPlaylistPreimageFolders* aimpObject);

            virtual ActionResult ItemsAdd(String^ path, bool recursive);

            virtual ActionResult ItemsDelete(int index);

            virtual ActionResult ItemsDeleteAll();

            virtual AimpActionResult<String^, bool>^ ItemsGet(int index);

            virtual int ItemsGetCount();
        };
    }
}
