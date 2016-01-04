#include "..\..\..\..\Stdafx.h"
#include "AimpUIForm.h"

namespace AIMP
{
    namespace SDK
    {
        AimpUIForm::AimpUIForm(IAIMPUIForm *aimpForm) : AimpUIWinControl(aimpForm)
        {}

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
    }
}
