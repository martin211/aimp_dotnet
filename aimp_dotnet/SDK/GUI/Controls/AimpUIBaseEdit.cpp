#include "..\..\..\Stdafx.h"
#include "AimpUIBaseEdit.h"


namespace AIMP
{
    namespace SDK
    {
        AimpUIBaseEdit::AimpUIBaseEdit(IAIMPUIBaseEdit *aimpObject, IAimpServiceUI ^serviceUI) : AimpUIWinControl(aimpObject, serviceUI)
        {
        }

        bool AimpUIBaseEdit::Borders::get()
        {
            return AimpConverter::GetBool(InternalAimpControl, AIMPUI_BASEEDIT_PROPID_BORDERS);
        }

        void AimpUIBaseEdit::Borders::set(bool value)
        {
            AimpConverter::SetBool(InternalAimpControl, AIMPUI_BASEEDIT_PROPID_BORDERS, value);
        }

        bool AimpUIBaseEdit::ReadOnly::get()
        {
            return AimpConverter::GetBool(InternalAimpControl, AIMPUI_BASEEDIT_PROPID_READONLY);
        }

        void AimpUIBaseEdit::ReadOnly::set(bool value)
        {
            AimpConverter::SetBool(InternalAimpControl, AIMPUI_BASEEDIT_PROPID_READONLY, value);
        }

        int AimpUIBaseEdit::MaxLength::get()
        {
            return AimpConverter::GetInt32(InternalAimpControl, AIMPUI_BASEEDIT_PROPID_MAXLENGTH);
        }

        void AimpUIBaseEdit::MaxLength::set(int value)
        {
            AimpConverter::SetInt32(InternalAimpControl, AIMPUI_BASEEDIT_PROPID_MAXLENGTH, value);
        }

        int AimpUIBaseEdit::SelStart::get()
        {
            return AimpConverter::GetInt32(InternalAimpControl, AIMPUI_BASEEDIT_PROPID_SELSTART);
        }

        void AimpUIBaseEdit::SelStart::set(int value)
        {
            AimpConverter::SetInt32(InternalAimpControl, AIMPUI_BASEEDIT_PROPID_SELSTART, value);
        }

        int AimpUIBaseEdit::SelLength::get()
        {
            return AimpConverter::GetInt32(InternalAimpControl, AIMPUI_BASEEDIT_PROPID_SELLENGTH);
        }

        void AimpUIBaseEdit::SelLength::set(int value)
        {
            AimpConverter::SetInt32(InternalAimpControl, AIMPUI_BASEEDIT_PROPID_SELLENGTH, value);
        }

        String ^AimpUIBaseEdit::SelText::get()
        {
            return AimpConverter::GetString(InternalAimpControl, AIMPUI_BASEEDIT_PROPID_SELTEXT);
        }

        void AimpUIBaseEdit::SelText::set(String ^value)
        {
            AimpConverter::SetString(InternalAimpControl, AIMPUI_BASEEDIT_PROPID_SELTEXT, value);
        }

        String ^AimpUIBaseEdit::Text::get()
        {
            return AimpConverter::GetString(InternalAimpControl, AIMPUI_BASEEDIT_PROPID_TEXT);
        }

        void AimpUIBaseEdit::Text::set(String ^value)
        {
            AimpConverter::SetString(InternalAimpControl, AIMPUI_BASEEDIT_PROPID_TEXT, value);
        }

        AimpActionResult AimpUIBaseEdit::CopyToClipboard()
        {
            return CheckResult(((IAIMPUIBaseEdit*)InternalAimpControl)->CopyToClipboard());
        }

        AimpActionResult AimpUIBaseEdit::CutToClipboard()
        {
            return CheckResult(((IAIMPUIBaseEdit*)InternalAimpControl)->CopyToClipboard());
        }

        AimpActionResult AimpUIBaseEdit::PasteFromClipboard()
        {
            return CheckResult(((IAIMPUIBaseEdit*)InternalAimpControl)->CopyToClipboard());
        }

        AimpActionResult AimpUIBaseEdit::SelectAll()
        {
            return CheckResult(((IAIMPUIBaseEdit*)InternalAimpControl)->CopyToClipboard());
        }

        AimpActionResult AimpUIBaseEdit::SelectNone()
        {
            return CheckResult(((IAIMPUIBaseEdit*)InternalAimpControl)->CopyToClipboard());
        }
    }
}
