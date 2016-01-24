#include "..\..\..\Stdafx.h"
#include "AimpUIControl.h"
#include "AimpUIWinControl.h"


namespace AIMP
{
    namespace SDK
    {
        AimpUIControl::AimpUIControl(IAIMPUIControl *aimpObject, IAimpServiceUI ^serviceUI)
            : AimpObject(aimpObject)
        {
            _serviceUI = serviceUI;
        }

        String ^AimpUIControl::CustomData::get()
        {
            return AimpConverter::GetString(_aimpObject, AIMPUI_CONTROL_PROPID_CUSTOM);
        }

        void AimpUIControl::CustomData::set(String ^value)
        {
            AimpConverter::SetString(_aimpObject, AIMPUI_CONTROL_PROPID_CUSTOM, value);
        }

        bool AimpUIControl::Enabled::get()
        {
            return AimpConverter::GetBool(_aimpObject, AIMPUI_CONTROL_PROPID_ENABLED);
        }

        void AimpUIControl::Enabled::set(bool value)
        {
            AimpConverter::SetBool(_aimpObject, AIMPUI_CONTROL_PROPID_ENABLED, value);
        }

        String ^AimpUIControl::Hint::get()
        {
            return AimpConverter::GetString(_aimpObject, AIMPUI_CONTROL_PROPID_HINT);
        }

        void AimpUIControl::Hint::set(String ^value)
        {
            AimpConverter::SetString(_aimpObject, AIMPUI_CONTROL_PROPID_HINT, value);
        }

        String ^AimpUIControl::Name::get()
        {
            return AimpConverter::GetString(_aimpObject, AIMPUI_CONTROL_PROPID_NAME);
        }

        void AimpUIControl::Name::set(String ^value)
        {
            AimpConverter::SetString(_aimpObject, AIMPUI_CONTROL_PROPID_NAME, value);
        }

        AIMP::SDK::GUI::Controls::IAimpUIWinControl ^AimpUIControl::Parent::get()
        {
            IAIMPUIWinControl *parent;
            AimpConverter::GetObject(_aimpObject, AIMPUI_CONTROL_PROPID_PARENT, IID_IAIMPUIWinControl, (void**)&parent);

            // TODO:  Complete it
            return nullptr;
        }

        void AimpUIControl::Parent::set(AIMP::SDK::GUI::Controls::IAimpUIWinControl ^value)
        {
            AimpConverter::SetObject(_aimpObject, AIMPUI_CONTROL_PROPID_PARENT, ((AimpUIWinControl^)value)->InternalAimpObject);
        }

        IAimpUIPopupMenu ^AimpUIControl::PopupMenu::get()
        {
            return nullptr;
        }

        void AimpUIControl::PopupMenu::set(IAimpUIPopupMenu ^value)
        {
            
        }

        bool AimpUIControl::Visible::get()
        {
            return AimpConverter::GetBool(_aimpObject, AIMPUI_CONTROL_PROPID_VISIBLE);
        }

        void AimpUIControl::Visible::set(bool value)
        {
            AimpConverter::SetBool(_aimpObject, AIMPUI_CONTROL_PROPID_VISIBLE, value);
        }

        AimpActionResult AimpUIControl::GetPlacement(AimpUIControlPlacement %placement)
        {
            TAIMPUIControlPlacement *aimpPlacement;
            AimpActionResult result = CheckResult(_aimpObject->GetPlacement(&aimpPlacement));

            if (result != AimpActionResult::Ok)
            {
                return result;
            }

            placement = AimpUIControlPlacement(
                (AimpUIControlAlignment)aimpPlacement->Alignment,
                System::Drawing::Rectangle(
                    aimpPlacement->AlignmentMargins.left,
                    aimpPlacement->AlignmentMargins.top,
                    aimpPlacement->AlignmentMargins.right - aimpPlacement->AlignmentMargins.left,
                    aimpPlacement->AlignmentMargins.top - aimpPlacement->AlignmentMargins.bottom),
                System::Drawing::Rectangle(
                    aimpPlacement->Anchors.left,
                    aimpPlacement->Anchors.top,
                    aimpPlacement->Anchors.right - aimpPlacement->Anchors.left,
                    aimpPlacement->Anchors.top - aimpPlacement->Anchors.bottom),
                System::Drawing::Rectangle(
                    aimpPlacement->Bounds.left,
                    aimpPlacement->Bounds.top,
                    aimpPlacement->Bounds.right - aimpPlacement->Bounds.left,
                    aimpPlacement->Bounds.top - aimpPlacement->Bounds.bottom)
                );

            return result;
        }

        AimpActionResult AimpUIControl::GetPlacementConstraints(AimpUIControlPlacementConstraints %placementConstraints)
        {
            TAIMPUIControlPlacementConstraints *aimpPlacement;
            AimpActionResult result = CheckResult(_aimpObject->GetPlacementConstraints(&aimpPlacement));

            if (result != AimpActionResult::Ok)
            {
                return result;
            }
            placementConstraints = AimpUIControlPlacementConstraints(aimpPlacement->MaxHeight, aimpPlacement->MaxWidth, aimpPlacement->MinHeight, aimpPlacement->MinWidth);

            return result;
        }

        AimpActionResult AimpUIControl::SetPlacement(AIMP::SDK::GUI::Controls::AimpUIControlPlacement placement)
        {
            TAIMPUIControlPlacement *pl = new TAIMPUIControlPlacement();
            pl->Alignment = (TAIMPUIControlAlignment)placement.Alignment;
            pl->AlignmentMargins = RECT();
            pl->AlignmentMargins.left = placement.AlignmentMargins.Left;
            pl->AlignmentMargins.right = placement.AlignmentMargins.Right;
            pl->AlignmentMargins.bottom = placement.AlignmentMargins.Bottom;
            pl->AlignmentMargins.top = placement.AlignmentMargins.Top;

            pl->Anchors = RECT();
            pl->Anchors.left = placement.Anchors.Left;
            pl->Anchors.right = placement.Anchors.Right;
            pl->Anchors.bottom = placement.Anchors.Bottom;
            pl->Anchors.top = placement.Anchors.Top;

            pl->Bounds = RECT();
            pl->Bounds.left = placement.Bounds.Left;
            pl->Bounds.right = placement.Bounds.Right;
            pl->Bounds.bottom = placement.Bounds.Bottom;
            pl->Bounds.top = placement.Bounds.Top;

            return CheckResult(_aimpObject->SetPlacement(pl));
        }

        AimpActionResult AimpUIControl::SetPlacementConstraints(AimpUIControlPlacementConstraints placementConstraints)
        {
            TAIMPUIControlPlacementConstraints *pl = new TAIMPUIControlPlacementConstraints();

            pl->MaxHeight = placementConstraints.MaxHeight;
            pl->MaxWidth = placementConstraints.MaxWidth;
            pl->MinHeight = placementConstraints.MinHeight;
            pl->MinWidth = placementConstraints.MinWidth;

            return CheckResult(_aimpObject->SetPlacementConstraints(pl));
        }

        AimpActionResult AimpUIControl::ClientToScreen(Point %point)
        {
            POINT *p = NULL;
            AimpActionResult result = CheckResult(_aimpObject->ClientToScreen(p));

            if (result != AimpActionResult::Ok)
            {
                return result;
            }

            point = Point(p->x, p->y);
            return result;
        }

        AimpActionResult AimpUIControl::ScreenToClient(Point %point)
        {
            POINT *p = NULL;
            AimpActionResult result = CheckResult(_aimpObject->ScreenToClient(p));

            if (result != AimpActionResult::Ok)
            {
                return result;
            }

            point = Point(p->x, p->y);
            return result;
        }

        AimpActionResult AimpUIControl::Invalidate()
        {
            return CheckResult(_aimpObject->Invalidate());
        }

        AimpActionResult AimpUIControl::PaintTo(IntPtr parent, int x, int y)
        {
            return CheckResult(_aimpObject->PaintTo((HDC)parent.ToPointer(), x, y));
        }


        void AimpUIControl::OnMouseDoubleClick::add(AimpUIEventHandler<AimpMouseClickArgs^> ^onEvent)
        {
            if (this->_mouseDoubleClick == nullptr)
            {
                this->_mouseDoubleClick = (AimpUIEventHandler<AimpMouseClickArgs^>^)Delegate::Combine(this->_mouseDoubleClick, onEvent);
            }
        }

        void AimpUIControl::OnMouseDoubleClick::remove(AimpUIEventHandler<AimpMouseClickArgs^> ^onEvent)
        {
            if (this->_mouseDoubleClick != nullptr)
            {
                this->_mouseDoubleClick = (AimpUIEventHandler<AimpMouseClickArgs^>^)Delegate::Remove(this->_mouseDoubleClick, onEvent);
            }
        }

        void AimpUIControl::OnMouseDoubleClick::raise(IAimpUIControl ^sender, AimpMouseClickArgs ^args)
        {
            if (this->_mouseDoubleClick != nullptr)
            {
                this->_mouseDoubleClick(sender, args);
            }
        }


        void AimpUIControl::OnMouseDown::add(AimpUIEventHandler<AimpMouseClickArgs^> ^onEvent)
        {
            if (this->_mouseDown == nullptr)
            {
                this->_mouseDown = (AimpUIEventHandler<AimpMouseClickArgs^>^)Delegate::Combine(this->_mouseDown, onEvent);
            }
        }

        void AimpUIControl::OnMouseDown::remove(AimpUIEventHandler<AimpMouseClickArgs^> ^onEvent)
        {
            if (this->_mouseDown != nullptr)
            {
                this->_mouseDown = (AimpUIEventHandler<AimpMouseClickArgs^>^)Delegate::Remove(this->_mouseDown, onEvent);
            }
        }

        void AimpUIControl::OnMouseDown::raise(IAimpUIControl ^sender, AimpMouseClickArgs ^args)
        {
            if (this->_mouseDown != nullptr)
            {
                this->_mouseDown(sender, args);
            }
        }


        void AimpUIControl::OnMouseUp::add(AimpUIEventHandler<AimpMouseClickArgs^> ^onEvent)
        {
            if (this->_mouseUp == nullptr)
            {
                this->_mouseUp = (AimpUIEventHandler<AimpMouseClickArgs^>^)Delegate::Combine(this->_mouseUp, onEvent);
            }
        }

        void AimpUIControl::OnMouseUp::remove(AimpUIEventHandler<AimpMouseClickArgs^> ^onEvent)
        {
            if (this->_mouseUp != nullptr)
            {
                this->_mouseUp = (AimpUIEventHandler<AimpMouseClickArgs^>^)Delegate::Remove(this->_mouseUp, onEvent);
            }
        }

        void AimpUIControl::OnMouseUp::raise(IAimpUIControl ^sender, AimpMouseClickArgs ^args)
        {
            if (this->_mouseUp != nullptr)
            {
                this->_mouseUp(sender, args);
            }
        }


        void AimpUIControl::OnMouseLeave::add(AimpUIEventHandler ^onEvent)
        {
            if (this->_mouseLeave == nullptr)
            {
                this->_mouseLeave = (AimpUIEventHandler^)Delegate::Combine(this->_mouseLeave, onEvent);
            }
        }

        void AimpUIControl::OnMouseLeave::remove(AimpUIEventHandler ^onEvent)
        {
            if (this->_mouseLeave != nullptr)
            {
                this->_mouseLeave = (AimpUIEventHandler^)Delegate::Remove(this->_mouseLeave, onEvent);
            }
        }

        void AimpUIControl::OnMouseLeave::raise(IAimpUIControl ^sender)
        {
            if (this->_mouseLeave != nullptr)
            {
                this->_mouseLeave(sender);
            }
        }


        void AimpUIControl::OnMouseMove::add(AimpUIEventHandler<AimpMouseMoveArgs^> ^onEvent)
        {
            if (this->_mouseMove == nullptr)
            {
                this->_mouseMove = (AimpUIEventHandler<AimpMouseMoveArgs^>^)Delegate::Combine(this->_mouseMove, onEvent);
            }
        }

        void AimpUIControl::OnMouseMove::remove(AimpUIEventHandler<AimpMouseMoveArgs^> ^onEvent)
        {
            if (this->_mouseMove != nullptr)
            {
                this->_mouseMove = (AimpUIEventHandler<AimpMouseMoveArgs^>^)Delegate::Remove(this->_mouseMove, onEvent);
            }
        }

        void AimpUIControl::OnMouseMove::raise(IAimpUIControl ^sender, AimpMouseMoveArgs ^args)
        {
            if (this->_mouseMove != nullptr)
            {
                this->_mouseMove(sender, args);
            }
        }


        void AimpUIControl::OnMouseWheel::add(AimpUIEventHandler ^onEvent)
        {
            if (this->_mouseWheel == nullptr)
            {
                this->_mouseWheel = (AimpUIEventHandler^)Delegate::Combine(this->_mouseWheel, onEvent);
            }
        }

        void AimpUIControl::OnMouseWheel::remove(AimpUIEventHandler ^onEvent)
        {
            if (this->_mouseWheel != nullptr)
            {
                this->_mouseWheel = (AimpUIEventHandler^)Delegate::Remove(this->_mouseWheel, onEvent);
            }
        }

        void AimpUIControl::OnMouseWheel::raise(IAimpUIControl ^sender)
        {
            if (this->_mouseWheel != nullptr)
            {
                this->_mouseWheel(sender);
            }
        }


        void AimpUIControl::OnBoundsChanged::add(AimpUIEventHandler ^onEvent)
        {
            if (this->_boundsChanged == nullptr)
            {
                this->_boundsChanged = (AimpUIEventHandler^)Delegate::Combine(this->_boundsChanged, onEvent);
            }
        }

        void AimpUIControl::OnBoundsChanged::remove(AimpUIEventHandler ^onEvent)
        {
            if (this->_boundsChanged != nullptr)
            {
                this->_boundsChanged = (AimpUIEventHandler^)Delegate::Remove(this->_boundsChanged, onEvent);
            }
        }

        void AimpUIControl::OnBoundsChanged::raise(IAimpUIControl ^sender)
        {
            if (this->_boundsChanged != nullptr)
            {
                this->_boundsChanged(sender);
            }
        }


        void AimpUIControl::OnContextPopup::add(AimpBoolUIEventHandler<AimpContextPopupArgs^> ^onEvent)
        {
            if (this->_contextPopup == nullptr)
            {
                this->_contextPopup = (AimpBoolUIEventHandler<AimpContextPopupArgs^>^)Delegate::Combine(this->_contextPopup, onEvent);
            }
        }

        void AimpUIControl::OnContextPopup::remove(AimpBoolUIEventHandler<AimpContextPopupArgs^> ^onEvent)
        {
            if (this->_contextPopup != nullptr)
            {
                this->_contextPopup = (AimpBoolUIEventHandler<AimpContextPopupArgs^>^)Delegate::Remove(this->_contextPopup, onEvent);
            }
        }

        bool AimpUIControl::OnContextPopup::raise(IAimpUIControl ^sender, AimpContextPopupArgs ^args)
        {
            if (this->_contextPopup != nullptr)
            {
                return this->_contextPopup(sender, args);
            }

            return false;
        }
    }
}
