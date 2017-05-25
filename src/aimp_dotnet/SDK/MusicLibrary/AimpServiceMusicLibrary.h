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
#include "SDK\BaseManager.h"
#include "AimpGroupingPresets.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::MusicLibrary;
        using namespace AIMP::SDK::MusicLibrary::DataStorage;
        using namespace AIMP::SDK::MusicLibrary::Presets;

        public ref class AimpServiceMusicLibrary : public AimpBaseManager<IAIMPServiceMusicLibrary>, public IAimpServiceMusicLibrary
        {
        public:
            explicit AimpServiceMusicLibrary(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceMusicLibrary>(core)
            {

            }

            virtual AimpActionResult GetActiveStorage(IAimpDataStorage ^%storage);

            virtual AimpActionResult GetActiveStorage(IAimpGroupingPresets ^%presets);

            virtual AimpActionResult SetActiveStorage(IAimpDataStorage ^storage);

            virtual AimpActionResult SetActiveStorage(IAimpGroupingPresets ^preset);

            virtual AimpActionResult GetStorage(int index, IAimpDataStorage ^%storage);

            virtual AimpActionResult GetStorage(int index, IAimpGroupingPresets ^%preset);

            virtual AimpActionResult GetStorageById(String ^id, IAimpDataStorage ^%storage);

            virtual AimpActionResult GetStorageById(String ^id, IAimpGroupingPresets ^%preset);

            virtual int GetStorageCount();
        };
    }
}
