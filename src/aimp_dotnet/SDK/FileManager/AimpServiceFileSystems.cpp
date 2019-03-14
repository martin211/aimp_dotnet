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
#include "Commands/AimpFileSystemCommandFileInfo.h"

using namespace AIMP::SDK;
using namespace Commands;

AimpServiceFileSystems::AimpServiceFileSystems(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceFileSystems>(core)
{
}

generic<typename TCommand>
where TCommand : gcnew()
AimpActionResult AimpServiceFileSystems::Get(FileCommandType commandType, String^ fileUri, TCommand% command)
{
    IAIMPServiceFileSystems* service = nullptr;
    auto result = AimpActionResult::Fail;
    IAIMPString *str = nullptr;
    GUID commandId;

    try
    {
        // TODO Complete it
        if (GetService(IID_IAIMPServiceFileSystems, &service) == AimpActionResult::OK && service != nullptr)
        {
            switch (commandType)
            {
            case FileCommandType::FileInfo:
                commandId = IID_IAIMPFileSystemCommandFileInfo;
                break;
            case FileCommandType::CopyToClipboard:
                commandId = IID_IAIMPFileSystemCommandCopyToClipboard;
                break;
            case FileCommandType::Delete:
                commandId = IID_IAIMPFileSystemCommandDelete;
                break;
            case FileCommandType::DropSource:
                commandId = IID_IAIMPFileSystemCommandDropSource;
                break;
            case FileCommandType::FileExists:
                commandId = IID_IAIMPFileSystemCommandFileExists;
                break;
            case FileCommandType::OpenFileFolder:
                commandId = IID_IAIMPFileSystemCommandFileInfo;
                break;
            case FileCommandType::Streaming:
                commandId = IID_IAIMPFileSystemCommandStreaming;
                break;
            }

            str = AimpConverter::ToAimpString(fileUri);
            IAIMPFileSystemCommandFileInfo* cmd = nullptr;
            result = CheckResult(service->Get(str, IID_IAIMPFileSystemCommandFileInfo, reinterpret_cast<void**>(&cmd)));

            if (result == AimpActionResult::OK && cmd != nullptr)
            {
                switch (commandType)
                {
                    case FileCommandType::FileInfo:
                    command = (TCommand)gcnew AimpFileSystemCommandFileInfo(cmd);
                    break;
                }
            }
        }
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

    return result;
}

generic<typename TCommand>
where TCommand : gcnew()
AimpActionResult AimpServiceFileSystems::GetDefault(FileCommandType commandType, TCommand %command)
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
