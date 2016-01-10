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
