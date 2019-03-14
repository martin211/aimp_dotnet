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

AimpActionResult AimpServiceFileSystems::Get(FileCommandType commandType, String^ fileUri, IAimpFileSystemCommand^% command)
{
    IAIMPServiceFileSystems* service = nullptr;
    auto result = AimpActionResult::Fail;
    IAIMPString *str = nullptr;
    GUID commandId = GetCommandId(commandType);

    try
    {
        // TODO Complete it
        if (GetService(IID_IAIMPServiceFileSystems, &service) == AimpActionResult::OK && service != nullptr)
        {
            str = AimpConverter::ToAimpString(fileUri);
            IAIMPFileSystemCommandFileInfo* cmd = nullptr;
            result = CheckResult(service->Get(str, IID_IAIMPFileSystemCommandFileInfo, reinterpret_cast<void**>(&cmd)));

            if (result == AimpActionResult::OK && cmd != nullptr)
            {
                switch (commandType)
                {
                    case FileCommandType::FileInfo:
                    command = gcnew AimpFileSystemCommandFileInfo(cmd);
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

AimpActionResult AimpServiceFileSystems::GetDefault(FileCommandType commandType, IAimpFileSystemCommand^% command)
{
    IAIMPServiceFileSystems* service = nullptr;
    auto result = AimpActionResult::Fail;
    GUID commandId = GetCommandId(commandType);

    try
    {
        if (GetService(IID_IAIMPServiceFileSystems, &service) == AimpActionResult::OK && service != nullptr)
        {
            switch (commandType)
            {
            case FileCommandType::FileInfo:
                IAIMPFileSystemCommandFileInfo* cmd = nullptr;
                result = CheckResult(service->GetDefault(commandId, reinterpret_cast<void**>(&cmd)));
                if (result == AimpActionResult::OK && cmd != nullptr)
                {
                    command = gcnew AimpFileSystemCommandFileInfo(cmd);
                }
                break;
            }

				//Type^ cmdType = command->GetType();
				//bool v = cmdType->IsGenericType;

    //            //IAimpFileSystemCommandFileInfo^ fileInfoCommand = dynamic_cast<IAimpFileSystemCommandFileInfo^>(command);
    //            //if (fileInfoCommand != nullptr)
    //            //{
    //            //    IAIMPFileSystemCommandFileInfo* cmd = nullptr;
    //            //    if (CheckResult(service->GetDefault(IID_IAIMPFileSystemCommandFileInfo, (void**)cmd)) == AimpActionResult::OK && cmd != nullptr)
    //            //    {
    //            //        command = gcnew AimpFileSystemCommandFileInfo(cmd);
    //            //    }
    //            //}
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

GUID AimpServiceFileSystems::GetCommandId(FileCommandType commandType)
{
    switch (commandType)
    {
        case FileCommandType::FileInfo:
            return IID_IAIMPFileSystemCommandFileInfo;
        case FileCommandType::CopyToClipboard:
            return IID_IAIMPFileSystemCommandCopyToClipboard;
        case FileCommandType::Delete:
            return IID_IAIMPFileSystemCommandDelete;
        case FileCommandType::DropSource:
            return IID_IAIMPFileSystemCommandDropSource;
        case FileCommandType::FileExists:
            return IID_IAIMPFileSystemCommandFileExists;
        case FileCommandType::OpenFileFolder:
            return IID_IAIMPFileSystemCommandFileInfo;
        case FileCommandType::Streaming:
            return IID_IAIMPFileSystemCommandStreaming;
    }

    throw gcnew ArgumentException("Invalid commandType");
}
