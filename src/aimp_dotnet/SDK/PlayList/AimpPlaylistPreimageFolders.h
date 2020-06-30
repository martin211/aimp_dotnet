// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
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

            virtual ActionResultType ItemsAdd(String^ path, bool recursive);

            virtual ActionResultType ItemsDelete(int index);

            virtual ActionResultType ItemsDeleteAll();

            virtual ActionResultType ItemsGet(int index, String^% path, bool% recursive);

            virtual int ItemsGetCount();
        };
    }
}
