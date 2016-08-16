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
            explicit AimpDataStorageManager(IAIMPMLDataStorageManager *manager) : AimpObject(manager)
            {}

            virtual void BackgroundTaskStarted(int id, System::String ^cartion, AIMP::SDK::ActionManager::IAimpActionEvent ^cancelEvent)
            {
                //todo complete it
                this->InternalAimpObject->BackgroundTaskStarted(id, AimpExtension::GetAimpString(cartion), NULL);
            }

            virtual void BackgroundTaskFinished(int id)
            {
                this->InternalAimpObject->BackgroundTaskFinished(id);
            }

            virtual void Changed()
            {
                this->InternalAimpObject->Changed();
            }
        };
    }
}