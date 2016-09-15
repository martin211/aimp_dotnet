#pragma once
#include "..\..\Stdafx.h"
#include "..\AimpObject.h"
#include "..\..\AIMPSDK\AIMPSDK.h"
#include "AimpGroupingPreset.h"
#include "AimpDataFieldFilter.h"
#include "..\AimpObjectList.h"

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
            public AimpGroupingPreset,
            public IAimpGroupingPresetStandard
        {
        public:
            AimpGroupingPresetStandard(IAIMPMLGroupingPresetStandard *aimpObject) : AimpGroupingPreset(aimpObject)
            {}

            virtual property AIMP::SDK::IAimpObjectList<String^>^ Fields
            {
                AIMP::SDK::IAimpObjectList<String^>^ get()
                {
                    IAIMPObjectList* fields = NULL;
                    
                    if (CheckResult(InternalAimpObject->GetValueAsObject(AIMPML_GROUPINGPRESETSTD_PROPID_FIELDS, IID_IAIMPObjectList, (void**)&fields)) == AimpActionResult::Ok)
                    {
                        return gcnew AimpObjectList<String^>(fields);
                    }

                    // TODO: Check GetObject
                    //if (PropertyListExtension::GetObject(InternalAimpObject, AIMPML_GROUPINGPRESETSTD_PROPID_FIELDS, IID_IAIMPObjectList, (void**)&fields) == AimpActionResult::Ok)
                    //{
                    //    if (fields == NULL)
                    //    {
                    //        //fields = AimpExtension::MakeObject<IAIMPObjectList>(IID_IAIMPObjectList);
                    //        //PropertyListExtension::SetObject(InternalAimpObject, AIMPML_GROUPINGPRESETSTD_PROPID_FIELDS, fields);
                    //    }
                    //    return gcnew AimpObjectList<String^>(fields);
                    //}

                    return nullptr;
                }

                void set(AIMP::SDK::IAimpObjectList<String^>^ value)
                {
                    System::Collections::Generic::IList<String^>^ result;
                    IAIMPObjectList *fields = AimpExtension::MakeObject<IAIMPObjectList>(IID_IAIMPObjectList);
                    int count = value->Count;

                    for (int i = 0; i < count; i++)
                    {
                        //fields->Add(AimpExtension::GetAimpString(value[i]));
                    }

                    PropertyListExtension::SetObject(InternalAimpObject, AIMPML_GROUPINGPRESETSTD_PROPID_FIELDS, fields);
                }
            }

            virtual AimpActionResult GetFilter(IAimpDataFieldFilter ^%filter)
            {
                return AimpActionResult::NotImplemented;
            }
        };
    }
}