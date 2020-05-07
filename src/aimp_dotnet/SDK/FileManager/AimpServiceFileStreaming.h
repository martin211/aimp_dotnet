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
        using namespace FileManager;

        public ref class AimpServiceFileStreaming : public BaseAimpService<IAIMPServiceFileStreaming>,
                                                    public IAimpServiceFileStreaming
        {
        public:
            AimpServiceFileStreaming(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceFileStreaming>(core)
            {
            }

            virtual ActionResultType CreateStreamForFile(String^ fileName, FileStreamingType flags, long long offset,
                                                         long long size, IAimpStream^% stream);

            virtual ActionResultType CreateStreamForFileUri(String^ fileUrl, IAimpVirtualFile^% virtualFile,
                                                            IAimpStream^% stream);
        protected:
            IAIMPServiceFileStreaming* GetAimpService() override;
        };
    }
}
