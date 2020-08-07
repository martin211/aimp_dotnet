// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

class InternalAimpExtensionFileInfoProvider :
    public IUnknownInterfaceImpl<IAIMPExtensionFileInfoProvider>,
    IAIMPExtensionFileInfoProviderEx {
private:
    gcroot<AIMP::SDK::FileManager::Extensions::IAimpExtensionFileInfoProvider^> _managedInstance;

public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionFileInfoProvider> Base;

    InternalAimpExtensionFileInfoProvider(
        gcroot<AIMP::SDK::FileManager::Extensions::IAimpExtensionFileInfoProvider^> managedInstance) {
        _managedInstance = managedInstance;
    }

    virtual HRESULT WINAPI GetFileInfo(IAIMPString* fileURI, IAIMPFileInfo* info);

    virtual HRESULT WINAPI GetFileInfo(IAIMPStream* stream, IAIMPFileInfo* info);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
