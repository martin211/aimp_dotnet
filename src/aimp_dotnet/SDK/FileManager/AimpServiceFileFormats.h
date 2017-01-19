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