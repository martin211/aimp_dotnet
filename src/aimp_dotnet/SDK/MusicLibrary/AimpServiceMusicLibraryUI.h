// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
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
        using namespace MusicLibrary;

        public ref class AimpServiceMusicLibraryUI :
            public BaseAimpService<IAIMPServiceMusicLibraryUI>,
            public IAimpServiceMusicLibraryUI
        {
        public:
            explicit AimpServiceMusicLibraryUI(ManagedAimpCore^ core);

            virtual ActionResultType GetFiles(FilesType flags, IAimpFileList^% list);

            virtual ActionResultType GetGroupingFilter(IAimpDataFilter^% filter);

            virtual ActionResultType GetGroupingFilterPath(String^% path);

            virtual ActionResultType SetGroupingFilterPath(String^ path);
        protected:
            IAIMPServiceMusicLibraryUI* GetAimpService() override;
        };
    }
}
