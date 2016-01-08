#include "..\..\..\Stdafx.h"
#include "AimpUIWinControl.h"

namespace AIMP
{
    namespace SDK
    {
        AimpUIWinControl::AimpUIWinControl(IAIMPUIWinControl *control) : AimpUIControl(control)
        {}

        bool AimpUIWinControl::Focused::get()
        {
            return AimpConverter::GetBool(InternalAimpControl, AIMPUI_WINCONTROL_PROPID_FOCUSED);
        }

        void AimpUIWinControl::Focused::set(bool value)
        {
            AimpConverter::SetBool(InternalAimpControl, AIMPUI_WINCONTROL_PROPID_FOCUSED, value);
        }

        int AimpUIWinControl::TabOrder::get()
        {
            return AimpConverter::GetInt32(InternalAimpControl, AIMPUI_WINCONTROL_PROPID_TABORDER);
        }

        void AimpUIWinControl::TabOrder::set(int value)
        {
            AimpConverter::SetInt32(InternalAimpControl, AIMPUI_WINCONTROL_PROPID_TABORDER, value);
        }

        AimpActionResult AimpUIWinControl::GetControl(AIMP::SDK::GUI::Controls::IAimpUIControl ^control, int index, String ^iid)
        {
            return AimpActionResult::Ok;
        }

        int AimpUIWinControl::GetControlCount()
        {
            return ((IAIMPUIWinControl*)InternalAimpControl)->GetControlCount();
        }

        IntPtr AimpUIWinControl::GetHandle()
        {
            return IntPtr(((IAIMPUIWinControl*)InternalAimpControl)->GetHandle());
        }

        bool AimpUIWinControl::HasHandle()
        {
            return ((IAIMPUIWinControl*)InternalAimpControl)->HasHandle();
        }

        AimpActionResult AimpUIWinControl::SetFocus()
        {
            return CheckResult(((IAIMPUIWinControl*)InternalAimpControl)->SetFocus());
        }


        void AimpUIWinControl::OnEnter::add(AimpUIEventHandler ^onEvent)
        {
            if (this->_onEnter == nullptr)
            {
                this->_onEnter = (AimpUIEventHandler^)Delegate::Combine(this->_onEnter, onEvent);
            }
        }

        void AimpUIWinControl::OnEnter::remove(AimpUIEventHandler ^onEvent)
        {
            if (this->_onEnter != nullptr)
            {
                this->_onEnter = (AimpUIEventHandler^)Delegate::Remove(this->_onEnter, onEvent);
            }
        }

        void AimpUIWinControl::OnEnter::raise(IAimpUIControl ^sender)
        {
            if (this->_onEnter != nullptr)
            {
                this->_onEnter(sender);
            }
        }


        void AimpUIWinControl::OnExit::add(AimpUIEventHandler ^onEvent)
        {
            if (this->_onExit == nullptr)
            {
                this->_onExit = (AimpUIEventHandler^)Delegate::Combine(this->_onExit, onEvent);
            }
        }

        void AimpUIWinControl::OnExit::remove(AimpUIEventHandler ^onEvent)
        {
            if (this->_onExit != nullptr)
            {
                this->_onExit = (AimpUIEventHandler^)Delegate::Remove(this->_onExit, onEvent);
            }
        }

        void AimpUIWinControl::OnExit::raise(IAimpUIControl ^sender)
        {
            if (this->_onExit != nullptr)
            {
                this->_onExit(sender);
            }
        }


        void AimpUIWinControl::OnKeyDown::add(AimpUIEventHandler<AimpKeyboardArgs^> ^onEvent)
        {
            if (this->_onKeyDown == nullptr)
            {
                this->_onKeyDown = (AimpUIEventHandler<AimpKeyboardArgs^>^)Delegate::Combine(this->_onKeyDown, onEvent);
            }
        }

        void AimpUIWinControl::OnKeyDown::remove(AimpUIEventHandler<AimpKeyboardArgs^> ^onEvent)
        {
            if (this->_onKeyDown != nullptr)
            {
                this->_onKeyDown = (AimpUIEventHandler<AimpKeyboardArgs^>^)Delegate::Remove(this->_onKeyDown, onEvent);
            }
        }

        void AimpUIWinControl::OnKeyDown::raise(IAimpUIControl ^sender, AimpKeyboardArgs ^args)
        {
            if (this->_onKeyDown != nullptr)
            {
                this->_onKeyDown(sender, args);
            }
        }


        void AimpUIWinControl::OnKeyUp::add(AimpUIEventHandler<AimpKeyboardArgs^> ^onEvent)
        {
            if (this->_onKeyUp == nullptr)
            {
                this->_onKeyUp = (AimpUIEventHandler<AimpKeyboardArgs^>^)Delegate::Combine(this->_onKeyUp, onEvent);
            }
        }

        void AimpUIWinControl::OnKeyUp::remove(AimpUIEventHandler<AimpKeyboardArgs^> ^onEvent)
        {
            if (this->_onKeyUp != nullptr)
            {
                this->_onKeyUp = (AimpUIEventHandler<AimpKeyboardArgs^>^)Delegate::Remove(this->_onKeyUp, onEvent);
            }
        }

        void AimpUIWinControl::OnKeyUp::raise(IAimpUIControl ^sender, AimpKeyboardArgs ^args)
        {
            if (this->_onKeyUp != nullptr)
            {
                this->_onKeyUp(sender, args);
            }
        }


        void AimpUIWinControl::OnKeyPress::add(AimpUIEventHandler<AimpKeyArgs^> ^onEvent)
        {
            if (this->_onKeyPress == nullptr)
            {
                this->_onKeyPress = (AimpUIEventHandler<AimpKeyArgs^>^)Delegate::Combine(this->_onKeyPress, onEvent);
            }
        }

        void AimpUIWinControl::OnKeyPress::remove(AimpUIEventHandler<AimpKeyArgs^> ^onEvent)
        {
            if (this->_onKeyPress != nullptr)
            {
                this->_onKeyPress = (AimpUIEventHandler<AimpKeyArgs^>^)Delegate::Remove(this->_onKeyPress, onEvent);
            }
        }

        void AimpUIWinControl::OnKeyPress::raise(IAimpUIControl ^sender, AimpKeyArgs ^args)
        {
            if (this->_onKeyPress != nullptr)
            {
                this->_onKeyPress(sender, args);
            }
        }


        void AimpUIWinControl::OnBeforeWndProc::add(AimpBoolUIEventHandler<AimpBeforeWndProcArgs^> ^onEvent)
        {
            if (this->_onBeforeWndProc == nullptr)
            {
                this->_onBeforeWndProc = (AimpBoolUIEventHandler<AimpBeforeWndProcArgs^>^)Delegate::Combine(this->_onBeforeWndProc, onEvent);
            }
        }

        void AimpUIWinControl::OnBeforeWndProc::remove(AimpBoolUIEventHandler<AimpBeforeWndProcArgs^> ^onEvent)
        {
            if (this->_onBeforeWndProc != nullptr)
            {
                this->_onBeforeWndProc = (AimpBoolUIEventHandler<AimpBeforeWndProcArgs^>^)Delegate::Remove(this->_onBeforeWndProc, onEvent);
            }
        }

        bool AimpUIWinControl::OnBeforeWndProc::raise(IAimpUIControl ^sender, AimpBeforeWndProcArgs ^args)
        {
            if (this->_onBeforeWndProc != nullptr)
            {
                return this->_onBeforeWndProc(sender, args);
            }
        }


        void AimpUIWinControl::OnAfterWndProc::add(AimpUIEventHandler<AimpAfterWndProcArgs^> ^onEvent)
        {
            if (this->_onAfterWndProc == nullptr)
            {
                this->_onAfterWndProc = (AimpUIEventHandler<AimpAfterWndProcArgs^>^)Delegate::Combine(this->_onAfterWndProc, onEvent);
            }
        }

        void AimpUIWinControl::OnAfterWndProc::remove(AimpUIEventHandler<AimpAfterWndProcArgs^> ^onEvent)
        {
            if (this->_onAfterWndProc != nullptr)
            {
                this->_onAfterWndProc = (AimpUIEventHandler<AimpAfterWndProcArgs^>^)Delegate::Remove(this->_onAfterWndProc, onEvent);
            }
        }

        void AimpUIWinControl::OnAfterWndProc::raise(IAimpUIControl ^sender, AimpAfterWndProcArgs ^args)
        {
            if (this->_onAfterWndProc != nullptr)
            {
                this->_onAfterWndProc(sender, args);
            }
        }
    }
}
