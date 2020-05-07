// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
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
        using namespace MusicLibrary;

        public ref class AimpDataStorageManager :
            public AimpObject<IAIMPMLDataStorageManager>,
            public IAimpDataStorageManager
        {
        public:
            explicit AimpDataStorageManager(IAIMPMLDataStorageManager* manager);

            virtual ActionResultType BackgroundTaskStarted(int id, String^ caption,
                                                           ActionManager::IAimpActionEvent^ cancelEvent);

            virtual ActionResultType BackgroundTaskFinished(int id);

            virtual void Changed();
        };
    }
}
