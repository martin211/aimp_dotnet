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

        public ref class AimpFileSystemCommandDelete : AimpObject<IAIMPFileSystemCommandDelete>, IAimpFileSystemCommandDelete
        {
        public:
            explicit AimpFileSystemCommandDelete(IAIMPFileSystemCommandDelete* aimpObject);

            virtual AimpActionResult CanProcess(String^ file);

            virtual AimpActionResult Process(String^ file);
        };
    }
}
