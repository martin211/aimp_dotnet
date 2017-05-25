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
AimpServiceFileSystems::AimpServiceFileSystems(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceFileSystems>(core)
{
}

generic<typename TCommand>
    AimpActionResult AimpServiceFileSystems::Get(String ^fileUri, IAimpFileSystemCommand ^%command)
    {
        IAIMPServiceFileSystems *service = NULL;
        AimpActionResult result = AimpActionResult::Fail;
        IAIMPString *str = NULL;

        try
        {
            if (GetService(IID_IAIMPServiceFileSystems, &service) == AimpActionResult::Ok)
            {
                if (service != NULL)
                {
                    //str = AimpConverter::GetAimpString(fileUri);

                    //if (IAimpFileSystemCommandFileInfo::GetType() == TCommand)
                    //{
                    //    IAIMPFileSystemCommandFileInfo *cmd;
                    //    result = CheckResult(service->Get(str, IID_IAIMPFileSystemCommandFileInfo, (void**)&cmd));

                    //    if (result == AimpActionResult::Ok)
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

        command = nullptr;
        return AimpActionResult::Fail;
    }

    generic<typename TCommand>
        AimpActionResult AimpServiceFileSystems::GetDefault(IAimpFileSystemCommand ^%command)
        {
            command = nullptr;
            return AimpActionResult::Fail;
        }
