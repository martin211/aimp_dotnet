#pragma once
#include "..\..\AIMPSDK\AIMP400\apiMusicLibrary.h"
#include "..\AimpObject.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::Collections::Generic;
        using namespace AIMP::SDK::MusicLibrary::DataStorage;
        using namespace AIMP::SDK::MusicLibrary::Presets;

        public ref class AimpGroupingPresets : public AimpObject<IAIMPMLGroupingPresets>, public IAimpGroupingPresets
        {
            AimpActionResult Add(String ^id, String ^name, IAimpGroupingTreeDataProvider ^provider, IAimpGroupingPreset ^%preset);

            AimpActionResult Add(String ^id, String ^name, IEnumerable<String^> ^fieldNames, IAimpGroupingPresetStandard ^%preset);

            AimpActionResult Add(String ^id, String ^name, String ^fieldName, IAimpGroupingPresetStandard ^%preset);

            void BeginUpdate();

            void EndUpdate();

            AimpActionResult Delete(int index);

            int GetCount();
        };
    }
}