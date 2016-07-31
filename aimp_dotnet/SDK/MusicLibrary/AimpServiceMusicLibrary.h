#pragma once
#include "..\BaseManager.h"
#include "..\..\AIMPSDK\AIMP400\apiMusicLibrary.h"

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

            virtual AimpActionResult GetActiveDataStorage(IAimpExtensionDataStorage ^%obj);

            virtual AimpActionResult GeteActiveGroupingPreset(IAimpGroupingPreset ^%preset);

            virtual AimpActionResult SetActiveStorage(IAimpExtensionDataStorage ^storage);

            //virtual AimpActionResult GetStorage(int index, StorageType storageType, Object ^%obj);

            //virtual AimpActionResult GetStorageById(String ^id, StorageType storageType, Object ^%obj);

            virtual int GetStorageCount();
        };
    }
}