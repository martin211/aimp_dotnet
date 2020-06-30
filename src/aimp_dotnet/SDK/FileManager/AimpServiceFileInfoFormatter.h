// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "SDK/BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        public ref class AimpServiceFileInfoFormatter : public BaseAimpService<IAIMPServiceFileInfoFormatter>, public IAimpServiceFileInfoFormatter
        {
        public:
            explicit AimpServiceFileInfoFormatter(ManagedAimpCore^ core);
            virtual StringResult Format(String^ tmpl, IAimpFileInfo^ fileInfo);
        protected:
            IAIMPServiceFileInfoFormatter* GetAimpService() override;
        };
    }
}
