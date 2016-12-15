#pragma once

class InternalAimpExtensionFileInfoProvider : 
    public IUnknownInterfaceImpl<IAIMPExtensionFileInfoProvider>,
    IAIMPExtensionFileInfoProviderEx
{
private:
    gcroot<AIMP::SDK::FileManager::Extensions::IAimpExtensionFileInfoProvider^> _managedInstance;

public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionFileInfoProvider> Base;

    InternalAimpExtensionFileInfoProvider(gcroot<AIMP::SDK::FileManager::Extensions::IAimpExtensionFileInfoProvider^> managedInstance)
    {
        _managedInstance = managedInstance;
    }

    virtual HRESULT WINAPI GetFileInfo(IAIMPString *FileURI, IAIMPFileInfo *Info);

    virtual HRESULT WINAPI GetFileInfo(IAIMPStream *Stream, IAIMPFileInfo *Info);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (!ppvObject)
        {
            return E_POINTER;
        }
        if (riid == IID_IAIMPExtensionFileInfoProvider) {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        if (riid == IID_IAIMPExtensionFileInfoProviderEx) {
            *ppvObject = static_cast<IAIMPExtensionFileInfoProviderEx*>(this);
            AddRef();
            return S_OK;
        }

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
