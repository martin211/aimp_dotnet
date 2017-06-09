// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once
#include "AimpGroupingPreset.h"
#include "AimpDataFilterGroup.h"
#include "SDK\AimpObject.h"
#include "SDK\AimpObjectList.h"
#include "AIMPSDK\AIMPSDK.h"

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
            AimpGroupingPresetStandard(IAIMPMLGroupingPresetStandard *aimpObject);

            virtual property AIMP::SDK::IAimpObjectList<String^>^ Fields
            {
                AIMP::SDK::IAimpObjectList<String^>^ get();

                void set(AIMP::SDK::IAimpObjectList<String^>^ value);
            }

            virtual AimpActionResult GetFilter(IAimpDataFilterGroup ^%filter);
        };
    }
}
