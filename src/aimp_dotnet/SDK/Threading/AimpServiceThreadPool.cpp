/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#include "Stdafx.h"
#include "AimpServiceThreadPool.h"

using namespace AIMP::SDK;

AimpServiceThreadPool::AimpServiceThreadPool(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceThreadPool>(core)
{

}

AimpActionResult AimpServiceThreadPool::Cancel(UIntPtr taskHandle, AimpServiceThreadPoolType flags)
{
    IAIMPServiceThreadPool *service = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceThreadPool, &service) == AimpActionResult::Ok && service != NULL)
        {
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

AimpActionResult AimpServiceThreadPool::Execute(IAimpTask ^task, UIntPtr %handle)
{
    IAIMPServiceThreadPool *service = NULL;

    try
    {
        DWORD_PTR h;

        if (GetService(IID_IAIMPServiceThreadPool, &service) == AimpActionResult::Ok && service != NULL)
        {
            InternalAimpTask *internalTask = new InternalAimpTask(task);
            AimpActionResult result = CheckResult(service->Execute(internalTask, &h));
            System::Diagnostics::Debug::WriteLine(result.ToString());

            handle = UIntPtr((void*)h);
            return result;
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

AimpActionResult AimpServiceThreadPool::WaitFor(UIntPtr handle)
{
    IAIMPServiceThreadPool *service = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceThreadPool, &service) == AimpActionResult::Ok && service != NULL)
        {
            return CheckResult(service->WaitFor((DWORD_PTR)handle.ToPointer()));
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
