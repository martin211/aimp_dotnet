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
#include "..\..\AimpObject.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::FileManager;
        using namespace AIMP::SDK::FileManager::Commands;

        public ref class AimpFileSystemCommandFileInfo : AimpObject<IAIMPFileSystemCommandFileInfo>, IAimpFileSystemCommandFileInfo
        {
        public:
            AimpFileSystemCommandFileInfo(IAIMPFileSystemCommandFileInfo *aimpObject);

            virtual AimpActionResult GetFileAttrs(String ^file, AimpFileAttributes %attr);

            virtual AimpActionResult GetFileSize(String ^file, long long %size);

            virtual AimpActionResult IsFileExists(String ^file);
        };
    }
}
