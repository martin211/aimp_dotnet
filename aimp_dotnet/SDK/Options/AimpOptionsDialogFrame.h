#pragma once
#include "..\AimpExtensionBase.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMPSDK;

        ref class AimpOptionsDialogFrame : public AimpExtensionBase
        {
        internal:
            property GUID ExtensionId
            {
                virtual GUID get() override
                {
                    return IID_IAIMPServiceOptionsDialog;
                }
            }
        };
    }
}
