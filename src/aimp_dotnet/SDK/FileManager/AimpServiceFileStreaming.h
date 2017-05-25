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
#include "SDK\BaseManager.h"
#include "SDK\AimpStream.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::FileManager;

        public ref class AimpServiceFileStreaming : public AimpBaseManager<IAIMPServiceFileStreaming>, public IAimpServiceFileStreaming
        {
        public:
            AimpServiceFileStreaming(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceFileStreaming>(core)
            {}

            // Inherited via IAimpServiceFileStreaming
            virtual AimpActionResult CreateStreamForFile(String ^fileName, FileStreamingType flags, long long ofset, long long size, IAimpStream ^%stream);

            virtual AimpActionResult CreateStreamForFileUri(String ^fileUrl, IAimpVirtualFile ^%virtualFile, IAimpStream ^%stream);
        };
    }
}
