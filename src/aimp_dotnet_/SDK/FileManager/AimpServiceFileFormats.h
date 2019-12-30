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
#include "SDK\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace FileManager;

        public ref class AimpServiceFileFormats : public BaseAimpService<IAIMPServiceFileFormats>,
                                                  public IAimpServiceFileFormats
        {
        public:
            explicit AimpServiceFileFormats(ManagedAimpCore^ core);

            virtual AimpActionResult GetFormats(FileFormats flags, String^% formats);

            virtual AimpActionResult IsSupported(String^ fileName, FileFormats flags);
        protected:
            IAIMPServiceFileFormats* GetAimpService() override;
        };
    }
}
