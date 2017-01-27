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

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::FileManager;

        public ref class AimpServiceFileFormats : public AimpBaseManager<IAIMPServiceFileFormats>, public IAimpServiceFileFormats
        {
        public:
            explicit AimpServiceFileFormats(ManagedAimpCore^ core);

            virtual AimpActionResult GetFormats(FileFormats flags, String ^% formats);

            virtual AimpActionResult IsSupported(String ^fileName, FileFormats flags);
        };
    }
}
