//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "BaseAimpDataStorage.h"

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace MusicLibrary::DataStorage;
        using namespace MusicLibrary::Presets;

        public ref class AimpDataStorage : public BaseAimpDataStorage<IAIMPMLDataStorage>, public IAimpDataStorage {
        public:
            explicit AimpDataStorage(IAIMPMLDataStorage* aimpDataStorage);
        };
    }
}
