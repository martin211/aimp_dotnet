#pragma once

#include "..\..\..\AIMPSDK\apiGUI.h"
#include "..\..\AimpObject.h"
#include "..\..\AimpConverter.h"
#include "AimpUIControl.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::Drawing;
        using namespace AIMP::SDK::GUI::Controls;

        public ref class AimpUIWinControl : public AimpUIControl, public IAimpUIWinControl
        {
        public:
            explicit AimpUIWinControl(IAIMPUIWinControl *aimpObject);

            virtual property bool Focused
            {
                bool get();
                void set(bool value);
            }

            virtual property int TabOrder
            {
                int get();
                void set(int vulue);
            }

            virtual AimpActionResult GetControl(AIMP::SDK::GUI::Controls::IAimpUIControl ^control, int index, String ^iid);

            virtual int GetControlCount();

            virtual IntPtr GetHandle();

            virtual bool HasHandle();

            virtual AimpActionResult SetFocus();

            virtual event AimpUIEventHandler ^OnEnter;

            virtual event AimpUIEventHandler ^OnExit;

            virtual event AimpUIEventHandler<AimpKeyboardArgs^> ^OnKeyDown;

            virtual event AimpUIEventHandler<AimpKeyboardArgs^> ^OnKeyUp;

            virtual event AimpUIEventHandler<AimpKeyArgs^> ^OnKeyPress;

            virtual event AimpBoolUIEventHandler<AimpBeforeWndProcArgs^> ^OnBeforeWndProc;

            virtual event AimpUIEventHandler<AimpAfterWndProcArgs^> ^OnAfterWndProc;
        };
    }
}
