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

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::MusicLibrary;

        public ref class AimpDataStorageManager : 
            public AimpObject<IAIMPMLDataStorageManager>,
            public IAimpDataStorageManager
        {
        public:
            explicit AimpDataStorageManager(IAIMPMLDataStorageManager *manager);

            virtual void BackgroundTaskStarted(int id, System::String ^cartion, AIMP::SDK::ActionManager::IAimpActionEvent ^cancelEvent);

            virtual void BackgroundTaskFinished(int id);

            virtual void Changed();
        };
    }
}
