// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
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

        public ref class AimpFileSystemCommandOpenFileFolder : AimpObject<IAIMPFileSystemCommandOpenFileFolder>,
                                                               IAimpFileSystemCommandOpenFileFolder
        {
        public:
            explicit AimpFileSystemCommandOpenFileFolder(IAIMPFileSystemCommandOpenFileFolder* aimpObject);

            virtual VoidResult CanProcess(String^ file);

            virtual VoidResult Process(String^ file);
        };
    }
}
