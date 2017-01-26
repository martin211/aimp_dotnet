#include "Stdafx.h"
#include "AimpDataStorageManager.h"

using namespace AIMP::SDK;

AimpDataStorageManager::AimpDataStorageManager(IAIMPMLDataStorageManager *manager) : AimpObject(manager)
{
}

void AimpDataStorageManager::BackgroundTaskStarted(int id, System::String ^cartion, ActionManager::IAimpActionEvent ^cancelEvent)
{
    //todo complete it
    IAIMPString *str = AimpConverter::ToAimpString(cartion);
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

void AimpDataStorageManager::BackgroundTaskFinished(int id)
{
    this->InternalAimpObject->BackgroundTaskFinished(id);
}

void AimpDataStorageManager::Changed()
{
    this->InternalAimpObject->Changed();
}
