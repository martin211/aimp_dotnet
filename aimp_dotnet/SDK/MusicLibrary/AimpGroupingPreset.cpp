#pragma once
#include "..\..\Stdafx.h"
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

        AimpActionResult AimpGroupingPreset::GetProperties(IAIMPPropertyList** properties)
        {
            IAIMPPropertyList *prop = NULL;
            AimpActionResult result = CheckResult(InternalAimpObject->QueryInterface(IID_IAIMPPropertyList, (void**)&prop));
            *properties = prop;
            return result;
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
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                {
                    return PropertyListExtension::GetString(properties, AIMPML_GROUPINGPRESET_PROPID_CUSTOM);
                }
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpGroupingPreset::Custom::set(String ^value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                {
                    PropertyListExtension::SetString(properties, AIMPML_GROUPINGPRESET_PROPID_CUSTOM, value);
                }
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        String ^AimpGroupingPreset::Id::get()
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                {
                    return PropertyListExtension::GetString(properties, AIMPML_GROUPINGPRESET_PROPID_ID);
                }
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpGroupingPreset::Id::set(String ^value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                {
                    PropertyListExtension::SetString(properties, AIMPML_GROUPINGPRESET_PROPID_ID, value);
                }
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        String ^AimpGroupingPreset::Name::get()
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                {
                    return PropertyListExtension::GetString(properties, AIMPML_GROUPINGPRESET_PROPID_NAME);
                }
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpGroupingPreset::Name::set(String ^value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                {
                    PropertyListExtension::SetString(properties, AIMPML_GROUPINGPRESET_PROPID_NAME, value);
                }
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }
    }
}
