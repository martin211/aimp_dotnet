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

class InternalAimpFileSystemCommandStreaming : IUnknownInterfaceImpl<IAIMPFileSystemCommandStreaming>
{
private:
    typedef IUnknownInterfaceImpl<IAIMPFileSystemCommandStreaming> Base;
    gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCommandStreaming^> _instance;

public:
    InternalAimpFileSystemCommandStreaming(gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCommandStreaming^> instance);

    virtual HRESULT WINAPI CreateStream(IAIMPString* fileName, const INT64 offset, const INT64 size, DWORD flags, IAIMPStream** stream);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
