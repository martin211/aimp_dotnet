/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
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

        public ref class AimpDataStorage : public AimpObject<IAIMPMLDataStorage>, public IAimpDataStorage
        {
        public:
            explicit AimpDataStorage(IAIMPMLDataStorage *aimpDataStorage);

            !AimpDataStorage();

            ~AimpDataStorage();

            virtual property String ^Id
            {
                String ^get();
            }

            virtual property String ^Caption
            {
                String ^get();
            }

            virtual property IAimpGroupingPreset ^GroupingPreset
            {
                IAimpGroupingPreset ^get();
                void set(IAimpGroupingPreset ^value);
            }

        private:
            AimpActionResult GetProperties(IAIMPPropertyList** properties);
        };
    }
}

