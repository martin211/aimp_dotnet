#pragma once
#include "AimpTask.h"
#include "..\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::Threading;

        public ref class AimpServiceSynchronizer : public AimpBaseManager<IAIMPServiceSynchronizer>, public IAimpServiceSynchronizer
        {
        public:
            explicit AimpServiceSynchronizer(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceSynchronizer>(core)
            {

            }

            virtual AimpActionResult ExecuteInMainThread(IAimpTask^ task, bool executeNow)
            {
                IAIMPServiceSynchronizer *service = NULL;

                try
                {
                    if (GetService(IID_IAIMPServiceSynchronizer, &service) == AimpActionResult::Ok)
                    {
                        if (service != NULL)
                        {
                            InternalAimpTask *internalTask = new InternalAimpTask(task);
                            return CheckResult(service->ExecuteInMainThread(internalTask, (BOOL)executeNow));
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

                return AIMP::SDK::AimpActionResult::Fail;
            }
        };
    }
}