// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "SDK\BaseManager.h"
#include "AimpGroupingPresets.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace MusicLibrary;
        using namespace DataStorage;
        using namespace Presets;

        public ref class AimpServiceMusicLibrary : public BaseAimpService<IAIMPServiceMusicLibrary>,
                                                   public IAimpServiceMusicLibrary
        {
        public:
            explicit AimpServiceMusicLibrary(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceMusicLibrary>(core)
            {
            }

            virtual ActionResultType GetActiveStorage(IAimpDataStorage^% storage);

            virtual ActionResultType GetActiveStorage(IAimpGroupingPresets^% presets);

            virtual ActionResultType SetActiveStorage(IAimpDataStorage^ storage);

            virtual ActionResultType SetActiveStorage(IAimpGroupingPresets^ preset);

            virtual ActionResultType GetStorage(int index, IAimpDataStorage^% storage);

            virtual ActionResultType GetStorage(int index, IAimpGroupingPresets^% preset);

            virtual ActionResultType GetStorageById(String^ id, IAimpDataStorage^% storage);

            virtual ActionResultType GetStorageById(String^ id, IAimpGroupingPresets^% preset);

            virtual int GetStorageCount();
        protected:
            IAIMPServiceMusicLibrary* GetAimpService() override;
        };
    }
}
