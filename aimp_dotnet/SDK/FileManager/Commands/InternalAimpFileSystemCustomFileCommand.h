#pragma once

class InternalAimpFileSystemCustomFileCommand : IUnknownInterfaceImpl<IAIMPFileSystemCustomFileCommand>
{
private:
    gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCustomFileCommand^> _instance;

public:
    InternalAimpFileSystemCustomFileCommand(gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCustomFileCommand^> instance)
    {
        _instance = instance;
    }

    virtual HRESULT WINAPI CanProcess(IAIMPString* FileName)
    {
        return (HRESULT)_instance->CanProcess(AIMP::SDK::AimpExtension::GetString(FileName));
    }

    virtual HRESULT WINAPI Process(IAIMPString* FileName)
    {
        return (HRESULT)_instance->Process(AIMP::SDK::AimpExtension::GetString(FileName));
    }
};
