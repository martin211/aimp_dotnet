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

            virtual AimpActionResult GetActiveDataStorage(IAimpDataStorage ^%storage);

            virtual AimpActionResult GetActiveDataStorage(IAimpGroupingPresets ^%preset);

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