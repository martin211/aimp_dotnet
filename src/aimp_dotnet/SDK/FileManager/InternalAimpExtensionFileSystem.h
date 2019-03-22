// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once
#include "Commands/Internal/InternalAimpFileSystemCommandFileInfo.h"
#include "Commands/Internal/InternalAimpFileSystemCommandOpenFileFolder.h"
#include "Commands/Internal/InternalAimpFileSystemCommandCopyToClipboard.h"
#include "Commands/Internal/InternalAimpFileSystemCommandDelete.h"
#include "Commands/Internal/InternalAimpFileSystemCommandDropSource.h"
#include "Commands/Internal/InternalAimpFileSystemCommandStreaming.h"

using namespace AIMP::SDK::FileManager::Commands;

class InternalAimpExtensionFileSystem : public IUnknownInterfaceImpl<IAIMPExtensionFileSystem>
{
private:
    gcroot<AIMP::SDK::FileManager::Extensions::IAimpExtensionFileSystem^> _managed;
    IAIMPCore* _core = nullptr;

    InternalAimpFileSystemCommandFileInfo* _commandFileInfo = nullptr;
    InternalAimpFileSystemCommandOpenFileFolder* _commandOpenFileFolder = nullptr;
    InternalAimpFileSystemCommandCopyToClipboard* _commandCopyToClipboard = nullptr;
    InternalAimpFileSystemCommandDelete* _commandDelete = nullptr;
    InternalAimpFileSystemCommandDropSource* _commandDropSource = nullptr;
    InternalAimpFileSystemCommandStreaming* _commandStreaming = nullptr;

public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionFileSystem> Base;

    InternalAimpExtensionFileSystem(gcroot<AIMP::SDK::FileManager::Extensions::IAimpExtensionFileSystem^> managed,
                                    IAIMPCore* core);

    virtual HRESULT WINAPI GetValueAsInt32(int propertyId, int* value);

    virtual HRESULT WINAPI GetValueAsObject(int propertyId, REFIID IID, void** value);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
