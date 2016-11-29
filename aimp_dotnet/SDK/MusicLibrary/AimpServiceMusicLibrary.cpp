#include "Stdafx.h"
#include "AimpServiceMusicLibrary.h"
#include "AimpDataStorage.h"
#include "AimpGroupingPresets.h"

namespace AIMP
{
    namespace SDK
    {
        AimpActionResult AimpServiceMusicLibrary::GetActiveStorage(IAimpDataStorage ^%storage)
        {
            IAIMPServiceMusicLibrary *service = NULL;
            AimpActionResult result = AimpActionResult::Fail;
            storage = nullptr;

            try
            {
                if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::Ok)
                {
                    if (service != NULL)
                    {
                        IAIMPMLDataStorage *aimpStorage;
                        result = CheckResult(service->GetActiveStorage(IID_IAIMPMLDataStorage, (void**)&aimpStorage));
                        if (result == AimpActionResult::Ok)
                        {
                            storage = gcnew AimpDataStorage(aimpStorage);
                        }
                    }
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

        AimpActionResult AimpServiceMusicLibrary::GetActiveStorage(IAimpGroupingPresets ^%presets)
        {
            IAIMPServiceMusicLibrary *service = NULL;
            AimpActionResult result = AimpActionResult::Fail;

            try
            {
                if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::Ok)
                {
                    if (service != NULL)
                    {
                        IAIMPMLGroupingPresets *aimpPresets;
                        result = CheckResult(service->GetActiveStorage(IID_IAIMPMLGroupingPresets, (void**)&aimpPresets));
                        presets = gcnew AimpGroupingPresets(aimpPresets);
                    }
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

        AimpActionResult AimpServiceMusicLibrary::SetActiveStorage(IAimpDataStorage ^storage)
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

        AimpActionResult AimpServiceMusicLibrary::SetActiveStorage(IAimpGroupingPresets ^preset)
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

        AimpActionResult AimpServiceMusicLibrary::GetStorage(int index, IAimpDataStorage ^%storage)
        {
            IAIMPServiceMusicLibrary *service = NULL;
            AimpActionResult result = AimpActionResult::Fail;

            try
            {
                if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::Ok)
                {
                    if (service == NULL)
                    {
                        return AimpActionResult::Fail;
                    }

                    IAIMPMLDataStorage *storage;
                    result = CheckResult(service->GetStorage(index, IID_IAIMPMLDataStorage, (void**)&storage));
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

        AimpActionResult AimpServiceMusicLibrary::GetStorage(int index, IAimpGroupingPresets ^%storage)
        {
            IAIMPServiceMusicLibrary *service = NULL;
            AimpActionResult result = AimpActionResult::Fail;

            try
            {
                if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::Ok)
                {
                    if (service == NULL)
                        return AimpActionResult::Fail;

                    IAIMPMLGroupingPresets* s;
                    result = CheckResult(service->GetStorage(index, IID_IAIMPMLGroupingPresets, (void**)&s));

                    if (s != NULL)
                    {
                        storage = gcnew AimpGroupingPresets(s);
                    }
                    else
                    {
                        return AimpActionResult::Handle;
                    }
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

        AimpActionResult AimpServiceMusicLibrary::GetStorageById(String ^id, IAimpDataStorage ^%storage)
        {
            IAIMPServiceMusicLibrary *service = NULL;
            AimpActionResult result = AimpActionResult::Fail;
            IAIMPString *aimpId;

            try
            {
                if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::Ok)
                {
                    IAIMPMLDataStorage *aimpStorage;
                    aimpId = AimpExtension::GetAimpString(id);
                    result = CheckResult(service->GetStorageByID(aimpId, IID_IAIMPMLDataStorage, (void**)&aimpStorage));
                    storage = gcnew AimpDataStorage(aimpStorage);
                }

                return result;
            }
            finally
            {
                if (service != NULL)
                {
                    service->Release();
                    aimpId->Release();
                }
            }
        }

        AimpActionResult AimpServiceMusicLibrary::GetStorageById(String ^id, IAimpGroupingPresets ^%storage)
        {
            IAIMPServiceMusicLibrary *service = NULL;
            AimpActionResult result = AimpActionResult::Fail;
            IAIMPString *aimpId;

            try
            {
                if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::Ok)
                {
                    IAIMPMLGroupingPresets *aimpStorage;
                    aimpId = AimpExtension::GetAimpString(id);
                    result = CheckResult(service->GetStorageByID(aimpId, IID_IAIMPMLGroupingPresets, (void**)&aimpStorage));
                    storage = gcnew AimpGroupingPresets(aimpStorage);
                }

                return result;
            }
            finally
            {
                if (service != NULL)
                {
                    service->Release();
                    aimpId->Release();
                }
            }
        }

        int AimpServiceMusicLibrary::GetStorageCount()
        {
            IAIMPServiceMusicLibrary *service = NULL;

            try
            {
                if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::Ok)
                {
                    if (service != NULL)
                    {
                        IAIMPMLGroupingPresets *storage;
                        return service->GetStorageCount();
                    }
                }
            }
            finally
            {
                if (service != NULL)
                {
                    service->Release();
                    service = NULL;
                }
            }

            return 0;
        }
    }
}
