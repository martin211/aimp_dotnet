// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "SDK\BaseManager.h"

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace MusicLibrary;

        public ref class AimpServiceMusicLibraryUI :
            public BaseAimpService<IAIMPServiceMusicLibraryUI>,
            public IAimpServiceMusicLibraryUI {
        public:
            explicit AimpServiceMusicLibraryUI(ManagedAimpCore^ core);

            virtual TYPED_RESULT(IAimpFileList) GetFiles(FilesType flags);

            virtual TYPED_RESULT(IAimpDataFilter) GetGroupingFilter();

            virtual StringResult GetGroupingFilterPath();

            virtual ActionResult SetGroupingFilterPath(String^ path);
        protected:
            IAIMPServiceMusicLibraryUI* GetAimpService() override;
        };
    }
}
