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
#include "SDK\AimpObject.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace FileManager;
        using namespace Commands;
        using namespace Objects;

        public ref class AimpFileSystemCommandStreaming : AimpObject<IAIMPFileSystemCommandStreaming>,
                                                          IAimpFileSystemCommandStreaming
        {
        public:
            explicit AimpFileSystemCommandStreaming(IAIMPFileSystemCommandStreaming* aimpObject);

            virtual IAimpStream^ CreateStream(String^ fileName, FileStreamingType flags, long long offset,
                                              long long size);
        };
    }
}
