#pragma once
#include "..\AimpObject.h"
#include "..\..\AIMPSDK\AIMPSDK.h"
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
        private:
            InternalAimpGroupingTreeDataProvider* _internalProvider;

        public:
            explicit AimpGroupingPresets(IAIMPMLGroupingPresets *aimpObject) : AimpObject(aimpObject)
            {
            }

            ~AimpGroupingPresets()
            {
                this->!AimpGroupingPresets();
            }

            !AimpGroupingPresets()
            {
                _aimpObject->Release();
            }

            virtual AimpActionResult Add(String^ id, String^ name, IAimpGroupingTreeDataProvider^ provider, IAimpGroupingPreset^% preset)
            {
                preset = nullptr;

                // create internal wrapper for grouping provider
                _internalProvider = new InternalAimpGroupingTreeDataProvider(provider);
                IAIMPMLGroupingPreset* aimpPreset = NULL;
                IAIMPString* aimpId = AimpExtension::GetAimpString(id);
                IAIMPString* aimpName = AimpExtension::GetAimpString(name);

                AimpActionResult result = CheckResult(InternalAimpObject->Add(aimpId, aimpName, 0, _internalProvider, &aimpPreset));

                aimpId->Release();
                aimpName->Release();

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
                    IAIMPString* s = AimpExtension::GetAimpString(fieldNames[i]);
                    fields->Add(s);
                    //AimpObjectDisposer::AddToBack(s);
                    s->Release();
                }

                IAIMPMLGroupingPresetStandard* standartPreset;
                IAIMPString* aimpId = AimpExtension::GetAimpString(id);
                IAIMPString* aimpName = AimpExtension::GetAimpString(name);

                AimpActionResult result = CheckResult(InternalAimpObject->Add2(aimpId, aimpName, 0, fields, &standartPreset));
                preset = nullptr;

                aimpId->Release();
                aimpName->Release();

                if (result == AimpActionResult::Ok)
                {
                    preset = gcnew AimpGroupingPresetStandard(standartPreset);
                }

                return result;
            }

            virtual AimpActionResult Add(System::String^ id, String^ name, String^ fieldName, IAimpGroupingPresetStandard^ %preset)
            {
                IAIMPMLGroupingPresetStandard* standartPreset;

                IAIMPString* aimpId = AimpExtension::GetAimpString(id);
                IAIMPString* aimpName = AimpExtension::GetAimpString(name);
                IAIMPString* aimpFieldName = AimpExtension::GetAimpString(name);

                AimpActionResult result = CheckResult(InternalAimpObject->Add3(aimpId, aimpName, 0, aimpFieldName, &standartPreset));

                aimpId->Release();
                aimpName->Release();
                aimpFieldName->Release();

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

                IAIMPString* aimpId = AimpExtension::GetAimpString(id);
                AimpActionResult result = CheckResult(InternalAimpObject->GetByID(aimpId, IID_IAIMPMLGroupingPreset, (void**)&p));
                aimpId->Release();

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

                IAIMPString* aimpId = AimpExtension::GetAimpString(id);
                AimpActionResult result = CheckResult(InternalAimpObject->GetByID(aimpId, IID_IAIMPMLGroupingPresetStandard, (void**)&p));
                aimpId->Release();

                if (result == AimpActionResult::Ok)
                {
                    preset = gcnew AimpGroupingPresetStandard(p);
                }

                return result;
            }
        };
    }
}