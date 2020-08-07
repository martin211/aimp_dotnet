// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "SDK\BaseAimpService.h"

namespace AIMP {
    namespace SDK {
        using namespace SDK;
        using namespace Options;

        public ref class AimpServiceOptionsDialog : public BaseAimpService<IAIMPServiceOptionsDialog>,
                                                    public IAimpServiceOptionsDialog {
        public:
            explicit AimpServiceOptionsDialog(ManagedAimpCore^ core);

            virtual ActionResult FrameModified(IAimpOptionsDialogFrame^ frame);

            virtual ActionResult FrameShow(IAimpOptionsDialogFrame^ frame, bool forceShow);
        protected:
            IAIMPServiceOptionsDialog* GetAimpService() override;
        };
    }
}
