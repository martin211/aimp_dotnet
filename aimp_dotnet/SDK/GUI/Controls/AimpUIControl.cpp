#include "..\..\..\Stdafx.h"
#include "AimpUIControl.h"
#include "AimpUIWinControl.h"

namespace AIMP
{
    namespace SDK
    {
        AimpUIControl::AimpUIControl(IAIMPUIControl *aimpObject) : AimpObject(aimpObject)
        {
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
                RectangleF(
                    aimpPlacement->AlignmentMargins.left,
                    aimpPlacement->AlignmentMargins.top,
                    aimpPlacement->AlignmentMargins.right - aimpPlacement->AlignmentMargins.left,
                    aimpPlacement->AlignmentMargins.top - aimpPlacement->AlignmentMargins.bottom),
                RectangleF(
                    aimpPlacement->Anchors.left,
                    aimpPlacement->Anchors.top,
                    aimpPlacement->Anchors.right - aimpPlacement->Anchors.left,
                    aimpPlacement->Anchors.top - aimpPlacement->Anchors.bottom),
                RectangleF(
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
            //_aimpObject->SetPlacement();
            return AimpActionResult::Ok;
        }

        AimpActionResult AimpUIControl::SetPlacementConstraints(AimpUIControlPlacementConstraints placementConstraints)
        {
            return AimpActionResult::Ok;
        }

        AimpActionResult AimpUIControl::ClientToScreen(PointF %point)
        {
            PointF ^p = gcnew PointF();
            point = *p;
            return AimpActionResult::Ok;
        }

        AimpActionResult AimpUIControl::ScreenToClient(PointF %point)
        {
            PointF ^p = gcnew PointF();
            point = *p;
            return AimpActionResult::Ok;
        }

        AimpActionResult AimpUIControl::Invalidate()
        {
            return AimpActionResult::Ok;
        }

        AimpActionResult AimpUIControl::PaintTo(IntPtr parent, int x, int y)
        {
            return AimpActionResult::Ok;
        }
    }
}
