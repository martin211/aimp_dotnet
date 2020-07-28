// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "SDK\BaseManager.h"

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace MusicLibrary;
        using namespace DataStorage;
        using namespace Presets;

        public ref class AimpServiceMusicLibrary : public BaseAimpService<IAIMPServiceMusicLibrary>,
                                                   public IAimpServiceMusicLibrary {
        public:
            explicit AimpServiceMusicLibrary(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceMusicLibrary>(core) {
            }

            virtual TYPED_RESULT(IAimpDataStorage) GetActiveStorage();

            virtual TYPED_RESULT(IAimpGroupingPresets) GetActiveGroupingPresets();

            virtual ActionResult SetActiveStorage(IAimpDataStorage^ storage);

            virtual ActionResult SetActiveStorage(IAimpGroupingPresets^ preset);

            virtual TYPED_RESULT(IAimpDataStorage) GetStorage(int index);

            virtual TYPED_RESULT(IAimpGroupingPresets) GetGroupingPresets(int index);

            virtual TYPED_RESULT(IAimpDataStorage) GetStorageById(String^ id);

            virtual TYPED_RESULT(IAimpGroupingPresets) GetGroupingPresetsById(String^ id);

            virtual int GetStorageCount();
        protected:
            IAIMPServiceMusicLibrary* GetAimpService() override;
        };
    }
}
