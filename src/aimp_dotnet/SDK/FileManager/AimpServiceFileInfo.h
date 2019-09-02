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
#include "AimpFileInfo.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace IO;
        using namespace FileManager;

        public ref class AimpServiceFileInfo : public BaseAimpService<IAIMPServiceFileInfo>, public IAimpServiceFileInfo
        {
        public:
            AimpServiceFileInfo(ManagedAimpCore^ core);

            virtual AimpActionResult GetFileInfoFromFileUri(String^ fileUri, ServiceFileInfoFlags fileInfoFlags,
                                                            IAimpFileInfo^% fileInfo);

            virtual AimpActionResult GetFileInfoFromStream(IAimpStream^ fileStream, ServiceFileInfoFlags fileInfoFlags,
                                                           IAimpFileInfo^% fileInfo);

            virtual AimpActionResult GetVirtualFile(String^ fileUri, IAimpVirtualFile^% virtualFile);
        protected:
            IAIMPServiceFileInfo* GetAimpService() override;
        };
    }
}
