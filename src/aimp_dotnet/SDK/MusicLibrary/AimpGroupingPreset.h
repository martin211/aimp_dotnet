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
#include "SDK\AimpObject.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace MusicLibrary::DataStorage;
        using namespace MusicLibrary::Presets;

        public ref class AimpGroupingPreset : public AimpObject<IAIMPMLGroupingPreset>, public IAimpGroupingPreset
        {
        public:
            explicit AimpGroupingPreset(IAIMPMLGroupingPreset* preset);

            ~AimpGroupingPreset();

            !AimpGroupingPreset();

            virtual property String^ Custom
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Id
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Name
            {
                String^ get();
                void set(String^ value);
            }
        };
    }
}
