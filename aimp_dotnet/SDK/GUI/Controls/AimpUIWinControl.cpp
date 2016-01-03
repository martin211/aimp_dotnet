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
    }
}
