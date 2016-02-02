#include "..\..\..\Stdafx.h"
#include "AimpUIBaseButtonnedEdit.h"
#include "AimpUIBaseButtonnedEditEvents.h"
#include "AimpUIEditButton.h"


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
            AimpUIBaseButtonnedEditEvents *eventHandler = new AimpUIBaseButtonnedEditEvents();
            IAIMPUIEditButton *btn;
            AimpActionResult r = CheckResult(((IAIMPUIBaseButtonnedEdit*)InternalAimpControl)->AddButton(eventHandler, &btn));

            if (r == AimpActionResult::Ok)
            {
                button = gcnew AimpUIEditButton(btn);
                btn->Release();
            }

            return r;
        }

        AimpActionResult AimpUIBaseButtonnedEdit::DeleteButton(IAimpUIEditButton ^button)
        {
            return CheckResult(((IAIMPUIBaseButtonnedEdit*)InternalAimpControl)->DeleteButton2(((AimpUIEditButton^)button)->AimpObject));
        }

        AimpActionResult AimpUIBaseButtonnedEdit::DeleteButton(int index)
        {
            return CheckResult(((IAIMPUIBaseButtonnedEdit*)InternalAimpControl)->DeleteButton(index));
        }

        AimpActionResult AimpUIBaseButtonnedEdit::GetButton(int index, IAimpUIEditButton ^button)
        {
            IAIMPUIEditButton *btn;
            AimpActionResult r = CheckResult(((IAIMPUIBaseButtonnedEdit*)InternalAimpControl)->GetButton(index, &btn));

            if (r == AimpActionResult::Ok)
            {
                button = gcnew AimpUIEditButton(btn);
                btn->Release();
            }

            return r;
        }

        int AimpUIBaseButtonnedEdit::GetButtonCount()
        {
            return ((IAIMPUIBaseButtonnedEdit*)InternalAimpControl)->GetButtonCount();
        }

        void AimpUIBaseButtonnedEdit::OnChanged::add(AimpUIControlEventHandler ^onEvent)
        {
            if (_onChange == nullptr)
            {
                _onChange = (AimpUIControlEventHandler^)Delegate::Combine(_onChange, onEvent);
            }
        }

        void AimpUIBaseButtonnedEdit::OnChanged::remove(AimpUIControlEventHandler ^onEvent)
        {
            if (_onChange != nullptr)
            {
                _onChange = (AimpUIControlEventHandler^)Delegate::Remove(_onChange, onEvent);
            }
        }

        void AimpUIBaseButtonnedEdit::OnChanged::raise(IAimpUIControl ^sender)
        {
            if (_onChange != nullptr)
            {
                _onChange(sender);
            }
        }
    }
}
