/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
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


