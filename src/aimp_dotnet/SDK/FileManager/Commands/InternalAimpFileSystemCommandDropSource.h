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
