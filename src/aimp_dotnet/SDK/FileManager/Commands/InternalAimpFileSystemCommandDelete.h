#pragma once

using namespace AIMP::SDK::FileManager::Commands;

class InternalAimpFileSystemCommandDelete : IUnknownInterfaceImpl<IAIMPFileSystemCommandDelete>
{
private:
    typedef IUnknownInterfaceImpl<IAIMPFileSystemCommandDelete> Base;
    gcroot<IAimpFileSystemCommandDelete^> _instance;

public:
    InternalAimpFileSystemCommandDelete(gcroot<IAimpFileSystemCommandDelete^> instance);

    virtual HRESULT WINAPI CanProcess(IAIMPString* FileName);

    virtual HRESULT WINAPI Process(IAIMPString* FileName);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
