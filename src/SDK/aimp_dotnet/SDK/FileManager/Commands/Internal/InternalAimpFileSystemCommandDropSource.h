//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

using namespace AIMP::SDK::FileManager::Commands;

class InternalAimpFileSystemCommandDropSource : IUnknownInterfaceImpl<IAIMPFileSystemCommandDropSource> {
private:
    typedef IUnknownInterfaceImpl<IAIMPFileSystemCommandDropSource> Base;
    gcroot<IAimpFileSystemCommandDropSource^> _instance;

public:
    InternalAimpFileSystemCommandDropSource(gcroot<IAimpFileSystemCommandDropSource^> instance);

    virtual HRESULT WINAPI CreateStream(IAIMPString* fileName, IAIMPStream** stream);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
