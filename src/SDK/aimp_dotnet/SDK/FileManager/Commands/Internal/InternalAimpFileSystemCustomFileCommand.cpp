//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpFileSystemCustomFileCommand.h"

InternalAimpFileSystemCustomFileCommand::InternalAimpFileSystemCustomFileCommand(
    gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCustomFileCommand^> instance) {
    _instance = instance;
}
