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
        using namespace SDK;
        using namespace Options;

        public ref class AimpServiceOptionsDialog : public AimpBaseManager<IAIMPServiceOptionsDialog>,
                                                    public IAimpServiceOptionsDialog
        {
        private:
            IAIMPServiceOptionsDialog* _service;

        public:
            explicit AimpServiceOptionsDialog(ManagedAimpCore^ core);

            virtual AimpActionResult FrameModified(IAimpOptionsDialogFrame^ frame);

            virtual AimpActionResult FrameShow(IAimpOptionsDialogFrame^ frame, bool forceShow);
        };
    }
}
