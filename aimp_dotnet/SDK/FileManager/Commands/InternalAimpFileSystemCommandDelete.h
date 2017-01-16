#pragma once

using namespace AIMP::SDK::FileManager::Commands;

class InternalAimpFileSystemCommandDelete : IUnknownInterfaceImpl<IAIMPFileSystemCommandDelete>
{
private:
    typedef IUnknownInterfaceImpl<IAIMPFileSystemCommandDelete> Base;
    gcroot<IAimpFileSystemCommandDelete^> _instance;

public:
    InternalAimpFileSystemCommandDelete(gcroot<IAimpFileSystemCommandDelete^> instance)
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
        if (riid == IID_IAIMPFileSystemCommandDelete)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }
};
