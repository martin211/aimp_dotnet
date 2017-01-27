#pragma once

using namespace AIMP::SDK::FileManager::Commands;

class InternalAimpFileSystemCommandDropSource : IUnknownInterfaceImpl<IAIMPFileSystemCommandDropSource>
{
private:
    typedef IUnknownInterfaceImpl<IAIMPFileSystemCommandDropSource> Base;
    gcroot<IAimpFileSystemCommandDropSource^> _instance;

public:
    InternalAimpFileSystemCommandDropSource(gcroot<IAimpFileSystemCommandDropSource^> instance);

    virtual HRESULT WINAPI CreateStream(IAIMPString* FileName, IAIMPStream** Stream);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
