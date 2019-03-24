// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once

class InternalAimpExtensionFileInfoProvider :
    public IUnknownInterfaceImpl<IAIMPExtensionFileInfoProvider>,
    IAIMPExtensionFileInfoProviderEx
{
private:
    gcroot<AIMP::SDK::FileManager::Extensions::IAimpExtensionFileInfoProvider^> _managedInstance;

public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionFileInfoProvider> Base;

    InternalAimpExtensionFileInfoProvider(
        gcroot<AIMP::SDK::FileManager::Extensions::IAimpExtensionFileInfoProvider^> managedInstance)
    {
        _managedInstance = managedInstance;
    }

    virtual HRESULT WINAPI GetFileInfo(IAIMPString* fileURI, IAIMPFileInfo* info);

    virtual HRESULT WINAPI GetFileInfo(IAIMPStream* stream, IAIMPFileInfo* info);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (!ppvObject)
        {
            return E_POINTER;
        }

        if (riid == IID_IAIMPExtensionFileInfoProvider)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        if (riid == IID_IAIMPExtensionFileInfoProviderEx)
        {
            *ppvObject = static_cast<IAIMPExtensionFileInfoProviderEx*>(this);
            AddRef();
            return S_OK;
        }

        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }
};
