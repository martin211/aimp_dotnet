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
#include "AimpServiceFileSystems.h"

using namespace AIMP::SDK;
using namespace AIMP::SDK::FileManager::Commands;

AimpServiceFileSystems::AimpServiceFileSystems(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceFileSystems>(core)
{
}

generic<typename TCommand>
where TCommand : gcnew()
AimpActionResult AimpServiceFileSystems::Get(String ^fileUri, TCommand %command)
{
    IAIMPServiceFileSystems *service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    IAIMPString *str = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceFileSystems, &service) == AimpActionResult::Ok)
        {
            if (service != nullptr)
            {
                //str = AimpConverter::GetAimpString(fileUri);

                //if (IAimpFileSystemCommandFileInfo::GetType() == TCommand)
                //{
                    //IAIMPFileSystemCommandFileInfo *cmd;
                    //result = CheckResult(service->Get(str, IID_IAIMPFileSystemCommandFileInfo, (void**)&cmd));

                    if (result == AimpActionResult::Ok)
                    {
                        //command = gcnew AimpFileSystemCommandFileInfo(cmd);
                    }
                //}
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

        if (str != NULL)
        {
            str->Release();
            str = NULL;
        }
    }

//    command = nullptr;
    return result;
}

generic<typename TCommand>
where TCommand : gcnew()
AimpActionResult AimpServiceFileSystems::GetDefault(TCommand %command)
{
    IAIMPServiceFileSystems *service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    
    try
    {
        if (GetService(IID_IAIMPServiceFileSystems, &service) == AimpActionResult::Ok)
        {
            if (service != nullptr)
            {
				Type^ cmdType = command->GetType();
				bool v = cmdType->IsGenericType;

                //IAimpFileSystemCommandFileInfo^ fileInfoCommand = dynamic_cast<IAimpFileSystemCommandFileInfo^>(command);
                //if (fileInfoCommand != nullptr)
                //{
                //    IAIMPFileSystemCommandFileInfo* cmd = nullptr;
                //    if (CheckResult(service->GetDefault(IID_IAIMPFileSystemCommandFileInfo, (void**)cmd)) == AimpActionResult::Ok && cmd != nullptr)
                //    {
                //        command = gcnew AimpFileSystemCommandFileInfo(cmd);
                //    }
                //}
            }
        }

        return result;
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    //command = nullptr;
    return result;
}
