#include "Stdafx.h"
#include "InternalAimpFileSystemCustomFileCommand.h"

InternalAimpFileSystemCustomFileCommand::InternalAimpFileSystemCustomFileCommand(gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCustomFileCommand^> instance)
{
    _instance = instance;
}

HRESULT WINAPI InternalAimpFileSystemCustomFileCommand::CanProcess(IAIMPString* FileName)
{
    return (HRESULT)_instance->CanProcess(AIMP::SDK::AimpExtension::GetString(FileName));
}

HRESULT WINAPI InternalAimpFileSystemCustomFileCommand::Process(IAIMPString* FileName)
{
    return (HRESULT)_instance->Process(AIMP::SDK::AimpExtension::GetString(FileName));
}
