#pragma once
#include "..\AimpObject.h"
#include "..\..\AIMPSDK\AIMPSDK.h"
//#include "AimpGroupingTreeDataProvider.h"
#include "AimpGroupingPresetStandard.h"
#include "InternalAimpGroupingTreeDataProvider.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::Collections;
        using namespace System::Collections::Generic;
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::MusicLibrary::DataStorage;
        using namespace AIMP::SDK::MusicLibrary::Presets;

        public ref class AimpGroupingPresets : public AimpObject<IAIMPMLGroupingPresets>, public IAimpGroupingPresets
        {
        public:
            explicit AimpGroupingPresets(IAIMPMLGroupingPresets *aimpObject) : AimpObject(aimpObject)
            {}

            virtual AimpActionResult Add(String^ id, String^ name, IAimpGroupingTreeDataProvider^ provider, IAimpGroupingPreset^% preset)
            {
                preset = nullptr;

                // create internal wrapper for grouping provider
                InternalAimpGroupingTreeDataProvider* internalProvider = new InternalAimpGroupingTreeDataProvider(provider);
                IAIMPMLGroupingPreset* aimpPreset = NULL;
                AimpActionResult result = CheckResult(InternalAimpObject->Add(AimpExtension::GetAimpString(id), AimpExtension::GetAimpString(name), 0, internalProvider, &aimpPreset));

                if (result == AimpActionResult::Ok)
                {
                    preset = gcnew AimpGroupingPreset(aimpPreset);
                }

                return result;
            }

            virtual AimpActionResult Add(String^ id, String^ name, System::Collections::Generic::IList<String^>^ fieldNames, IAimpGroupingPresetStandard^ %preset)
            {
                IAIMPObjectList* fields = AimpExtension::MakeObject<IAIMPObjectList>(IID_IAIMPObjectList);

                for (int i = 0; i < fieldNames->Count; i++)
                {
                    fields->Add(AimpExtension::GetAimpString(fieldNames[i]));
                }

                IAIMPMLGroupingPresetStandard* standartPreset;
                AimpActionResult result = CheckResult(InternalAimpObject->Add2(AimpExtension::GetAimpString(id), AimpExtension::GetAimpString(name), 0, fields, &standartPreset));
                preset = nullptr;
                if (result == AimpActionResult::Ok)
                {
                    preset = gcnew AimpGroupingPresetStandard(standartPreset);
                }

                return result;
            }

            virtual AimpActionResult Add(System::String^ id, String^ name, String^ fieldName, IAimpGroupingPresetStandard^ %preset)
            {
                IAIMPMLGroupingPresetStandard* standartPreset;
                AimpActionResult result = CheckResult(InternalAimpObject->Add3(AimpExtension::GetAimpString(id), AimpExtension::GetAimpString(name), 0, AimpExtension::GetAimpString(fieldName), &standartPreset));

                preset = nullptr;
                if (result == AimpActionResult::Ok)
                {
                    preset = gcnew AimpGroupingPresetStandard(standartPreset);
                }

                return result;
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
                IAIMPMLGroupingPreset* p = NULL;
                preset = nullptr;

                AimpActionResult result = CheckResult(InternalAimpObject->Get(index, IID_IAIMPMLGroupingPreset, (void**)&p));
                if (result == AimpActionResult::Ok)
                {
                    preset = gcnew AimpGroupingPreset(p);
                }

                return result;
            }

            virtual AimpActionResult Get(int index, IAimpGroupingPresetStandard ^%preset)
            {
                IAIMPMLGroupingPresetStandard* p = NULL;
                preset = nullptr;
                AimpActionResult result = CheckResult(InternalAimpObject->Get(index, IID_IAIMPMLGroupingPresetStandard, (void**)&p));

                if (result == AimpActionResult::Ok)
                {
                    preset = gcnew AimpGroupingPresetStandard(p);
                }

                return result;
            }

            virtual AimpActionResult GetById(String^ id, IAimpGroupingPreset ^%preset)
            {
                IAIMPMLGroupingPreset* p = NULL;
                preset = nullptr;

                AimpActionResult result = CheckResult(InternalAimpObject->GetByID(AimpExtension::GetAimpString(id), IID_IAIMPMLGroupingPreset, (void**)&p));

                if (result == AimpActionResult::Ok)
                {
                    preset = gcnew AimpGroupingPreset(p);
                }

                return result;
            }

            virtual AimpActionResult GetById(String^ id, IAimpGroupingPresetStandard ^%preset)
            {
                IAIMPMLGroupingPresetStandard* p = NULL;
                preset = nullptr;
                AimpActionResult result = CheckResult(InternalAimpObject->GetByID(AimpExtension::GetAimpString(id), IID_IAIMPMLGroupingPresetStandard, (void**)&p));

                if (result == AimpActionResult::Ok)
                {
                    preset = gcnew AimpGroupingPresetStandard(p);
                }

                return result;
            }
        };
    }
}