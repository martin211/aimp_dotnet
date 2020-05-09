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

            virtual FileInfoResult GetFileInfoFromFileUri(String^ fileUri, ServiceFileInfoFlags fileInfoFlags);

            virtual FileInfoResult GetFileInfoFromStream(IAimpStream^ fileStream, ServiceFileInfoFlags fileInfoFlags);

            virtual VirtualFileResult GetVirtualFile(String^ fileUri);
        protected:
            IAIMPServiceFileInfo* GetAimpService() override;
        };
    }
}
