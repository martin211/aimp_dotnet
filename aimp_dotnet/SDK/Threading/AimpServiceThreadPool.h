#pragma once
#include "..\BaseManager.h"
#include "AimpTask.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::Threading;

        public ref class AimpServiceThreadPool : public AimpBaseManager<IAIMPServiceThreadPool>, public IAimpServiceThreadPool
        {
        public:
            explicit AimpServiceThreadPool(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceThreadPool>(core)
            {}

            virtual AimpActionResult Cancel(UIntPtr taskHandle, AimpServiceThreadPoolType flags)
            {
                IAIMPServiceThreadPool *service = NULL;

                try
                {
                    if (GetService(IID_IAIMPServiceThreadPool, &service) == AimpActionResult::Ok)
                    {
                        if (service != NULL)
                            return CheckResult(service->Cancel((DWORD_PTR)taskHandle.ToPointer(), (DWORD)flags));
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
            }

            virtual AimpActionResult Execute(IAimpTask ^task, UIntPtr %handle)
            {
                IAIMPServiceThreadPool *service = NULL;

                try
                {
                    DWORD_PTR h;

                    if (GetService(IID_IAIMPServiceThreadPool, &service) == AimpActionResult::Ok)
                    {
                        if (service != NULL)
                        {
                            InternalAimpTask *internalTask = new InternalAimpTask(task);
                            AimpActionResult result = CheckResult(service->Execute(internalTask, &h));
                            System::Diagnostics::Debug::WriteLine(result.ToString());

                            handle = UIntPtr((void*)h);
                            return result;
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
            }

            virtual AimpActionResult WaitFor(UIntPtr handle)
            {
                IAIMPServiceThreadPool *service = NULL;

                try
                {
                    if (GetService(IID_IAIMPServiceThreadPool, &service) == AimpActionResult::Ok)
                    {
                        if (service != NULL)
                        {
                            return CheckResult(service->WaitFor((DWORD_PTR)handle.ToPointer()));
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
            }
        };
    }
}
