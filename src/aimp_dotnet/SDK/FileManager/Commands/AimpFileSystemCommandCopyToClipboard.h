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
        using namespace Objects;

        public ref class AimpFileSystemCommandCopyToClipboard : AimpObject<IAIMPFileSystemCommandCopyToClipboard>,
                                                                IAimpFileSystemCommandCopyToClipboard {
        public:
            explicit AimpFileSystemCommandCopyToClipboard(IAIMPFileSystemCommandCopyToClipboard* aimpObject);

            virtual ActionResult CopyToClipboard(List<String^>^ files);
        };
    }
}
