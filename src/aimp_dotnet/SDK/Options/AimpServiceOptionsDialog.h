/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#pragma once
#include "..\BaseManager.h"
#include "..\..\SDK\Options\OptionsDialogFrameExtension.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::Options;

        public ref class AimpServiceOptionsDialog : public AimpBaseManager<IAIMPServiceOptionsDialog>, public IAimpServiceOptionsDialog
        {
            private:
                IAIMPServiceOptionsDialog *_service;

            public:
                explicit AimpServiceOptionsDialog(ManagedAimpCore ^core);

                virtual AimpActionResult FrameModified(IAimpOptionsDialogFrame ^frame);

                virtual AimpActionResult FrameShow(IAimpOptionsDialogFrame ^frame, bool forceShow);
        };
    }
}


