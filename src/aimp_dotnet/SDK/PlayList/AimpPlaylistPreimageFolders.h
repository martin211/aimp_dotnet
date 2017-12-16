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
#include "AimpPlaylistPreimage.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::Playlist;

        public ref class AimpPlaylistPreimageFolders :
            public AimpPlaylistPreimage,
            public IAimpPlaylistPreimageFolders
        {
        public:
            explicit AimpPlaylistPreimageFolders(IAIMPPlaylistPreimageFolders* aimpObject);

            virtual AimpActionResult ItemsAdd(String^ path, bool recursive);

            virtual AimpActionResult ItemsDelete(int index);

            virtual AimpActionResult ItemsDeleteAll();

            virtual AimpActionResult ItemsGet(int index, String^% path, bool% recursive);

            virtual int ItemsGetCount();
        };
    }
}
