//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "AimpGroupingPreset.h"
#include "AIMPSDK\AIMPSDK.h"

using namespace MusicLibrary;

namespace AIMP {
    namespace SDK {
        using namespace MusicLibrary::Presets;
        using namespace System;
        using namespace Collections;
        using namespace Generic;
        using namespace MusicLibrary::DataFilter;

        public ref class AimpGroupingPresetStandard :
            public AimpGroupingPreset,
            public IAimpGroupingPresetStandard {
        public:
            AimpGroupingPresetStandard(IAIMPMLGroupingPresetStandard* aimpObject);

            virtual property IAimpObjectList<IAimpSortItem^>^ Fields
            {
                IAimpObjectList<IAimpSortItem^>^ get();

                void set(IAimpObjectList<IAimpSortItem^>^ value);
            }

            virtual TYPED_RESULT(IAimpDataFilterGroup) GetFilter();
        };
    }
}
