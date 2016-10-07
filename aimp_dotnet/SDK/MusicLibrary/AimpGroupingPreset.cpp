#pragma once
#include "Stdafx.h"
#include "AimpGroupingPreset.h"

namespace AIMP
{
    namespace SDK
    {
        AimpGroupingPreset::AimpGroupingPreset(IAIMPMLGroupingPreset *preset) : AimpObject(preset)
        {
        }

        AimpGroupingPreset::~AimpGroupingPreset()
        {
            this->!AimpGroupingPreset();
        }

        AimpGroupingPreset::!AimpGroupingPreset()
        {
            Release();
        }

        void AimpGroupingPreset::Release()
        {
            if (InternalAimpObject != NULL)
            {
                _aimpObject->Release();
                _aimpObject = NULL;
            }
        }

        String ^AimpGroupingPreset::Custom::get()
        {
            return PropertyListExtension::GetString(InternalAimpObject, AIMPML_GROUPINGPRESET_PROPID_CUSTOM);
        }

        void AimpGroupingPreset::Custom::set(String ^value)
        {
            PropertyListExtension::SetString(InternalAimpObject, AIMPML_GROUPINGPRESET_PROPID_CUSTOM, value);
        }


        String ^AimpGroupingPreset::Id::get()
        {
            return PropertyListExtension::GetString(_aimpObject, AIMPML_GROUPINGPRESET_PROPID_ID);
        }

        void AimpGroupingPreset::Id::set(String ^value)
        {
            PropertyListExtension::SetString(InternalAimpObject, AIMPML_GROUPINGPRESET_PROPID_ID, value);
        }


        String ^AimpGroupingPreset::Name::get()
        {
             return PropertyListExtension::GetString(InternalAimpObject, AIMPML_GROUPINGPRESET_PROPID_NAME);
        }

        void AimpGroupingPreset::Name::set(String ^value)
        {
            PropertyListExtension::SetString(InternalAimpObject, AIMPML_GROUPINGPRESET_PROPID_NAME, value);
        }
    }
}
