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

            virtual AimpActionResult GetFiles(FilesType flags, IAimpFileList^% list);

            virtual AimpActionResult GetGroupingFilter(IAimpDataFilter^% filter);

            virtual AimpActionResult GetGroupingFilterPath(String^% path);

            virtual AimpActionResult SetGroupingFilterPath(String^ path);
        protected:
            IAIMPServiceMusicLibraryUI* GetAimpService() override;
        };
    }
}
