/* AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 */
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
