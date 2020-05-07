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

#include "Stdafx.h"
#include "AimpExtensionDataStorage.h"
#include "SDK\AimpConfig.h"

using namespace AIMP::SDK;

#pragma region AimpDataProvider

AimpDataProvider::AimpDataProvider(gcroot<Extension::IAimpExtensionDataStorage^> instance)
{
    _instance = instance;
}

HRESULT WINAPI AimpDataProvider::GetData(IAIMPObjectList* Fields, IAIMPMLDataFilter* Filter, IUnknown** Data)
{
    Object^ obj = _instance;

    IAimpDataProvider^ provider = dynamic_cast<IAimpDataProvider^>(obj);
    if (provider != nullptr)
    {
        Object^ o;
        const ActionResultType result = provider->GetData(AimpConverter::ToStringCollection(Fields),
                                                          gcnew AimpDataFilter(Filter), o);

        if (result == ActionResultType::OK)
        {
            IAimpDataProviderSelection^ selection = dynamic_cast<IAimpDataProviderSelection^>(o);

            if (selection != nullptr)
            {
                *Data = new InternalAimpDataProviderSelection(static_cast<IAimpDataProviderSelection^>(o));
            }
            else
            {
                *Data = AimpConverter::ToAimpString(o->ToString());
            }
        }
    }

    return S_OK;
}

ULONG WINAPI AimpDataProvider::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI AimpDataProvider::Release(void)
{
    return Base::Release();
}

#pragma endregion

#pragma region AimpDataStorageCommandAddFilesDialog
AimpDataStorageCommandAddFilesDialog::AimpDataStorageCommandAddFilesDialog(
    gcroot<IAimpDataStorageCommandAddFilesDialog^> instance)
{
    _instance = instance;
}

HRESULT WINAPI AimpDataStorageCommandAddFilesDialog::Execute(HWND OwnerHandle)
{
    IntPtr ownerHandle(OwnerHandle);
    return HRESULT(_instance->Execute(ownerHandle));
}

HRESULT WINAPI AimpDataStorageCommandAddFilesDialog::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    *ppvObject = nullptr;
    if (riid == IID_IAIMPMLDataStorageCommandAddFilesDialog)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG WINAPI AimpDataStorageCommandAddFilesDialog::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI AimpDataStorageCommandAddFilesDialog::Release(void)
{
    return Base::Release();
}
#pragma endregion

#pragma region AimpDataStorageCommandDeleteFiles
AimpDataStorageCommandDeleteFiles::AimpDataStorageCommandDeleteFiles(
    gcroot<IAimpDataStorageCommandDeleteFiles^> instance)
{
    _instance = instance;
}

BOOL WINAPI AimpDataStorageCommandDeleteFiles::CanDelete(BOOL Physically)
{
    return _instance->CanDelete(Physically);
}

HRESULT WINAPI AimpDataStorageCommandDeleteFiles::Delete(IAIMPMLFileList* Files, BOOL Physically)
{
    return HRESULT(_instance->Delete(gcnew AimpFileList(Files), Physically));
}

HRESULT WINAPI AimpDataStorageCommandDeleteFiles::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    *ppvObject = nullptr;
    if (riid == IID_IAIMPMLDataStorageCommandDeleteFiles)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG WINAPI AimpDataStorageCommandDeleteFiles::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI AimpDataStorageCommandDeleteFiles::Release(void)
{
    return Base::Release();
}
#pragma endregion

#pragma region AimpDataStorageCommandDropData
AimpDataStorageCommandDropData::AimpDataStorageCommandDropData(
    gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandDropData^> instance)
{
    _instance = instance;
}

HRESULT WINAPI AimpDataStorageCommandDropData::DropData()
{
    return HRESULT(_instance->DropData());
}

HRESULT WINAPI AimpDataStorageCommandDropData::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    *ppvObject = nullptr;
    if (riid == IID_IAIMPMLDataStorageCommandDropData)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG WINAPI AimpDataStorageCommandDropData::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI AimpDataStorageCommandDropData::Release(void)
{
    return Base::Release();
}
#pragma endregion

#pragma region AimpDataStorageCommandReloadTags
AimpDataStorageCommandReloadTags::AimpDataStorageCommandReloadTags(gcroot<IAimpDataStorageCommandReloadTags^> instance)
{
    _instance = instance;
}

HRESULT WINAPI AimpDataStorageCommandReloadTags::ReloadTags(IAIMPMLFileList* Files)
{
    return HRESULT(_instance->ReloadTags(gcnew AimpFileList(Files)));
}

HRESULT WINAPI AimpDataStorageCommandReloadTags::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    *ppvObject = nullptr;
    if (riid == IID_IAIMPMLDataStorageCommandReloadTags)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG WINAPI AimpDataStorageCommandReloadTags::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI AimpDataStorageCommandReloadTags::Release(void)
{
    return Base::Release();
}
#pragma endregion

#pragma region AimpDataStorageCommandReportDialog
AimpDataStorageCommandReportDialog::AimpDataStorageCommandReportDialog(
    gcroot<IAimpDataStorageCommandReportDialog^> instance)
{
    _instance = instance;
}

HRESULT WINAPI AimpDataStorageCommandReportDialog::Execute(HWND OwnerHandle)
{
    IntPtr ownerHandle(OwnerHandle);
    return HRESULT(_instance->Execute(ownerHandle));
}

HRESULT WINAPI AimpDataStorageCommandReportDialog::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    *ppvObject = nullptr;
    if (riid == IID_IAIMPMLDataStorageCommandReportDialog)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG WINAPI AimpDataStorageCommandReportDialog::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI AimpDataStorageCommandReportDialog::Release(void)
{
    return Base::Release();
}
#pragma endregion

#pragma region AimpDataStorageCommandUserMark
AimpDataStorageCommandUserMark::AimpDataStorageCommandUserMark(gcroot<IAimpDataStorageCommandUserMark^> instance)
{
    _instance = instance;
}

HRESULT WINAPI AimpDataStorageCommandUserMark::SetMark(VARIANT* ID, const DOUBLE Value)
{
    return HRESULT(_instance->SetMark(AimpConverter::FromVaiant(ID), Value));
}

HRESULT WINAPI AimpDataStorageCommandUserMark::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    *ppvObject = nullptr;
    if (riid == IID_IAIMPMLDataStorageCommandUserMark)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG WINAPI AimpDataStorageCommandUserMark::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI AimpDataStorageCommandUserMark::Release(void)
{
    return Base::Release();
}
#pragma endregion

#pragma region AimpExtensionDataStorage
AimpExtensionDataStorage::AimpExtensionDataStorage(IAIMPCore* aimpCore,
                                                   gcroot<Extension::IAimpExtensionDataStorage^> instance)
{
    _managedInstance = instance;
    _aimpCore = aimpCore;

    Object^ obj = _managedInstance;

    IAimpDataStorageCommandAddFiles^ AddFilesCommand = dynamic_cast<IAimpDataStorageCommandAddFiles^>(obj);
    IAimpDataStorageCommandAddFilesDialog^ AddFilesDialogCommand = dynamic_cast<IAimpDataStorageCommandAddFilesDialog^>(
        obj);
    IAimpDataStorageCommandDeleteFiles^ DeleteFilesCommand = dynamic_cast<IAimpDataStorageCommandDeleteFiles^>(obj);
    IAimpDataStorageCommandDropData^ dropDataCommand = dynamic_cast<IAimpDataStorageCommandDropData^>(obj);
    IAimpDataStorageCommandReloadTags^ reloadTagsCommand = dynamic_cast<IAimpDataStorageCommandReloadTags^>(obj);
    IAimpDataStorageCommandReportDialog^ reportDialogCommand = dynamic_cast<IAimpDataStorageCommandReportDialog^>(obj);
    IAimpDataStorageCommandUserMark^ userMarkCommand = dynamic_cast<IAimpDataStorageCommandUserMark^>(obj);

    if (AddFilesDialogCommand != nullptr)
    {
        _addFilesDialogCommand = new AimpDataStorageCommandAddFilesDialog(AddFilesDialogCommand);
    }

    if (AddFilesCommand != nullptr)
    {
        _addFilesCommand = new AimpDataStorageCommandAddFiles(AddFilesCommand);
    }

    if (DeleteFilesCommand != nullptr)
    {
        _deleteFilesCommand = new AimpDataStorageCommandDeleteFiles(DeleteFilesCommand);
    }

    if (dropDataCommand != nullptr)
    {
        _dropDataCommand = new AimpDataStorageCommandDropData(dropDataCommand);
    }

    if (reloadTagsCommand != nullptr)
    {
        _reloadTagsCommand = new AimpDataStorageCommandReloadTags(reloadTagsCommand);
    }

    if (reportDialogCommand != nullptr)
    {
        _reportDialogCommand = new AimpDataStorageCommandReportDialog(reportDialogCommand);
    }

    if (userMarkCommand != nullptr)
    {
        _userMarkCommand = new AimpDataStorageCommandUserMark(userMarkCommand);
    }

    _aimpDataProvider = new AimpDataProvider(instance);
}

void WINAPI AimpExtensionDataStorage::Finalize()
{
    _managedInstance->Terminate();
    _aimpDataProvider->Release();
    _aimpDataProvider = nullptr;

    if (_addFilesCommand != nullptr)
        _addFilesCommand->Release();

    if (_addFilesDialogCommand != nullptr)
        _addFilesDialogCommand->Release();

    if (_deleteFilesCommand != nullptr)
        _deleteFilesCommand->Release();

    if (_dropDataCommand != nullptr)
        _dropDataCommand->Release();

    if (_reloadTagsCommand != nullptr)
        _reloadTagsCommand->Release();

    if (_reportDialogCommand != nullptr)
        _reportDialogCommand->Release();

    if (_userMarkCommand != nullptr)
        _userMarkCommand->Release();

    _managedInstance = nullptr;
}

void WINAPI AimpExtensionDataStorage::Initialize(IAIMPMLDataStorageManager* Manager)
{
    IAimpDataStorageManager^ manager = gcnew AimpDataStorageManager(Manager);
    _managedInstance->Initialize(manager);
}

HRESULT WINAPI AimpExtensionDataStorage::ConfigLoad(IAIMPConfig* Config, IAIMPString* Section)
{
    IAimpConfig^ cfg = gcnew AimpConfig(Config);
    return HRESULT(_managedInstance->ConfigLoad(cfg, AimpConverter::ToManagedString(Section)));
}

HRESULT WINAPI AimpExtensionDataStorage::ConfigSave(IAIMPConfig* Config, IAIMPString* Section)
{
    IAimpConfig^ cfg = gcnew AimpConfig(Config);
    return HRESULT(_managedInstance->ConfigSave(cfg, AimpConverter::ToManagedString(Section)));
}

HRESULT WINAPI AimpExtensionDataStorage::GetFields(int Schema, IAIMPObjectList** List)
{
    IAIMPObjectList* L = AimpConverter::GetAimpObjectList();

    Collections::IList^ collection;
    ActionResultType result = _managedInstance->GetFields(static_cast<Extension::SchemaType>(Schema), collection);

    if (collection == nullptr)
    {
        return HRESULT(result);
    }

    auto t = collection->GetType()->GetGenericArguments()[0];
    if (t == IAimpDataField::typeid)
    {
        for (int i = 0; i < collection->Count; i++)
        {
            auto dataField = static_cast<IAimpDataField^>(collection[i]);
            IAIMPMLDataField* df = AimpConverter::GetAimpDataField();

            PropertyListExtension::SetInt32(df, AIMPML_FIELD_PROPID_TYPE, int(dataField->Type));
            PropertyListExtension::SetString(df, AIMPML_FIELD_PROPID_NAME, dataField->Name);
            PropertyListExtension::SetInt32(df, AIMPML_FIELD_PROPID_FLAGS, int(dataField->Flags));

            L->Add(df);
            df->Release();
        }
    }
    else if (t == String::typeid)
    {
        for (int i = 0; i < collection->Count; i++)
        {
            auto str = static_cast<String^>(collection[i]);
            IAIMPString* s = AimpConverter::ToAimpString(str);
            L->Add(s);
            s->Release();
        }
    }

    *List = L;

    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::GetGroupingPresets(int Schema, IAIMPMLGroupingPresets* Presets)
{
    _managedPresets = gcnew AimpGroupingPresets(Presets);
    return HRESULT(_managedInstance->GetGroupingPresets(static_cast<Extension::GroupingPresetsSchemaType>(Schema),
                                                        _managedPresets));
}

void WINAPI AimpExtensionDataStorage::FlushCache(int Reserved)
{
    _managedInstance->FlushCache();
}

void WINAPI AimpExtensionDataStorage::BeginUpdate()
{
}

void WINAPI AimpExtensionDataStorage::EndUpdate()
{
}

HRESULT WINAPI AimpExtensionDataStorage::Reset()
{
    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::GetValueAsFloat(int PropertyID, double* Value)
{
    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::GetValueAsInt32(int PropertyID, int* Value)
{
    if (PropertyID == AIMPML_DATASTORAGE_PROPID_CAPABILITIES)
    {
        *Value = int(_managedInstance->Capabilities);
    }

    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::GetValueAsInt64(int PropertyID, INT64* Value)
{
    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::GetValueAsObject(int PropertyID, REFIID IID, void** Value)
{
    if (PropertyID == AIMPML_DATASTORAGE_PROPID_ID)
    {
        *Value = AimpConverter::ToAimpString(_managedInstance->Id);
    }

    if (PropertyID == AIMPML_DATASTORAGE_PROPID_CAPTION)
    {
        *Value = AimpConverter::ToAimpString(_managedInstance->Caption);
    }

    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::SetValueAsFloat(int PropertyID, const double Value)
{
    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::SetValueAsInt32(int PropertyID, int Value)
{
    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::SetValueAsInt64(int PropertyID, const INT64 Value)
{
    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::SetValueAsObject(int PropertyID, IUnknown* Value)
{
    // TODO complete it
    return S_OK;

    if (PropertyID == AIMPML_DATASTORAGE_PROPID_ID)
    {
        AIMP::SDK::PropertyListExtension::SetString(this, AIMPML_DATASTORAGE_PROPID_ID, _managedInstance->Id);
    }

    if (PropertyID == AIMPML_DATASTORAGE_PROPID_CAPTION)
    {
        AIMP::SDK::PropertyListExtension::SetString(this, AIMPML_DATASTORAGE_PROPID_CAPTION, _managedInstance->Caption);
    }

    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    if (!ppvObject)
    {
        return E_POINTER;
    }

    if (riid == IID_IAIMPMLDataProvider)
    {
        *ppvObject = _aimpDataProvider;
        _aimpDataProvider->AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPMLExtensionDataStorage)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPMLDataStorageCommandAddFilesDialog && _addFilesDialogCommand != nullptr)
    {
        return _addFilesDialogCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandDeleteFiles && _deleteFilesCommand != nullptr)
    {
        return _deleteFilesCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandAddFiles && _addFilesCommand != nullptr)
    {
        return _addFilesCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandDropData && _dropDataCommand != nullptr)
    {
        return _dropDataCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandReloadTags && _reloadTagsCommand != nullptr)
    {
        return _reloadTagsCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandUserMark && _userMarkCommand != nullptr)
    {
        return _userMarkCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandReportDialog && _reportDialogCommand != nullptr)
    {
        return _reportDialogCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLGroupingTreeDataProvider)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG WINAPI AimpExtensionDataStorage::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI AimpExtensionDataStorage::Release(void)
{
    return Base::Release();
}
#pragma endregion
