// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
using namespace AIMP::SDK::FileManager::Commands;

class InternalAimpFileSystemCommandFileInfo : IUnknownInterfaceImpl<IAIMPFileSystemCommandFileInfo> {
private:
    typedef IUnknownInterfaceImpl<IAIMPFileSystemCommandFileInfo> Base;
    gcroot<IAimpFileSystemCommandFileInfo^> _instance;
    IAIMPCore* _core;

public:
    InternalAimpFileSystemCommandFileInfo(gcroot<IAimpFileSystemCommandFileInfo^> instance, IAIMPCore* core);

    virtual HRESULT WINAPI GetFileAttrs(IAIMPString* fileName, TAIMPFileAttributes* attrs);

    virtual HRESULT WINAPI GetFileSize(IAIMPString* fileName, INT64* size);

    virtual HRESULT WINAPI IsFileExists(IAIMPString* fileName);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
