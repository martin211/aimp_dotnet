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

        public ref class AimpFileSystemCommandOpenFileFolder : AimpObject<IAIMPFileSystemCommandOpenFileFolder>, IAimpFileSystemCommandOpenFileFolder
        {
        public:
            explicit AimpFileSystemCommandOpenFileFolder(IAIMPFileSystemCommandOpenFileFolder* aimpObject);

            virtual AimpActionResult CanProcess(String^ file);

            virtual AimpActionResult Process(String^ file);
        };
    }
}
