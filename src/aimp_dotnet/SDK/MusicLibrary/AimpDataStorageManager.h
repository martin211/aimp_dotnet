/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
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
