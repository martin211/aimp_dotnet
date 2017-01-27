/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
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

