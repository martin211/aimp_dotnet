#pragma once
#include "..\AimpExtensionBase.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMPSDK;

        public ref class AimpOptionsDialogFrame : public AimpExtensionBase
        {
        internal:
            property GUID ExtensionId
            {
                virtual GUID get() override
                {
                    return IID_IAIMPServiceOptionsDialog;
                }
            }

            property String ^Name
            {
                virtual String ^get() override
                {
                    return "Options dialog frame";
                }
            }

            property IUnknown *InternalProxyExtension
            {
                virtual IUnknown *get() override
                {
                    return nullptr;
                }

                virtual void set(IUnknown *value) override
                {

                }
            }
        };
    }
}
