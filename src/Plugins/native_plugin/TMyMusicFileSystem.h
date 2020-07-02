// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

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
    IAIMPCore* _core;

    virtual HRESULT WINAPI GetValueAsObject(int PropertyID, REFIID IID, void** Value)
    {
        if (PropertyID == AIMP_FILESYSTEM_PROPID_SCHEME)
        {
            IAIMPString* s = nullptr;
            _core->CreateObject(IID_IAIMPString, (void**)&s);
            s->SetData(L"mymusic:\\\\", 12);
            *Value = s;
        }

        return E_NOTIMPL;
    }

    virtual HRESULT WINAPI GetValueAsInt32(int PropertyID, int* Value)
    {
        if (PropertyID == AIMP_FILESYSTEM_PROPID_READONLY)
        {
            *Value = 1;
        }

        return E_NOTIMPL;
    }

    virtual HRESULT WINAPI CreateStream(IAIMPString* FileName, const INT64 Offset, const INT64 Size, DWORD Flags,
                                        IAIMPStream** Stream)
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
