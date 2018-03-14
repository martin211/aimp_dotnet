#pragma once
#include "IUnknownInterfaceImpl.h"
#include "AimpSDK.h"

class TMyMusicFileSystem :
    IUnknownInterfaceImpl<IAIMPExtensionFileSystem>,
    IAIMPFileSystemCommandStreaming,
    IAIMPFileSystemCommandFileInfo
{
public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionFileSystem> Base;

    virtual HRESULT WINAPI CreateStream(IAIMPString* FileName, const INT64 Offset, const INT64 Size, DWORD Flags, IAIMPStream** Stream)
    {
        return S_OK;
    }

    virtual HRESULT WINAPI GetFileAttrs(IAIMPString* FileName, TAIMPFileAttributes* Attrs)
    {
        return S_OK;
    }

    virtual HRESULT WINAPI GetFileSize(IAIMPString* FileName, INT64* Size)
    {
        *Size = 0;
        return S_OK;
    }

    virtual HRESULT WINAPI IsFileExists(IAIMPString* FileName)
    {
        return S_OK;
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        HRESULT res = Base::QueryInterface(riid, ppvObject);

        if (!ppvObject)
        {
            return E_POINTER;
        }

        if (riid == IID_IAIMPExtensionFileSystem)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        if (riid == IID_IAIMPFileSystemCommandStreaming)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        if (riid == IID_IAIMPFileSystemCommandFileInfo)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        return res;
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
