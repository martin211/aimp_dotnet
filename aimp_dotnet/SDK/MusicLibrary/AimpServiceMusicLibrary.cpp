#include "AimpServiceMusicLibrary.h"

AimpActionResult AimpServiceMusicLibrary::GetActiveDataStorage(IAimpExtensionDataStorage ^%obj)
{
    IAIMPServiceMusicLibrary *service = NULL;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::Ok)
        {
            IAIMPMLDataStorage *storage;
            result = CheckResult(service->GetActiveStorage(IID_IAIMPMLDataStorage, (void**)&storage));
        }

        return result;
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }
    }
}

AimpActionResult AimpServiceMusicLibrary::GeteActiveGroupingPreset(IAimpGroupingPreset ^%preset)
{
    IAIMPServiceMusicLibrary *service = NULL;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::Ok)
        {
            IAIMPMLGroupingPresets *storage;
            result = CheckResult(service->GetActiveStorage(IID_IAIMPMLGroupingPresets, (void**)&storage));
        }

        return result;
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }
    }
}

AimpActionResult AimpServiceMusicLibrary::SetActiveStorage(IAimpExtensionDataStorage ^storage)
{
    IAIMPServiceMusicLibrary *service = NULL;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::Ok)
        {
            IAIMPMLGroupingPresets *storage;
            //result = CheckResult(service->SetActiveStorage(IID_IAIMPMLGroupingPresets));
        }

        return result;
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }
    }
}
