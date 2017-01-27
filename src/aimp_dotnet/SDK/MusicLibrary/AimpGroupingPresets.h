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
#include "..\..\AIMPSDK\AIMPSDK.h"
#include "AimpGroupingPresetStandard.h"
#include "InternalAimpGroupingTreeDataProvider.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::Collections;
        using namespace System::Collections::Generic;
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::MusicLibrary::DataStorage;
        using namespace AIMP::SDK::MusicLibrary::Presets;

        public ref class AimpGroupingPresets : public AimpObject<IAIMPMLGroupingPresets>, public IAimpGroupingPresets
        {
        private:
            InternalAimpGroupingTreeDataProvider* _internalProvider;

        public:
            explicit AimpGroupingPresets(IAIMPMLGroupingPresets *aimpObject);

            ~AimpGroupingPresets();

            !AimpGroupingPresets();

            virtual AimpActionResult Add(String^ id, String^ name, IAimpGroupingTreeDataProvider^ provider, IAimpGroupingPreset^% preset);

            virtual AimpActionResult Add(String^ id, String^ name, System::Collections::Generic::IList<String^>^ fieldNames, IAimpGroupingPresetStandard^ %preset);

            virtual AimpActionResult Add(System::String^ id, String^ name, String^ fieldName, IAimpGroupingPresetStandard^ %preset);

            virtual void BeginUpdate();

            virtual void EndUpdate();

            virtual AimpActionResult Delete(int index);

            virtual int GetCount(void);

            virtual AimpActionResult Get(int index, IAimpGroupingPreset ^%preset);

            virtual AimpActionResult Get(int index, IAimpGroupingPresetStandard ^%preset);

            virtual AimpActionResult GetById(String^ id, IAimpGroupingPreset ^%preset);

            virtual AimpActionResult GetById(String^ id, IAimpGroupingPresetStandard ^%preset);
        };
    }
}
