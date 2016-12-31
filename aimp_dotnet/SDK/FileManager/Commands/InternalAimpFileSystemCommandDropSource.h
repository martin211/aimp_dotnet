#pragma once

using namespace AIMP::SDK::FileManager::Commands;

class InternalAimpFileSystemCommandDropSource : IUnknownInterfaceImpl<IAIMPFileSystemCommandDropSource>
{
private:
    typedef IUnknownInterfaceImpl<IAIMPFileSystemCommandDropSource> Base;
    gcroot<IAimpFileSystemCommandDropSource^> _instance;

public:
    InternalAimpFileSystemCommandDropSource(gcroot<IAimpFileSystemCommandDropSource^> instance)
    {
        _instance = instance;
    }

    virtual HRESULT WINAPI CreateStream(IAIMPString* FileName, IAIMPStream** Stream)
    {
        AimpStream^ aimpStream;
        AimpActionResult result = _instance->CreateStream(AIMP::SDK::AimpExtension::GetString(FileName), aimpStream);
        if (result == AimpActionResult::Ok)
        {
            *Stream = aimpStream->InternalAimpObject;
        }

        return (HRESULT)result;
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
        if (riid == IID_IAIMPFileSystemCommandDropSource)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }
};
