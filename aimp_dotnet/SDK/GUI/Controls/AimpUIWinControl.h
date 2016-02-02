#pragma once

#include "..\..\AimpConverter.h"
#include "AimpUIControl.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::Drawing;
        using namespace AIMP::SDK::GUI;
        using namespace AIMP::SDK::GUI::Controls;

        public ref class AimpUIWinControl : public AimpUIControl, public IAimpUIWinControl
        {
        public:
            explicit AimpUIWinControl(IAIMPUIWinControl *aimpObject, IAimpServiceUI ^serviceUI);

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

            generic <typename TControl>
            virtual AimpActionResult GetControl(TControl %control, int index);

            virtual int GetControlCount();

            virtual IntPtr GetHandle();

            virtual bool HasHandle();

            virtual AimpActionResult SetFocus();

            virtual event AimpUIControlEventHandler ^OnEnter
            {
                virtual void add(AimpUIControlEventHandler ^onEvent);
                virtual void remove(AimpUIControlEventHandler ^onEvent);
                virtual void raise(IAimpUIControl ^sender);
            }

            virtual event AimpUIControlEventHandler ^OnExit
            {
                virtual void add(AimpUIControlEventHandler ^onEvent);
                virtual void remove(AimpUIControlEventHandler ^onEvent);
                virtual void raise(IAimpUIControl ^sender);
            }

            virtual event AimpUIControlEventHandler<AimpKeyboardArgs^> ^OnKeyDown
            {
                virtual void add(AimpUIControlEventHandler<AimpKeyboardArgs^> ^onEvent);
                virtual void remove(AimpUIControlEventHandler<AimpKeyboardArgs^> ^onEvent);
                virtual void raise(IAimpUIControl ^sender, AimpKeyboardArgs ^args);
            }

            virtual event AimpUIControlEventHandler<AimpKeyboardArgs^> ^OnKeyUp
            {
                virtual void add(AimpUIControlEventHandler<AimpKeyboardArgs^> ^onEvent);
                virtual void remove(AimpUIControlEventHandler<AimpKeyboardArgs^> ^onEvent);
                virtual void raise(IAimpUIControl ^sender, AimpKeyboardArgs ^args);
            }

            virtual event AimpUIControlEventHandler<AimpKeyArgs^> ^OnKeyPress
            {
                virtual void add(AimpUIControlEventHandler<AimpKeyArgs^> ^onEvent);
                virtual void remove(AimpUIControlEventHandler<AimpKeyArgs^> ^onEvent);
                virtual void raise(IAimpUIControl ^sender, AimpKeyArgs ^args);
            }

            virtual event AimpBoolUIControlEventHandler<AimpBeforeWndProcArgs^> ^OnBeforeWndProc
            {
                virtual void add(AimpBoolUIControlEventHandler<AimpBeforeWndProcArgs^> ^onEvent);
                virtual void remove(AimpBoolUIControlEventHandler<AimpBeforeWndProcArgs^> ^onEvent);
                virtual bool raise(IAimpUIControl ^sender, AimpBeforeWndProcArgs ^args);
            }

            virtual event AimpUIControlEventHandler<AimpAfterWndProcArgs^> ^OnAfterWndProc
            {
                virtual void add(AimpUIControlEventHandler<AimpAfterWndProcArgs^> ^onEvent);
                virtual void remove(AimpUIControlEventHandler<AimpAfterWndProcArgs^> ^onEvent);
                virtual void raise(IAimpUIControl ^sender, AimpAfterWndProcArgs ^args);
            }

        internal:
            void OnEnterEvent(IAIMPUIWinControl *sender)
            {
                OnEnter(this);
            }

            void OnExitEvent(IAIMPUIWinControl *sender)
            {
                OnExit(this);
            }

            void OnKeyDownEvent(IAIMPUIWinControl *sender, WORD *key, WORD modifiers)
            {
                OnKeyDown(this, gcnew AimpKeyboardArgs((int)key, (AimpUIModifiers)modifiers));
            }

            void OnKeyUpEvent(IAIMPUIWinControl *sender, WORD *key, WORD modifiers)
            {
                OnKeyUp(this, gcnew AimpKeyboardArgs((int)key, (AimpUIModifiers)modifiers));
            }

            void OnKeyPressEvent(IAIMPUIWinControl *sender, WCHAR *key)
            {
                OnKeyPress(this, gcnew AimpKeyArgs((int)key));
            }

            bool OnBeforeWndProcEvent(DWORD message, WPARAM paramW, LPARAM paramL, LRESULT *resultL)
            {
                AimpBeforeWndProcArgs ^args = gcnew AimpBeforeWndProcArgs(message, paramW, paramL, (int)resultL);
                return OnBeforeWndProc(this, args);
            }

            void OnAfterWndProcEvent(DWORD message, WPARAM paramW, LPARAM paramL, LRESULT *resultL)
            {
                OnAfterWndProc(this, gcnew AimpAfterWndProcArgs(message, paramW, paramL, (int)resultL));
            }
        private:
            AimpUIControlEventHandler ^_onEnter;
            AimpUIControlEventHandler ^_onExit;
            AimpUIControlEventHandler<AimpKeyboardArgs^> ^_onKeyDown;
            AimpUIControlEventHandler<AimpKeyboardArgs^> ^_onKeyUp;
            AimpUIControlEventHandler<AimpKeyArgs^> ^_onKeyPress;
            AimpBoolUIControlEventHandler<AimpBeforeWndProcArgs^> ^_onBeforeWndProc;
            AimpUIControlEventHandler<AimpAfterWndProcArgs^> ^_onAfterWndProc;
        };
    }
}
