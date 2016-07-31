#pragma once
#include "..\..\AIMPSDK\AIMP400\apiMusicLibrary.h"
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

