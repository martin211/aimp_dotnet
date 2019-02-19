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
#include "Commands\InternalAimpFileSystemCommandFileInfo.h"
#include "Commands\InternalAimpFileSystemCommandOpenFileFolder.h"
#include "Commands\InternalAimpFileSystemCommandCopyToClipboard.h"
#include "Commands\InternalAimpFileSystemCommandDelete.h"
#include "Commands\InternalAimpFileSystemCommandDropSource.h"
#include "Commands\InternalAimpFileSystemCommandStreaming.h"

using namespace AIMP::SDK::FileManager::Commands;

class InternalAimpExtensionFileSystem : public IUnknownInterfaceImpl<IAIMPExtensionFileSystem>
{
private:
    gcroot<AIMP::SDK::FileManager::Extensions::IAimpExtensionFileSystem^> _managed;
    IAIMPCore *_core;

    InternalAimpFileSystemCommandFileInfo *_commandFileInfo = nullptr;
    InternalAimpFileSystemCommandOpenFileFolder *_commandOpenFileFolder = nullptr;
    InternalAimpFileSystemCommandCopyToClipboard *_commandCopyToClipboard = nullptr;
    InternalAimpFileSystemCommandDelete *_commandDelete = nullptr;
    InternalAimpFileSystemCommandDropSource *_commandDropSource = nullptr;
    InternalAimpFileSystemCommandStreaming *_commandStreaming = nullptr;

public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionFileSystem> Base;

    InternalAimpExtensionFileSystem(gcroot<AIMP::SDK::FileManager::Extensions::IAimpExtensionFileSystem^> managed, IAIMPCore *core);

    virtual HRESULT WINAPI GetValueAsInt32(int PropertyID, int *Value);

    virtual HRESULT WINAPI GetValueAsObject(int PropertyID, REFIID IID, void **Value);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
