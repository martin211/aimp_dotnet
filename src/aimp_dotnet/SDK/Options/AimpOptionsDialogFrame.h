// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

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
