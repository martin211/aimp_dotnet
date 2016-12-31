#pragma once

using namespace AIMP::SDK::FileManager::Commands;

class InternalAimpFileSystemCommandCopyToClipboard : IUnknownInterfaceImpl<IAIMPFileSystemCommandCopyToClipboard>
{
private:
    typedef IUnknownInterfaceImpl<IAIMPFileSystemCommandCopyToClipboard> Base;
    gcroot<IAimpFileSystemCommandCopyToClipboard^> _instance;

public:
    InternalAimpFileSystemCommandCopyToClipboard(gcroot<IAimpFileSystemCommandCopyToClipboard^> instance)
    {
        _instance = instance;
    }

    virtual HRESULT WINAPI CopyToClipboard(IAIMPObjectList* Files)
    {
        return (HRESULT)_instance->CopyToClipboard(AIMP::SDK::AimpExtension::ToStringCollection(Files));
    }

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        *ppvObject = NULL;
        if (riid == IID_IAIMPFileSystemCommandCopyToClipboard)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }
};
