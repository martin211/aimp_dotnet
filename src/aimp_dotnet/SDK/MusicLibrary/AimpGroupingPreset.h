/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#pragma once
#include "..\AimpObject.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::MusicLibrary::DataStorage;
        using namespace AIMP::SDK::MusicLibrary::Presets;

        public ref class AimpGroupingPreset : public AimpObject<IAIMPMLGroupingPreset>, public IAimpGroupingPreset
        {
        public:
            explicit AimpGroupingPreset(IAIMPMLGroupingPreset *preset);

            ~AimpGroupingPreset();

            !AimpGroupingPreset();

            virtual property String ^Custom
            {
                String ^get();
                void set(String ^value);
            }

            virtual property String ^Id
            {
                String ^get();
                void set(String ^value);
            }

            virtual property String ^Name
            {
                String ^get();
                void set(String ^value);
            }
        };
    }
}
