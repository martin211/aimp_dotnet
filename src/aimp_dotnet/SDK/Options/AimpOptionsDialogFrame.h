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

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::Options;

        public ref class AimpOptionsDialogFrame :
            public AimpObject<IAIMPOptionsDialogFrame>,
            public IAimpOptionsDialogFrame,
            public IAimpOptionsDialogFrameKeyboardHelper
        {
        public:
            explicit AimpOptionsDialogFrame(IAIMPOptionsDialogFrame* aimpObject);

            virtual String^ GetName() abstract;

            virtual IntPtr CreateFrame(IntPtr parentWindow) abstract;

            virtual void DestroyFrame() abstract;
            
            virtual void Notification(int id) abstract;

            virtual bool DialogKey(int charCode) abstract;

            virtual bool SelectFirstControl() abstract;

            virtual bool SelectNextControl(int findForward, int isTabKeyAction) abstract;
        };
    }
}
