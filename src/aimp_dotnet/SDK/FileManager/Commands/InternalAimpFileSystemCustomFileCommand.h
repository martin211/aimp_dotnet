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

#pragma once

class InternalAimpFileSystemCustomFileCommand : IUnknownInterfaceImpl<IAIMPFileSystemCustomFileCommand>
{
private:
    gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCustomFileCommand^> _instance;

public:
    InternalAimpFileSystemCustomFileCommand(gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCustomFileCommand^> instance);

    virtual HRESULT WINAPI CanProcess(IAIMPString* FileName);

    virtual HRESULT WINAPI Process(IAIMPString* FileName);
};
