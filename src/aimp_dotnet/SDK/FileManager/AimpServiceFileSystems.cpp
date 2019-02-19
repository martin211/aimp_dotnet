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
using namespace Commands;

AimpServiceFileSystems::AimpServiceFileSystems(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceFileSystems>(core)
{
}

generic<typename TCommand>
where TCommand : gcnew()
AimpActionResult AimpServiceFileSystems::Get(String^ fileUri, TCommand% command)
{
    IAIMPServiceFileSystems* service = nullptr;
    const auto result = AimpActionResult::Fail;
    IAIMPString *str = nullptr;

    try
    {
        // TODO Complete it
        if (GetService(IID_IAIMPServiceFileSystems, &service) == AimpActionResult::OK && service != nullptr)
        {
            //str = AimpConverter::GetAimpString(fileUri);

            //if (IAimpFileSystemCommandFileInfo::GetType() == TCommand)
            //{
                //IAIMPFileSystemCommandFileInfo *cmd;
                //result = CheckResult(service->Get(str, IID_IAIMPFileSystemCommandFileInfo, (void**)&cmd));

                if (result == AimpActionResult::OK)
                {
                    //command = gcnew AimpFileSystemCommandFileInfo(cmd);
                }
            //}
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

        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

//    command = nullptr;
    return result;
}

generic<typename TCommand>
where TCommand : gcnew()
AimpActionResult AimpServiceFileSystems::GetDefault(TCommand %command)
{
    IAIMPServiceFileSystems* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    
    try
    {
        if (GetService(IID_IAIMPServiceFileSystems, &service) == AimpActionResult::OK)
        {
            if (service != nullptr)
            {
				Type^ cmdType = command->GetType();
				bool v = cmdType->IsGenericType;

                //IAimpFileSystemCommandFileInfo^ fileInfoCommand = dynamic_cast<IAimpFileSystemCommandFileInfo^>(command);
                //if (fileInfoCommand != nullptr)
                //{
                //    IAIMPFileSystemCommandFileInfo* cmd = nullptr;
                //    if (CheckResult(service->GetDefault(IID_IAIMPFileSystemCommandFileInfo, (void**)cmd)) == AimpActionResult::OK && cmd != nullptr)
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
