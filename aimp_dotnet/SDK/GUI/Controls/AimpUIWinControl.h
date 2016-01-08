#pragma once

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
                void set(int value);
            }

            virtual AimpActionResult GetControl(AIMP::SDK::GUI::Controls::IAimpUIControl ^control, int index, String ^iid);

            virtual int GetControlCount();

            virtual IntPtr GetHandle();

            virtual bool HasHandle();

            virtual AimpActionResult SetFocus();

            virtual event AimpUIEventHandler ^OnEnter
            {
                virtual void add(AimpUIEventHandler ^onEvent);
                virtual void remove(AimpUIEventHandler ^onEvent);
                virtual void raise(IAimpUIControl ^sender);
            }

            virtual event AimpUIEventHandler ^OnExit
            {
                virtual void add(AimpUIEventHandler ^onEvent);
                virtual void remove(AimpUIEventHandler ^onEvent);
                virtual void raise(IAimpUIControl ^sender);
            }

            virtual event AimpUIEventHandler<AimpKeyboardArgs^> ^OnKeyDown
            {
                virtual void add(AimpUIEventHandler<AimpKeyboardArgs^> ^onEvent);
                virtual void remove(AimpUIEventHandler<AimpKeyboardArgs^> ^onEvent);
                virtual void raise(IAimpUIControl ^sender, AimpKeyboardArgs ^args);
            }

            virtual event AimpUIEventHandler<AimpKeyboardArgs^> ^OnKeyUp
            {
                virtual void add(AimpUIEventHandler<AimpKeyboardArgs^> ^onEvent);
                virtual void remove(AimpUIEventHandler<AimpKeyboardArgs^> ^onEvent);
                virtual void raise(IAimpUIControl ^sender, AimpKeyboardArgs ^args);
            }

            virtual event AimpUIEventHandler<AimpKeyArgs^> ^OnKeyPress
            {
                virtual void add(AimpUIEventHandler<AimpKeyArgs^> ^onEvent);
                virtual void remove(AimpUIEventHandler<AimpKeyArgs^> ^onEvent);
                virtual void raise(IAimpUIControl ^sender, AimpKeyArgs ^args);
            }

            virtual event AimpBoolUIEventHandler<AimpBeforeWndProcArgs^> ^OnBeforeWndProc
            {
                virtual void add(AimpBoolUIEventHandler<AimpBeforeWndProcArgs^> ^onEvent);
                virtual void remove(AimpBoolUIEventHandler<AimpBeforeWndProcArgs^> ^onEvent);
                virtual bool raise(IAimpUIControl ^sender, AimpBeforeWndProcArgs ^args);
            }

            virtual event AimpUIEventHandler<AimpAfterWndProcArgs^> ^OnAfterWndProc
            {
                virtual void add(AimpUIEventHandler<AimpAfterWndProcArgs^> ^onEvent);
                virtual void remove(AimpUIEventHandler<AimpAfterWndProcArgs^> ^onEvent);
                virtual void raise(IAimpUIControl ^sender, AimpAfterWndProcArgs ^args);
            }
        private:
            AimpUIEventHandler ^_onEnter;
            AimpUIEventHandler ^_onExit;
            AimpUIEventHandler<AimpKeyboardArgs^> ^_onKeyDown;
            AimpUIEventHandler<AimpKeyboardArgs^> ^_onKeyUp;
            AimpUIEventHandler<AimpKeyArgs^> ^_onKeyPress;
            AimpBoolUIEventHandler<AimpBeforeWndProcArgs^> ^_onBeforeWndProc;
            AimpUIEventHandler<AimpAfterWndProcArgs^> ^_onAfterWndProc;
        };
    }
}
