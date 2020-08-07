// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "SDK\BaseAimpService.h"

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace FileManager;

        public ref class AimpServiceFileStreaming : public BaseAimpService<IAIMPServiceFileStreaming>,
                                                    public IAimpServiceFileStreaming {
        public:
            AimpServiceFileStreaming(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceFileStreaming>(core) {
            }

            virtual StreamResult CreateStreamForFile(String^ fileName, FileStreamingType flags, long long offset,
                                                     long long size);

            virtual AimpActionResult<CeateStreamResult^>^ CreateStreamForFileUri(String^ fileUrl);
        protected:
            IAIMPServiceFileStreaming* GetAimpService() override;
        };
    }
}
