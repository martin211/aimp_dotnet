//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "AIMPSDK\AIMPSDK.h"
#include "SDK/MusicLibrary/InternalAimpGroupingTreeDataProvider.h"

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace Collections;
        using namespace Generic;
        using namespace SDK;
        using namespace MusicLibrary::DataStorage;
        using namespace MusicLibrary::Presets;

        public ref class AimpGroupingPresets : public AimpObject<IAIMPMLGroupingPresets>, public IAimpGroupingPresets {
        private:
            InternalAimpGroupingTreeDataProvider* _internalProvider;

        public:
            explicit AimpGroupingPresets(IAIMPMLGroupingPresets* aimpObject);

            virtual TYPED_RESULT(IAimpGroupingPreset) Add(String^ id, String^ name,
                                                          IAimpGroupingTreeDataProvider^ provider);

            virtual TYPED_RESULT(IAimpGroupingPresetStandard) Add(String^ id, String^ name,
                                                                  Generic::IList<String^>^ fieldNames);

            virtual TYPED_RESULT(IAimpGroupingPresetStandard) Add(String^ id, String^ name, String^ fieldName);

            virtual void BeginUpdate();

            virtual void EndUpdate();

            virtual ActionResult Delete(int index);

            virtual int GetCount(void);

            generic <class TAimpGroupingPreset>
            virtual AimpActionResult<TAimpGroupingPreset>^ Get(int index);
            generic <class TAimpGroupingPreset>
            virtual AimpActionResult<TAimpGroupingPreset>^ GetById(String^ id);
        };
    }
}
