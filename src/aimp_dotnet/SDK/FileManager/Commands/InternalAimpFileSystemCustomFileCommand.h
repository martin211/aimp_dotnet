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
