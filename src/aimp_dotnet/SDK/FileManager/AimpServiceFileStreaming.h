/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 */
 
#pragma once
#include "..\BaseManager.h"
#include "..\AimpStream.h"

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
