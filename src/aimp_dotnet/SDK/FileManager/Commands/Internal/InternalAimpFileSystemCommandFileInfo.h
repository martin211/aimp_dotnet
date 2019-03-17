// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once
using namespace AIMP::SDK::FileManager::Commands;

class InternalAimpFileSystemCommandFileInfo : IUnknownInterfaceImpl<IAIMPFileSystemCommandFileInfo>
{
private:
    typedef IUnknownInterfaceImpl<IAIMPFileSystemCommandFileInfo> Base;
    gcroot<IAimpFileSystemCommandFileInfo^> _instance;
    IAIMPCore* _core;

public:
    InternalAimpFileSystemCommandFileInfo(gcroot<IAimpFileSystemCommandFileInfo^> instance, IAIMPCore* core);

    virtual HRESULT WINAPI GetFileAttrs(IAIMPString* FileName, TAIMPFileAttributes* Attrs);

    virtual HRESULT WINAPI GetFileSize(IAIMPString* FileName, INT64* Size);

    virtual HRESULT WINAPI IsFileExists(IAIMPString* FileName);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
