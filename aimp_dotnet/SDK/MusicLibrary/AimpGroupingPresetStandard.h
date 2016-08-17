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
                    System::Collections::Generic::IList<String^>^ result = gcnew System::Collections::Generic::List<String^>();
                    IAIMPObjectList* fields = NULL;
                    if (PropertyListExtension::GetObject(InternalAimpObject, AIMPML_GROUPINGPRESETSTD_PROPID_FIELDS, IID_IAIMPObjectList, (void**)fields) == AimpActionResult::Ok)
                    {
                        if (fields == NULL)
                        {
                            return result;
                        }

                        int count = fields->GetCount();
                        for (int i = 0; i < count; i++)
                        {
                            IAIMPString* str = NULL;
                            fields->GetObject(i, IID_IAIMPString, (void**)str);
                            result->Add(AimpExtension::GetString(str));
                        }
                    }

                    return result;
                }

                void set(System::Collections::Generic::IList<String^>^ value)
                {
                    System::Collections::Generic::IList<String^>^ result;
                    IAIMPObjectList *fields = AimpExtension::MakeObject<IAIMPObjectList>(IID_IAIMPObjectList);
                    int count = value->Count;

                    for (int i = 0; i < count; i++)
                    {
                        fields->Add(AimpExtension::GetAimpString(value[i]));
                    }

                    PropertyListExtension::SetObject(InternalAimpObject, AIMPML_GROUPINGPRESETSTD_PROPID_FIELDS, fields);
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
                    return PropertyListExtension::GetString(InternalAimpObject, AIMPML_GROUPINGPRESET_PROPID_ID);
                }
                void set(String^ value)
                {
                    PropertyListExtension::SetString(InternalAimpObject, AIMPML_GROUPINGPRESET_PROPID_ID, value);
                }
            }

            virtual property String^ Name
            {
                String^ get()
                {
                    return PropertyListExtension::GetString(InternalAimpObject, AIMPML_GROUPINGPRESET_PROPID_NAME);
                }
                void set(String^ value)
                {
                    PropertyListExtension::SetString(InternalAimpObject, AIMPML_GROUPINGPRESET_PROPID_NAME, value);
                }
            }

            virtual AimpActionResult GetFilter(IAimpDataFieldFilter ^%filter)
            {
                return AimpActionResult::NotImplemented;
            }
        };
    }
}