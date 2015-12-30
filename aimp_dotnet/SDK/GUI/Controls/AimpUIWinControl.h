#pragma once

#include "..\..\..\AIMPSDK\apiGUI.h"
#include "..\..\AimpObject.h"


namespace AIMP
{
    namespace SDK
    {
        ref class AimpUIWinControl : public AimpObject<IAIMPUIWinControl>, public AIMP::SDK::GUI::IAimpUIWinControl
        {
        public:
            AimpUIWinControl();
        };
    }
}


