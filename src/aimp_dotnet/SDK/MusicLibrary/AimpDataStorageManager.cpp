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

#include "Stdafx.h"
#include "AimpDataStorageManager.h"

using namespace AIMP::SDK;

AimpDataStorageManager::AimpDataStorageManager(IAIMPMLDataStorageManager *manager) : AimpObject(manager)
{
}

AimpActionResult AimpDataStorageManager::BackgroundTaskStarted(int id, System::String ^cartion, ActionManager::IAimpActionEvent ^cancelEvent)
{
    //todo complete it
    IAIMPString *str = AimpConverter::ToAimpString(cartion);
    try
    {
        return Utils::CheckResult(this->InternalAimpObject->BackgroundTaskStarted(id, str, NULL));
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

AimpActionResult AimpDataStorageManager::BackgroundTaskFinished(int id)
{
    return Utils::CheckResult(this->InternalAimpObject->BackgroundTaskFinished(id));
}

void AimpDataStorageManager::Changed()
{
    this->InternalAimpObject->Changed();
}
