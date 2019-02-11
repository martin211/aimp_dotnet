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
#include "AimpDataStorageManager.h"
#include "AimpGroupingPresets.h"
#include "AimpDataFilter.h"
#include "InternalAimpDataProviderSelection.h"
#include "AimpFileList.h"

using namespace AIMP::SDK::MusicLibrary::Extension::Command;

class AimpDataProvider : public IUnknownInterfaceImpl<IAIMPMLDataProvider>
{
private:
    gcroot<AIMP::SDK::MusicLibrary::Extension::IAimpExtensionDataStorage^> _instance;

public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataProvider> Base;

    AimpDataProvider(gcroot<AIMP::SDK::MusicLibrary::Extension::IAimpExtensionDataStorage^> instance);

    virtual HRESULT WINAPI GetData(IAIMPObjectList* Fields, IAIMPMLDataFilter* Filter, IUnknown** Data);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};

class AimpDataStorageCommandAddFiles : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandAddFiles>
{
private:
    gcroot<IAimpDataStorageCommandAddFiles^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandAddFiles> Base;

    AimpDataStorageCommandAddFiles(gcroot<IAimpDataStorageCommandAddFiles^> instance)
    {
        _instance = instance;
    }

    virtual HRESULT WINAPI Add(IAIMPObjectList* Files)
    {
        return HRESULT(_instance->Add(nullptr));
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        *ppvObject = nullptr;
        if (riid == IID_IAIMPMLDataStorageCommandAddFiles)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }
};

class AimpDataStorageCommandAddFilesDialog : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandAddFilesDialog>
{
private:
    gcroot<IAimpDataStorageCommandAddFilesDialog^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandAddFilesDialog> Base;

    AimpDataStorageCommandAddFilesDialog(gcroot<IAimpDataStorageCommandAddFilesDialog^> instance);

    virtual HRESULT WINAPI Execute(HWND OwnerHandle);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};

class AimpDataStorageCommandDeleteFiles : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandDeleteFiles>
{
private:
    gcroot<IAimpDataStorageCommandDeleteFiles^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandDeleteFiles> Base;

    AimpDataStorageCommandDeleteFiles(gcroot<IAimpDataStorageCommandDeleteFiles^> instance);

    virtual BOOL WINAPI CanDelete(BOOL Physically);

    virtual HRESULT WINAPI Delete(IAIMPMLFileList* Files, BOOL Physically);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};

class AimpDataStorageCommandDropData : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandDropData>
{
private:
    gcroot<IAimpDataStorageCommandDropData^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandDropData> Base;

    AimpDataStorageCommandDropData(gcroot<IAimpDataStorageCommandDropData^> instance);

    virtual HRESULT WINAPI DropData();

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};

class AimpDataStorageCommandReloadTags : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandReloadTags>
{
private:
    gcroot<IAimpDataStorageCommandReloadTags^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandReloadTags> Base;

    AimpDataStorageCommandReloadTags(gcroot<IAimpDataStorageCommandReloadTags^> instance);

    virtual HRESULT WINAPI ReloadTags(IAIMPMLFileList* Files);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};

class AimpDataStorageCommandReportDialog : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandReportDialog>
{
private:
    gcroot<IAimpDataStorageCommandReportDialog^> _instance;

public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandReportDialog> Base;

    AimpDataStorageCommandReportDialog(gcroot<IAimpDataStorageCommandReportDialog^> instance);

    virtual HRESULT WINAPI Execute(HWND OwnerHandle);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};

class AimpDataStorageCommandUserMark : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandUserMark>
{
private:
    gcroot<IAimpDataStorageCommandUserMark^> _instance;

public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandUserMark> Base;

    AimpDataStorageCommandUserMark(gcroot<IAimpDataStorageCommandUserMark^> instance);

    virtual HRESULT WINAPI SetMark(VARIANT* ID, const DOUBLE Value);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

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
    gcroot<AIMP::SDK::AimpGroupingPresets^> _managedPresets;

public:
    typedef IUnknownInterfaceImpl<IAIMPMLExtensionDataStorage> Base;

    AimpExtensionDataStorage(IAIMPCore *aimpCore, gcroot<AIMP::SDK::MusicLibrary::Extension::IAimpExtensionDataStorage^> instance);

    virtual void WINAPI Finalize();

    virtual void WINAPI Initialize(IAIMPMLDataStorageManager* Manager);

    virtual HRESULT WINAPI ConfigLoad(IAIMPConfig *Config, IAIMPString* Section);

    virtual HRESULT WINAPI ConfigSave(IAIMPConfig *Config, IAIMPString* Section);

    virtual HRESULT WINAPI GetFields(int Schema, IAIMPObjectList** List);

    virtual HRESULT WINAPI GetGroupingPresets(int Schema, IAIMPMLGroupingPresets* Presets);

    virtual void WINAPI FlushCache(int Reserved);

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

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

private:
    gcroot<AIMP::SDK::MusicLibrary::Extension::IAimpExtensionDataStorage^> _managedInstance;
    IAIMPCore *_aimpCore;
};
