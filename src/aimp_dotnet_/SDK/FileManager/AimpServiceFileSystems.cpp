// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceFileSystems.h"
#include "Commands/AimpFileSystemCommandFileInfo.h"
#include "Commands/AimpFileSystemCommandCopyToClipboard.h"
#include "Commands/AimpFileSystemCommandDelete.h"
#include "Commands/AimpFileSystemCommandDropSource.h"
#include "Commands/AimpFileSystemCommandOpenFileFolder.h"
#include "Commands/AimpFileSystemCommandStreaming.h"

using namespace AIMP::SDK;
using namespace Commands;

AimpServiceFileSystems::AimpServiceFileSystems(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceFileSystems>(core)
{
}

AimpActionResult AimpServiceFileSystems::Get(FileCommandType commandType, String^ fileUri, IAimpFileSystemCommand^% command)
{
    IAIMPServiceFileSystems* service = GetAimpService();
    auto result = AimpActionResult::Fail;
    command = nullptr;

    try
    {
        if (service != nullptr)
        {
            result = GetCommand(commandType, GetCommandId(commandType), service, fileUri, command, false);
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return result;
}

AimpActionResult AimpServiceFileSystems::GetDefault(FileCommandType commandType, IAimpFileSystemCommand^% command)
{
    IAIMPServiceFileSystems* service = GetAimpService();
    auto result = AimpActionResult::Fail;

    try
    {
        if (service != nullptr)
        {
            result = GetCommand(commandType, GetCommandId(commandType), service, nullptr, command, true);
        }

        return result;
    }
    finally
    {
        ReleaseObject(service);
    }
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
        return IID_IAIMPFileSystemCommandOpenFileFolder;
    case FileCommandType::Streaming:
        return IID_IAIMPFileSystemCommandStreaming;
    }

    throw gcnew ArgumentException("Invalid commandType");
}

AimpActionResult AimpServiceFileSystems::GetCommand(FileCommandType commandType, GUID commandId,
                                                    IAIMPServiceFileSystems* service, String^ value,
                                                    IAimpFileSystemCommand^% command, bool isDefault)
{
    IAIMPString* str = isDefault
                           ? nullptr
                           : AimpConverter::ToAimpString(value);
    auto result = AimpActionResult::Fail;

    try
    {
        switch (commandType)
        {
        case FileCommandType::FileInfo:
            {
                IAIMPFileSystemCommandFileInfo* cmd = nullptr;
                result = isDefault
                             ? CheckResult(service->GetDefault(commandId, reinterpret_cast<void**>(&cmd)))
                             : CheckResult(service->Get(str, commandId, reinterpret_cast<void**>(&cmd)));
                if (result == AimpActionResult::OK && cmd != nullptr)
                {
                    command = gcnew AimpFileSystemCommandFileInfo(cmd);
                }
                break;
            }
        case FileCommandType::CopyToClipboard:
            {
                IAIMPFileSystemCommandCopyToClipboard* cmd = nullptr;
                result = isDefault
                             ? CheckResult(service->GetDefault(commandId, reinterpret_cast<void**>(&cmd)))
                             : CheckResult(service->Get(str, commandId, reinterpret_cast<void**>(&cmd)));
                if (result == AimpActionResult::OK && cmd != nullptr)
                {
                    command = gcnew AimpFileSystemCommandCopyToClipboard(cmd);
                }
                break;
            }
        case FileCommandType::Delete:
            {
                IAIMPFileSystemCommandDelete* cmd = nullptr;
                result = isDefault
                             ? CheckResult(service->GetDefault(commandId, reinterpret_cast<void**>(&cmd)))
                             : CheckResult(service->Get(str, commandId, reinterpret_cast<void**>(&cmd)));
                if (result == AimpActionResult::OK && cmd != nullptr)
                {
                    command = gcnew AimpFileSystemCommandDelete(cmd);
                }
                break;
            }
        case FileCommandType::DropSource:
            {
                IAIMPFileSystemCommandDropSource* cmd = nullptr;
                result = isDefault
                             ? CheckResult(service->GetDefault(commandId, reinterpret_cast<void**>(&cmd)))
                             : CheckResult(service->Get(str, commandId, reinterpret_cast<void**>(&cmd)));
                if (result == AimpActionResult::OK && cmd != nullptr)
                {
                    command = gcnew AimpFileSystemCommandDropSource(cmd);
                }
                break;
            }
        case FileCommandType::OpenFileFolder:
            {
                IAIMPFileSystemCommandOpenFileFolder* cmd = nullptr;
                result = isDefault
                             ? CheckResult(service->GetDefault(commandId, reinterpret_cast<void**>(&cmd)))
                             : CheckResult(service->Get(str, commandId, reinterpret_cast<void**>(&cmd)));
                if (result == AimpActionResult::OK && cmd != nullptr)
                {
                    command = gcnew AimpFileSystemCommandOpenFileFolder(cmd);
                }
                break;
            }
        case FileCommandType::Streaming:
            {
                IAIMPFileSystemCommandStreaming* cmd = nullptr;
                result = isDefault
                             ? CheckResult(service->GetDefault(commandId, reinterpret_cast<void**>(&cmd)))
                             : CheckResult(service->Get(str, commandId, reinterpret_cast<void**>(&cmd)));
                if (result == AimpActionResult::OK && cmd != nullptr)
                {
                    command = gcnew AimpFileSystemCommandStreaming(cmd);
                }
                break;
            }
        }
    }
    finally
    {
        ReleaseObject(str);
    }

    return result;
}

IAIMPServiceFileSystems* AimpServiceFileSystems::GetAimpService()
{
    IAIMPServiceFileSystems* service = nullptr;
    GetService(IID_IAIMPServiceFileSystems, &service);
    return service;
}
