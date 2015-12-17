#pragma once
#include "..\BaseManager.h"
#include "AimpOptionsDialogFrame.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::Services;
        using namespace AIMP::SDK::Services::Options;

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
                    return CheckResult(_service->FrameModified(((AimpOptionsDialogFrame^)_core->OptionsFrame)->AimpObject));
                }

                virtual AimpActionResult FrameShow(IAimpOptionsDialogFrame ^frame, bool forceShow)
                {
                    return CheckResult(_service->FrameShow(((AimpOptionsDialogFrame^)_core->OptionsFrame)->AimpObject));
                }
        };
    }
}


