// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "AimpGroupingPreset.h"
#include "AIMPSDK\AIMPSDK.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace MusicLibrary::Presets;
        using namespace System;
        using namespace Collections;
        using namespace Generic;
        using namespace MusicLibrary::DataFilter;

        public ref class AimpGroupingPresetStandard :
            public AimpGroupingPreset,
            public IAimpGroupingPresetStandard
        {
        public:
            AimpGroupingPresetStandard(IAIMPMLGroupingPresetStandard* aimpObject);

            virtual property IAimpObjectList<String^>^ Fields
            {
                IAimpObjectList<String^>^ get();

                void set(IAimpObjectList<String^>^ value);
            }

            virtual ActionResultType GetFilter(IAimpDataFilterGroup^% filter);
        };
    }
}
