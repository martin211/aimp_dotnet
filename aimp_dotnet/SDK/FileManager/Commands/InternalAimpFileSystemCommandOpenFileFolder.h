#pragma once
#include "InternalAimpFileSystemCustomFileCommand.h"

using namespace AIMP::SDK::FileManager::Commands;

class InternalAimpFileSystemCommandOpenFileFolder : public IUnknownInterfaceImpl<IAIMPFileSystemCommandOpenFileFolder>
{
private:
    typedef IUnknownInterfaceImpl<IAIMPFileSystemCommandOpenFileFolder> Base;
    gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCommandOpenFileFolder^> _instance;

public:
    InternalAimpFileSystemCommandOpenFileFolder(gcroot<IAimpFileSystemCommandOpenFileFolder^> instance)
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
        if (riid == IID_IAIMPFileSystemCommandOpenFileFolder)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }
};
