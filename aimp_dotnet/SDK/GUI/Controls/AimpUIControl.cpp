#include "..\..\..\Stdafx.h"
#include "AimpUIControl.h"

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
            AimpConverter::SetObject(_aimpObject, AIMPUI_CONTROL_PROPID_PARENT, IID_IAIMPUIWinControl, (AimpUIWinControl)value->InternalAimpObject);
        }
    }
}
