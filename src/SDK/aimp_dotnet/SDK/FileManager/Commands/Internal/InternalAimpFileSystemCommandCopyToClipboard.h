//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

using namespace AIMP::SDK::FileManager::Commands;

class InternalAimpFileSystemCommandCopyToClipboard : IUnknownInterfaceImpl<IAIMPFileSystemCommandCopyToClipboard> {
private:
    typedef IUnknownInterfaceImpl<IAIMPFileSystemCommandCopyToClipboard> Base;
    gcroot<IAimpFileSystemCommandCopyToClipboard^> _instance;

public:
    InternalAimpFileSystemCommandCopyToClipboard(gcroot<IAimpFileSystemCommandCopyToClipboard^> instance);

    virtual HRESULT WINAPI CopyToClipboard(IAIMPObjectList* Files);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
