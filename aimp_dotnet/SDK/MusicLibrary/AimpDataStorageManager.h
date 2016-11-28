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
                IAIMPString *str = AimpExtension::GetAimpString(cartion);
                try
                {
                    this->InternalAimpObject->BackgroundTaskStarted(id, str, NULL);
                }
                finally
                {
                    if (str != NULL)
                    {
                        str->Release();
                        str = NULL;
                    }
                }
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