//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

namespace AIMP {
    namespace SDK {
        using namespace MusicLibrary;
        using namespace Actions;
        using namespace Actions::Objects;

        public ref class AimpDataStorageManager :
            public AimpObject<IAIMPMLDataStorageManager>,
            public IAimpDataStorageManager {
        public:
            explicit AimpDataStorageManager(IAIMPMLDataStorageManager* manager);

            virtual ActionResult BackgroundTaskStarted(int id, String^ caption, IAimpActionEvent^ cancelEvent);

            virtual ActionResult BackgroundTaskFinished(int id);

            virtual void Changed();
        };
    }
}
