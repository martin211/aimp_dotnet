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
#include "InternalAimpFileSystemCustomFileCommand.h"

using namespace AIMP::SDK::FileManager::Commands;

class InternalAimpFileSystemCommandOpenFileFolder : public IUnknownInterfaceImpl<IAIMPFileSystemCommandOpenFileFolder>
{
private:
    typedef IUnknownInterfaceImpl<IAIMPFileSystemCommandOpenFileFolder> Base;
    gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCommandOpenFileFolder^> _instance;

public:
    InternalAimpFileSystemCommandOpenFileFolder(gcroot<IAimpFileSystemCommandOpenFileFolder^> instance);

    virtual HRESULT WINAPI CanProcess(IAIMPString* FileName);

    virtual HRESULT WINAPI Process(IAIMPString* FileName);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
