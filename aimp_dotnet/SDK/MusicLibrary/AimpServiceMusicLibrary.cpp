#include "..\..\Stdafx.h"
#include "AimpServiceMusicLibrary.h"

namespace AIMP
{
    namespace SDK
    {
        AimpActionResult AimpServiceMusicLibrary::GetActiveDataStorage(IAimpDataStorage ^%storage)
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

        AimpActionResult AimpServiceMusicLibrary::GetActiveDataStorage(IAimpGroupingPresets ^%preset)
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
                    IAIMPMLGroupingPresets *storage;
                    result = CheckResult(service->GetStorage(index, IID_IAIMPMLGroupingPresets, (void**)&storage));
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

            try
            {
                if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::Ok)
                {
                    IAIMPMLDataStorage *storage;
                    //result = CheckResult(service->GetStorageByID(index, IID_IAIMPMLDataStorage, (void**)&storage));
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

        AimpActionResult AimpServiceMusicLibrary::GetStorageById(String ^id, IAimpGroupingPresets ^%storage)
        {
            IAIMPServiceMusicLibrary *service = NULL;
            AimpActionResult result = AimpActionResult::Fail;

            try
            {
                if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::Ok)
                {
                    IAIMPMLGroupingPresets *storage;
                    //result = CheckResult(service->GetStorageByID(index, IID_IAIMPMLGroupingPresets, (void**)&storage));
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

        int AimpServiceMusicLibrary::GetStorageCount()
        {
            IAIMPServiceMusicLibrary *service = NULL;

            try
            {
                if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::Ok)
                {
                    IAIMPMLGroupingPresets *storage;
                    return service->GetStorageCount();
                }

                return 0;
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
    }
}
