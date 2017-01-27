/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 */
#pragma once

class InternalAimpFileSystemCommandFileInfo : IUnknownInterfaceImpl<IAIMPFileSystemCommandFileInfo>
{
private:
    typedef IUnknownInterfaceImpl<IAIMPFileSystemCommandFileInfo> Base;
    gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCommandFileInfo^> _instance;

public:
    InternalAimpFileSystemCommandFileInfo(gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCommandFileInfo^> instance);

    virtual HRESULT WINAPI GetFileAttrs(IAIMPString* FileName, TAIMPFileAttributes* Attrs);

    virtual HRESULT WINAPI GetFileSize(IAIMPString* FileName, INT64* Size);

    virtual HRESULT WINAPI IsFileExists(IAIMPString* FileName);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
