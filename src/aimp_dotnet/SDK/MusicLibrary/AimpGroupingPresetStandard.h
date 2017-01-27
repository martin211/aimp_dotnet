/* AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 */
#pragma once
#include "..\AimpObject.h"
#include "..\..\AIMPSDK\AIMPSDK.h"
#include "AimpGroupingPreset.h"
#include "..\AimpObjectList.h"
#include "AimpDataFilterGroup.h"

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
