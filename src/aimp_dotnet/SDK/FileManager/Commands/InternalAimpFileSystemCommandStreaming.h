/* AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 */
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
