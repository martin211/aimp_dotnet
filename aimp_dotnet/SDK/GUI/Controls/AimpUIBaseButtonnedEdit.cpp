#include "..\..\..\Stdafx.h"
#include "AimpUIBaseButtonnedEdit.h"


namespace AIMP
{
    namespace SDK
    {
        AimpUIBaseButtonnedEdit::AimpUIBaseButtonnedEdit(IAIMPUIBaseButtonnedEdit *aimpObject, IAimpServiceUI ^serviceUI) : AimpUIBaseEdit(aimpObject, serviceUI)
        { }

        IAimpUIImageList ^AimpUIBaseButtonnedEdit::ButtonsImages::get()
        {
            return nullptr;
        }

        void AimpUIBaseButtonnedEdit::ButtonsImages::set(IAimpUIImageList ^value)
        {}

        AimpActionResult AimpUIBaseButtonnedEdit::AddButton(IAimpUIEditButton ^%button)
        {
            return AimpActionResult::Ok;
        }

        AimpActionResult AimpUIBaseButtonnedEdit::DeleteButton(IAimpUIEditButton ^button)
        {
            return AimpActionResult::Ok;
        }

        AimpActionResult AimpUIBaseButtonnedEdit::DeleteButton(int index, IAimpUIEditButton ^button)
        {
            return AimpActionResult::Ok;
        }

        AimpActionResult AimpUIBaseButtonnedEdit::GetButton(int index, IAimpUIEditButton ^button)
        {
            return AimpActionResult::Ok;
        }

        int AimpUIBaseButtonnedEdit::GetButtonCount()
        {
            return 0;
        }

        void AimpUIBaseButtonnedEdit::OnChanged::add(AimpUIEventHandler ^onEvent)
        {}

        void AimpUIBaseButtonnedEdit::OnChanged::remove(AimpUIEventHandler ^onEvent)
        {}

        void AimpUIBaseButtonnedEdit::OnChanged::raise(IAimpUIControl ^sender)
        {}
    }
}
