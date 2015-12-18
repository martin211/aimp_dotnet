#pragma once
#include "..\BaseManager.h"
#include "..\..\Extensions\OptionsDialogFrameExtension.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::Options;

        public ref class AimpServiceOptionsDialog : public AimpBaseManager, public IAimpServiceOptionsDialog
        {
            private:
                IAIMPServiceOptionsDialog *_service;

            public:
                explicit AimpServiceOptionsDialog(ManagedAimpCore ^core) : AimpBaseManager(core)
                {
                    IAIMPServiceOptionsDialog *service;
                    core->GetService(IID_IAIMPServiceOptionsDialog, (void**) &service);
                    _service = service;
                }

                virtual AimpActionResult FrameModified(IAimpOptionsDialogFrame ^frame)
                {
                    return CheckResult(_service->FrameModified(_core->GetOptionsFrame()));
                }

                virtual AimpActionResult FrameShow(IAimpOptionsDialogFrame ^frame, bool forceShow)
                {
                    return CheckResult(_service->FrameShow(_core->GetOptionsFrame()));
                }
        };
    }
}


