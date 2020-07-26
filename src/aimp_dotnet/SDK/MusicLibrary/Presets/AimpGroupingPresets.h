// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "SDK\AimpObject.h"
#include "AIMPSDK\AIMPSDK.h"
#include "SDK/MusicLibrary/InternalAimpGroupingTreeDataProvider.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace Collections;
        using namespace Generic;
        using namespace SDK;
        using namespace MusicLibrary::DataStorage;
        using namespace MusicLibrary::Presets;

        public ref class AimpGroupingPresets : public AimpObject<IAIMPMLGroupingPresets>, public IAimpGroupingPresets
        {
        private:
            InternalAimpGroupingTreeDataProvider* _internalProvider;

        public:
            explicit AimpGroupingPresets(IAIMPMLGroupingPresets* aimpObject);

            virtual TYPED_RESULT(IAimpGroupingPreset) Add(String^ id, String^ name, IAimpGroupingTreeDataProvider^ provider);

            virtual TYPED_RESULT(IAimpGroupingPresetStandard) Add(String^ id, String^ name, Generic::IList<String^>^ fieldNames);

            virtual TYPED_RESULT(IAimpGroupingPresetStandard) Add(String^ id, String^ name, String^ fieldName);

            virtual void BeginUpdate();

            virtual void EndUpdate();

            virtual ActionResult Delete(int index);

            virtual int GetCount(void);

            virtual TYPED_RESULT(IAimpGroupingPreset) GetPreset(int index);

            virtual TYPED_RESULT(IAimpGroupingPresetStandard) GetStandardPreset(int index);

            virtual TYPED_RESULT(IAimpGroupingPreset) GetPresetById(String^ id);

            virtual TYPED_RESULT(IAimpGroupingPresetStandard) GetStandardPresetById(String^ id);
        };
    }
}
