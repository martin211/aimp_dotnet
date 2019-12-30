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
            virtual AimpActionResult Format(String^ tmpl, IAimpFileInfo^ fileInfo, String^% formattedResult);
        protected:
            IAIMPServiceFileInfoFormatter* GetAimpService() override;
        };
    }
}
