#pragma once
#include "..\..\Stdafx.h"
#include "..\AimpObject.h"
#include "..\..\AIMPSDK\AIMPSDK.h"
#include "AimpGroupingPreset.h"
#include "AimpDataFieldFilter.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::MusicLibrary::Presets;
        using namespace System;
        using namespace System::Collections;
        using namespace System::Collections::Generic;
        using namespace AIMP::SDK::MusicLibrary::DataFilter;

        public ref class AimpGroupingPresetStandard :
            public AimpObject<IAIMPMLGroupingPresetStandard>, 
            public IAimpGroupingPresetStandard,
            public IAimpGroupingPreset
        {
        public:
            AimpGroupingPresetStandard(IAIMPMLGroupingPresetStandard *aimpObject) : AimpObject(aimpObject)
            {}

            virtual property System::Collections::Generic::IList<String^>^ Fields
            {
                System::Collections::Generic::IList<String^>^ get()
                {
                    IAIMPPropertyList *properties = NULL;
                    System::Collections::Generic::IList<String^>^ result;
                    try
                    {
                        if (GetProperties(&properties) == AimpActionResult::Ok)
                        {
                            IAIMPObjectList *fields;
                            if (PropertyListExtension::GetObject(properties, AIMPML_GROUPINGPRESETSTD_PROPID_FIELDS, IID_IAIMPObjectList, (void**)fields) == AimpActionResult::Ok)
                            {
                                int count = fields->GetCount();
                                result = gcnew System::Collections::Generic::List<String^>(count);
                                for (int i = 0; i < count; i++)
                                {
                                    IAIMPString* str;
                                    fields->GetObject(i, IID_IAIMPString, (void**)str);
                                    result->Add(AimpExtension::GetString(str));
                                }
                            }
                        }

                        return nullptr;
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

                void set(System::Collections::Generic::IList<String^>^ value)
                {
                    IAIMPPropertyList *properties = NULL;
                    System::Collections::Generic::IList<String^>^ result;
                    try
                    {
                        if (GetProperties(&properties) == AimpActionResult::Ok)
                        {
                            IAIMPObjectList *fields = AimpExtension::MakeObject<IAIMPObjectList>(IID_IAIMPObjectList);
                            int count = value->Count;

                            for (int i = 0; i < count; i++)
                            {
                                fields->Add(AimpExtension::GetAimpString(value[i]));
                            }

                            PropertyListExtension::SetObject(properties, AIMPML_GROUPINGPRESETSTD_PROPID_FIELDS, fields);
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

            virtual property String^ Custom
            {
                String^ get()
                {
                    return "";
                }
                void set(String^ value)
                {}
            }

            virtual property String^ Id
            {
                String^ get()
                {
                    IAIMPPropertyList *properties = NULL;
                    try
                    {
                        if (GetProperties(&properties) == AimpActionResult::Ok)
                        {
                            return PropertyListExtension::GetString(properties, AIMPML_GROUPINGPRESET_PROPID_ID);
                        }

                        return nullptr;
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
                void set(String^ value)
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
            }

            virtual property String^ Name
            {
                String^ get()
                {
                    IAIMPPropertyList *properties = NULL;
                    try
                    {
                        if (GetProperties(&properties) == AimpActionResult::Ok)
                        {
                            return PropertyListExtension::GetString(properties, AIMPML_GROUPINGPRESET_PROPID_NAME);
                        }

                        return nullptr;
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
                void set(String^ value)
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

            virtual AimpActionResult GetFilter(IAimpDataFieldFilter ^%filter)
            {
                return AimpActionResult::NotImplemented;
            }

        private:
            AimpActionResult GetProperties(IAIMPPropertyList** properties)
            {
                IAIMPPropertyList *prop = NULL;
                AimpActionResult result = CheckResult(InternalAimpObject->QueryInterface(IID_IAIMPPropertyList, (void**)&prop));
                *properties = prop;
                return result;
            }
        };
    }
}