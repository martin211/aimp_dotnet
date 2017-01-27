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
#include "..\BaseManager.h"
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
