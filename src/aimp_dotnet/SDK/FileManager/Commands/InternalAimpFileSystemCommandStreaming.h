#pragma once

class InternalAimpFileSystemCommandStreaming : IUnknownInterfaceImpl<IAIMPFileSystemCommandStreaming>
{
private:
    typedef IUnknownInterfaceImpl<IAIMPFileSystemCommandStreaming> Base;
    gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCommandStreaming^> _instance;
public:
    InternalAimpFileSystemCommandStreaming(gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCommandStreaming^> instance);

    virtual HRESULT WINAPI CreateStream(IAIMPString* FileName, const INT64 Offset, const INT64 Size, DWORD Flags, IAIMPStream** Stream);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
