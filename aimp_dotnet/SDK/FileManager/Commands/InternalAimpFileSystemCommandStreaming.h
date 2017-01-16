#pragma once

class InternalAimpFileSystemCommandStreaming : IUnknownInterfaceImpl<IAIMPFileSystemCommandStreaming>
{
private:
    typedef IUnknownInterfaceImpl<IAIMPFileSystemCommandStreaming> Base;
    gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCommandStreaming^> _instance;
public:
    InternalAimpFileSystemCommandStreaming(gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCommandStreaming^> instance)
    {
        _instance = instance;
    }

    virtual HRESULT WINAPI CreateStream(IAIMPString* FileName, const INT64 Offset, const INT64 Size, DWORD Flags, IAIMPStream** Stream)
    {
        AimpStream^ stream = nullptr;
        //return (HRESULT)_instance->CreateStream(AIMP::SDK::AimpExtension::GetString(FileName), Offset, Size, Flags, &stream);
        return S_OK;
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
        if (riid == IID_IAIMPFileSystemCommandStreaming)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }
};
