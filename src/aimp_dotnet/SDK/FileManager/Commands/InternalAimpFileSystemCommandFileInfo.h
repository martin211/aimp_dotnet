/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
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
