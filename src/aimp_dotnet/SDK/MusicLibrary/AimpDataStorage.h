// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
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

        public ref class AimpDataStorage : public AimpObject<IAIMPMLDataStorage>, public IAimpDataStorage
        {
        public:
            explicit AimpDataStorage(IAIMPMLDataStorage* aimpDataStorage);

            virtual property String^ Id
            {
                String^ get();
            }

            virtual property String^ Caption
            {
                String^ get();
            }

            virtual property IAimpGroupingPreset^ GroupingPreset
            {
                IAimpGroupingPreset^ get();
                void set(IAimpGroupingPreset^ value);
            }

        private:
            ActionResultType GetProperties(IAIMPPropertyList** properties);
        };
    }
}
