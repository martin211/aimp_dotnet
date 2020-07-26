// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

#include "Command/AimpDataStorageCommandAddFilesDialog.h"
#include "Command/AimpDataStorageCommandDeleteFiles.h"
#include "Command/AimpDataStorageCommandDropData.h"
#include "Command/AimpDataStorageCommandReloadTags.h"
#include "Command/AimpDataStorageCommandReportDialog.h"
#include "Command/AimpDataStorageCommandUserMark.h"
#include "Command/AimpDataStorageCommandAddFiles.h"
#include "SDK/MusicLibrary/Presets/AimpGroupingPresets.h"

class AimpDataProvider : public IUnknownInterfaceImpl<IAIMPMLDataProvider>
{
private:
    gcroot<MusicLibrary::Extension::IAimpExtensionDataStorage^> _instance;

public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataProvider> Base;

    AimpDataProvider(gcroot<MusicLibrary::Extension::IAimpExtensionDataStorage^> instance);

    virtual HRESULT WINAPI GetData(IAIMPObjectList* Fields, IAIMPMLDataFilter* Filter, IUnknown** Data);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};

class AimpExtensionDataStorage :
    public IUnknownInterfaceImpl<IAIMPMLExtensionDataStorage>
{
private:
    AimpDataProvider* _aimpDataProvider;
    AimpDataStorageCommandAddFiles* _addFilesCommand = nullptr;
    AimpDataStorageCommandAddFilesDialog* _addFilesDialogCommand = nullptr;
    AimpDataStorageCommandDeleteFiles* _deleteFilesCommand = nullptr;
    AimpDataStorageCommandDropData* _dropDataCommand = nullptr;
    AimpDataStorageCommandReloadTags* _reloadTagsCommand = nullptr;
    AimpDataStorageCommandReportDialog* _reportDialogCommand = nullptr;
    AimpDataStorageCommandUserMark* _userMarkCommand = nullptr;
    gcroot<AimpGroupingPresets^> _managedPresets;

public:
    typedef IUnknownInterfaceImpl<IAIMPMLExtensionDataStorage> Base;

    AimpExtensionDataStorage(IAIMPCore* aimpCore,
                             gcroot<AIMP::SDK::MusicLibrary::Extension::IAimpExtensionDataStorage^> instance);

    virtual void WINAPI Finalize();

    virtual void WINAPI Initialize(IAIMPMLDataStorageManager* Manager);

    virtual HRESULT WINAPI ConfigLoad(IAIMPConfig* Config, IAIMPString* Section);

    virtual HRESULT WINAPI ConfigSave(IAIMPConfig* Config, IAIMPString* Section);

    virtual HRESULT WINAPI GetFields(int Schema, IAIMPObjectList** List);

    virtual HRESULT WINAPI GetGroupingPresets(int Schema, IAIMPMLGroupingPresets* Presets);

    virtual void WINAPI FlushCache(int Reserved);

    virtual void WINAPI BeginUpdate();

    virtual void WINAPI EndUpdate();

    virtual HRESULT WINAPI Reset();

    // Read
    virtual HRESULT WINAPI GetValueAsFloat(int PropertyID, double* Value);

    virtual HRESULT WINAPI GetValueAsInt32(int PropertyID, int* Value);

    virtual HRESULT WINAPI GetValueAsInt64(int PropertyID, INT64* Value);

    virtual HRESULT WINAPI GetValueAsObject(int PropertyID, REFIID IID, void** Value);
    // Write
    virtual HRESULT WINAPI SetValueAsFloat(int PropertyID, const double Value);

    virtual HRESULT WINAPI SetValueAsInt32(int PropertyID, int Value);

    virtual HRESULT WINAPI SetValueAsInt64(int PropertyID, const INT64 Value);

    virtual HRESULT WINAPI SetValueAsObject(int PropertyID, IUnknown* Value);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

private:
    gcroot<AIMP::SDK::MusicLibrary::Extension::IAimpExtensionDataStorage^> _managedInstance;
    IAIMPCore* _aimpCore;
};
