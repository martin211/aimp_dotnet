#include "..\..\..\..\Stdafx.h"
#include "AimpUIForm.h"

namespace AIMP
{
    namespace SDK
    {
        AimpUIForm::AimpUIForm(IAIMPUIForm *aimpForm) : AimpUIWinControl(aimpForm)
        {
            
        }

        String ^AimpUIForm::Caption::get()
        {
            return AimpConverter::GetString(InternalAimpControl, AIMPUI_FORM_PROPID_CAPTION);
        }

        void AimpUIForm::Caption::set(String ^value)
        {
            AimpConverter::SetString(InternalAimpControl, AIMPUI_FORM_PROPID_CAPTION, value);
        }

        AimpBorderIcon AimpUIForm::AimpBorderIcons::get()
        {
            return (AimpBorderIcon)AimpConverter::GetInt32(InternalAimpControl, AIMPUI_FORM_PROPID_BORDERICONS);
        }

        void AimpUIForm::AimpBorderIcons::set(AimpBorderIcon value)
        {
            AimpConverter::SetInt32(InternalAimpControl, AIMPUI_FORM_PROPID_BORDERICONS, (int)value);
        }

        AimpBorderStyle AimpUIForm::AimpBorderStyle::get()
        {
            return (AIMP::SDK::GUI::Controls::Form::AimpBorderStyle)AimpConverter::GetInt32(InternalAimpControl, AIMPUI_FORM_PROPID_BORDERSTYLE);
        }

        void AimpUIForm::AimpBorderStyle::set(AIMP::SDK::GUI::Controls::Form::AimpBorderStyle value)
        {
            AimpConverter::SetInt32(InternalAimpControl, AIMPUI_FORM_PROPID_BORDERSTYLE, (int)value);
        }

        IntPtr AimpUIForm::Icon::get()
        {
            return IntPtr::Zero;
        }

        void AimpUIForm::Icon::set(IntPtr value)
        {
            AimpConverter::SetInt32(InternalAimpControl, AIMPUI_FORM_PROPID_ICON, value.ToInt32());
        }

        bool AimpUIForm::ShowTasksBar::get()
        {
            return AimpConverter::GetBool(InternalAimpControl, AIMPUI_FORM_PROPID_SHOWONTASKBAR);
        }

        void AimpUIForm::ShowTasksBar::set(bool value)
        {
            AimpConverter::SetBool(InternalAimpControl, AIMPUI_FORM_PROPID_SHOWONTASKBAR, value);
        }

        bool AimpUIForm::CloseByEscape::get()
        {
            return AimpConverter::GetBool(InternalAimpControl, AIMPUI_FORM_PROPID_CLOSEBYESCAPE);
        }

        void AimpUIForm::CloseByEscape::set(bool value)
        {
            AimpConverter::SetBool(InternalAimpControl, AIMPUI_FORM_PROPID_CLOSEBYESCAPE, value);
        }

        int AimpUIForm::Padding::get()
        {
            return AimpConverter::GetInt32(InternalAimpControl, AIMPUI_FORM_PROPID_PADDING);
        }

        void AimpUIForm::Padding::set(int value)
        {
            AimpConverter::SetInt32(InternalAimpControl, AIMPUI_FORM_PROPID_PADDING, value);
        }

        AimpActionResult AimpUIForm::Close()
        {
            return CheckResult(((IAIMPUIForm*)InternalAimpControl)->Close());
        }

        AimpActionResult AimpUIForm::GetFocusedControl(IAimpUIWinControl ^%control)
        {
            IAIMPUIWinControl *aimpControl;
            AimpActionResult result = CheckResult(((IAIMPUIForm*)InternalAimpControl)->GetFocusedControl(&aimpControl));

            if (result != AimpActionResult::Ok)
            {
                return result;
            }

            // TODO: create control.

            return result;
        }

        AimpActionResult AimpUIForm::Localized()
        {
            return CheckResult(((IAIMPUIForm*)InternalAimpControl)->Localize());
        }

        AimpActionResult AimpUIForm::Release(bool postponed)
        {
            return CheckResult(((IAIMPUIForm*)InternalAimpControl)->Release(postponed));
        }

        AimpModalResult AimpUIForm::ShowModal()
        {
            return (AimpModalResult)((IAIMPUIForm*)InternalAimpControl)->ShowModal();
        }

        void AimpUIForm::Show()
        {
            Visible = true;
        }


        void AimpUIForm::OnActivated::add(AimpUIEventHandler ^onEvent)
        {
            if (this->_onActivated == nullptr)
            {
                this->_onActivated = (AimpUIEventHandler^)Delegate::Combine(this->_onActivated, onEvent);
            }
        }

        void AimpUIForm::OnActivated::remove(AimpUIEventHandler ^onEvent)
        {
            if (this->_onActivated != nullptr)
            {
                this->_onActivated = (AimpUIEventHandler^)Delegate::Remove(this->_onActivated, onEvent);
            }
            
        }

        void AimpUIForm::OnActivated::raise(IAimpUIControl ^sender)
        {
            if (this->_onActivated != nullptr)
            {
                this->_onActivated(sender);
            }
        }


        void AimpUIForm::OnDeactivated::add(AimpUIEventHandler ^onEvent)
        {
            if (this->_onDeactivated == nullptr)
            {
                this->_onDeactivated = (AimpUIEventHandler^)Delegate::Combine(this->_onDeactivated, onEvent);
            }
        }

        void AimpUIForm::OnDeactivated::remove(AimpUIEventHandler ^onEvent)
        {
            if (this->_onDeactivated != nullptr)
            {
                this->_onDeactivated = (AimpUIEventHandler^)Delegate::Remove(this->_onDeactivated, onEvent);
            }

        }

        void AimpUIForm::OnDeactivated::raise(IAimpUIControl ^sender)
        {
            if (this->_onDeactivated != nullptr)
            {
                this->_onDeactivated(sender);
            }
        }


        void AimpUIForm::OnCreated::add(AimpUIEventHandler ^onEvent)
        {
            if (this->_onCreated == nullptr)
            {
                this->_onCreated = (AimpUIEventHandler^)Delegate::Combine(this->_onCreated, onEvent);
            }
        }

        void AimpUIForm::OnCreated::remove(AimpUIEventHandler ^onEvent)
        {
            if (this->_onCreated != nullptr)
            {
                this->_onCreated = (AimpUIEventHandler^)Delegate::Remove(this->_onCreated, onEvent);
            }

        }

        void AimpUIForm::OnCreated::raise(IAimpUIControl ^sender)
        {
            if (this->_onCreated != nullptr)
            {
                this->_onCreated(sender);
            }
        }


        void AimpUIForm::OnDestroyed::add(AimpUIEventHandler ^onEvent)
        {
            if (this->_onDestroyed == nullptr)
            {
                this->_onDestroyed = (AimpUIEventHandler^)Delegate::Combine(this->_onDestroyed, onEvent);
            }
        }

        void AimpUIForm::OnDestroyed::remove(AimpUIEventHandler ^onEvent)
        {
            if (this->_onDestroyed != nullptr)
            {
                this->_onDestroyed = (AimpUIEventHandler^)Delegate::Remove(this->_onDestroyed, onEvent);
            }

        }

        void AimpUIForm::OnDestroyed::raise(IAimpUIControl ^sender)
        {
            if (this->_onDestroyed != nullptr)
            {
                this->_onDestroyed(sender);
            }
        }


        void AimpUIForm::OnLocalize::add(AimpUIEventHandler ^onEvent)
        {
            if (this->_onLocalize == nullptr)
            {
                this->_onLocalize = (AimpUIEventHandler^)Delegate::Combine(this->_onLocalize, onEvent);
            }
        }

        void AimpUIForm::OnLocalize::remove(AimpUIEventHandler ^onEvent)
        {
            if (this->_onLocalize != nullptr)
            {
                this->_onLocalize = (AimpUIEventHandler^)Delegate::Remove(this->_onLocalize, onEvent);
            }

        }

        void AimpUIForm::OnLocalize::raise(IAimpUIControl ^sender)
        {
            if (this->_onLocalize != nullptr)
            {
                this->_onLocalize(sender);
            }
        }


        void AimpUIForm::OnCloseQuery::add(AimpUIEventHandler<AimpFormCloseQueryArgs^> ^onEvent)
        {
            if (this->_onCloseQuery == nullptr)
            {
                this->_onCloseQuery = (AimpUIEventHandler<AimpFormCloseQueryArgs^>^)Delegate::Combine(this->_onLocalize, onEvent);
            }
        }

        void AimpUIForm::OnCloseQuery::remove(AimpUIEventHandler<AimpFormCloseQueryArgs^> ^onEvent)
        {
            if (this->_onCloseQuery != nullptr)
            {
                this->_onCloseQuery = (AimpUIEventHandler<AimpFormCloseQueryArgs^>^)Delegate::Remove(this->_onLocalize, onEvent);
            }

        }

        void AimpUIForm::OnCloseQuery::raise(IAimpUIControl ^sender, AimpFormCloseQueryArgs^ args)
        {
            if (this->_onCloseQuery != nullptr)
            {
                this->_onCloseQuery(sender, args);
            }
        }


        void AimpUIForm::OnShortCut::add(AimpUIEventHandler<AimpFormShortCutArgs^> ^onEvent)
        {
            if (this->_onShortCut == nullptr)
            {
                this->_onShortCut = (AimpUIEventHandler<AimpFormShortCutArgs^>^)Delegate::Combine(this->_onShortCut, onEvent);
            }
        }

        void AimpUIForm::OnShortCut::remove(AimpUIEventHandler<AimpFormShortCutArgs^> ^onEvent)
        {
            if (this->_onShortCut != nullptr)
            {
                this->_onShortCut = (AimpUIEventHandler<AimpFormShortCutArgs^>^)Delegate::Remove(this->_onShortCut, onEvent);
            }

        }

        void AimpUIForm::OnShortCut::raise(IAimpUIControl ^sender, AimpFormShortCutArgs^ args)
        {
            if (this->_onShortCut != nullptr)
            {
                this->_onShortCut(sender, args);
            }
        }
    }
}
