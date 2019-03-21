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

        public ref class AimpFileSystemCommandDropSource : AimpObject<IAIMPFileSystemCommandDropSource>, IAimpFileSystemCommandDropSource
        {
        public:
            explicit AimpFileSystemCommandDropSource(IAIMPFileSystemCommandDropSource* aimpObject);

            virtual IAimpStream^ CreateStream(String^ fileName);
        };
    }
}
