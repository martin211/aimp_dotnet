#pragma once
#include "..\AimpObject.h"
#include "..\..\AIMPSDK\AIMPSDK.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::Collections;
        using namespace System::Collections::Generic;
        using namespace AIMP::SDK::MusicLibrary::DataStorage;
        using namespace AIMP::SDK::MusicLibrary::Presets;

        public ref class AimpGroupingPresets : public AimpObject<IAIMPMLGroupingPresets>, public IAimpGroupingPresets
        {
        public:
            explicit AimpGroupingPresets(IAIMPMLGroupingPresets *aimpObject) : AimpObject(aimpObject)
            {}

            virtual AimpActionResult Add(String^ id, String^ name, IAimpGroupingTreeDataProvider^ provider, IAimpGroupingPreset ^%preset)
            {
                return AimpActionResult::Unexpected;
            }

            virtual AimpActionResult Add(String^ id, String^ name, System::Collections::Generic::IList<String^>^ fieldNames, IAimpGroupingPresetStandard^ %preset)
            {
                return AimpActionResult::Unexpected;
            }

            virtual AimpActionResult Add(System::String^ id, String^ name, String^ fieldName, IAimpGroupingPresetStandard^ %preset)
            {
                return AimpActionResult::Unexpected;
            }

            virtual void BeginUpdate()
            {
                InternalAimpObject->BeginUpdate();
            }

            virtual void EndUpdate()
            {
                InternalAimpObject->EndUpdate();
            }

            virtual AimpActionResult Delete(int index)
            {
                return CheckResult(InternalAimpObject->Delete(index));
            }

            virtual int GetCount(void)
            {
                return InternalAimpObject->GetCount();
            }

            virtual AimpActionResult Get(int index, IAimpGroupingPreset ^%preset)
            {
                return AimpActionResult::Unexpected;
            }

            virtual AimpActionResult Get(int index, IAimpGroupingPresetStandard ^%preset)
            {
                return AimpActionResult::Unexpected;
            }

            virtual AimpActionResult GetById(int index, IAimpGroupingPreset ^%preset)
            {
                return AimpActionResult::Unexpected;
            }

            virtual AimpActionResult GetById(int index, IAimpGroupingPresetStandard ^%preset)
            {
                return AimpActionResult::Unexpected;
            }
        };
    }
}