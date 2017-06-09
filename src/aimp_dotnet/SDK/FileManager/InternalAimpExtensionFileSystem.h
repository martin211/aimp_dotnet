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

    InternalAimpFileSystemCommandFileInfo *_commandFileInfo = NULL;
    InternalAimpFileSystemCommandOpenFileFolder *_commandOpenFileFolder = NULL;
    InternalAimpFileSystemCommandCopyToClipboard *_commandCopyToClipboard = NULL;
    InternalAimpFileSystemCommandDelete *_commandDelete = NULL;
    InternalAimpFileSystemCommandDropSource *_commandDropSource = NULL;
    InternalAimpFileSystemCommandStreaming *_commandStreaming = NULL;

public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionFileSystem> Base;

    InternalAimpExtensionFileSystem(gcroot<AIMP::SDK::FileManager::Extensions::IAimpExtensionFileSystem^> managed, IAIMPCore *core);

    virtual void WINAPI BeginUpdate();

    virtual void WINAPI EndUpdate();

    virtual HRESULT WINAPI Reset();

    // Read
    virtual HRESULT WINAPI GetValueAsFloat(int PropertyID, double *Value);

    virtual HRESULT WINAPI GetValueAsInt32(int PropertyID, int *Value);

    virtual HRESULT WINAPI GetValueAsInt64(int PropertyID, INT64 *Value);

    virtual HRESULT WINAPI GetValueAsObject(int PropertyID, REFIID IID, void **Value);

    // Write
    virtual HRESULT WINAPI SetValueAsFloat(int PropertyID, const double Value);

    virtual HRESULT WINAPI SetValueAsInt32(int PropertyID, int Value);

    virtual HRESULT WINAPI SetValueAsInt64(int PropertyID, const INT64 Value);

    virtual HRESULT WINAPI SetValueAsObject(int PropertyID, IUnknown *Value);

    virtual HRESULT WINAPI GetFileAttrs(IAIMPString* FileName, TAIMPFileAttributes* Attrs);

    virtual HRESULT WINAPI GetFileSize(IAIMPString* FileName, INT64* Size);

    virtual HRESULT WINAPI IsFileExists(IAIMPString* FileName);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
