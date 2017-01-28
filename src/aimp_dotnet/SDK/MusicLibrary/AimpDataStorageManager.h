/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
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
