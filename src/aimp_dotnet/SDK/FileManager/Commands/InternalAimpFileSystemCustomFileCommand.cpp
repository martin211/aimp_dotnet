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
#include "InternalAimpFileSystemCustomFileCommand.h"

InternalAimpFileSystemCustomFileCommand::InternalAimpFileSystemCustomFileCommand(gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCustomFileCommand^> instance)
{
    _instance = instance;
}

HRESULT WINAPI InternalAimpFileSystemCustomFileCommand::CanProcess(IAIMPString* FileName)
{
    return (HRESULT)_instance->CanProcess(AIMP::SDK::AimpConverter::ToManagedString(FileName));
}

HRESULT WINAPI InternalAimpFileSystemCustomFileCommand::Process(IAIMPString* FileName)
{
    return (HRESULT)_instance->Process(AIMP::SDK::AimpConverter::ToManagedString(FileName));
}
