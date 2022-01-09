// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "SDK\AimpObject.h"

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace FileManager;
        using namespace Commands;

        public ref class AimpFileSystemCommandDelete : AimpObject<IAIMPFileSystemCommandDelete>,
                                                       IAimpFileSystemCommandDelete {
        public:
            explicit AimpFileSystemCommandDelete(IAIMPFileSystemCommandDelete* aimpObject);

            virtual ActionResult CanProcess(String^ file);

            virtual ActionResult Process(String^ file);
        };
    }
}
