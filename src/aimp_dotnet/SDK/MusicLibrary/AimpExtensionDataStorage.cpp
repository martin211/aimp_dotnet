/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#include "Stdafx.h"
#include "AimpExtensionDataStorage.h"

using namespace AIMP::SDK;

#pragma region AimpDataProvider

AimpDataProvider::AimpDataProvider(gcroot<AIMP::SDK::MusicLibrary::Extension::IAimpExtensionDataStorage^> instance)
{
    _instance = instance;
}

HRESULT WINAPI AimpDataProvider::GetData(IAIMPObjectList* Fields, IAIMPMLDataFilter* Filter, IUnknown** Data)
{
    System::Diagnostics::Debug::WriteLine("Get data");
    System::Object^ obj = _instance;

    IAimpDataProvider^ provider = dynamic_cast<IAimpDataProvider^>(obj);
    if (provider != nullptr)
    {
        System::Object^ o;
        AimpActionResult result = provider->GetData(AimpConverter::ToStringCollection(Fields), gcnew AimpDataFilter(Filter), o);

        if (result == AimpActionResult::Ok)
        {
            IAimpDataProviderSelection^ selection = dynamic_cast<IAimpDataProviderSelection^>(o);

            if (selection != nullptr)
            {
                *Data = new InternalAimpDataProviderSelection((IAimpDataProviderSelection^)o);
            }
            else
            {
                *Data = AIMP::SDK::AimpConverter::ToAimpString(o->ToString());
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
AimpDataStorageCommandAddFilesDialog::AimpDataStorageCommandAddFilesDialog(gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandAddFilesDialog^> instance)
{
    _instance = instance;
}

HRESULT WINAPI AimpDataStorageCommandAddFilesDialog::Execute(HWND OwnerHandle)
{
    System::IntPtr ownerHandle(OwnerHandle);
    return (HRESULT)_instance->Execute(ownerHandle);
}

HRESULT WINAPI AimpDataStorageCommandAddFilesDialog::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    *ppvObject = NULL;
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
AimpDataStorageCommandDeleteFiles::AimpDataStorageCommandDeleteFiles(gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandDeleteFiles^> instance)
{
    _instance = instance;
}

BOOL WINAPI AimpDataStorageCommandDeleteFiles::CanDelete(BOOL Physically)
{
    return _instance->CanDelete(Physically);
}

HRESULT WINAPI AimpDataStorageCommandDeleteFiles::Delete(IAIMPMLFileList* Files, BOOL Physically)
{
    return (HRESULT)_instance->Delete(gcnew AimpFileList(Files), Physically);
}

HRESULT WINAPI AimpDataStorageCommandDeleteFiles::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    *ppvObject = NULL;
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
AimpDataStorageCommandDropData::AimpDataStorageCommandDropData(gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandDropData^> instance)
{
    _instance = instance;
}

HRESULT WINAPI AimpDataStorageCommandDropData::DropData()
{
    return (HRESULT)_instance->DropData();
}

HRESULT WINAPI AimpDataStorageCommandDropData::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    *ppvObject = NULL;
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
AimpDataStorageCommandReloadTags::AimpDataStorageCommandReloadTags(gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandReloadTags^> instance)
{
    _instance = instance;
}

HRESULT WINAPI AimpDataStorageCommandReloadTags::ReloadTags(IAIMPMLFileList* Files)
{
    return (HRESULT)_instance->ReloadTags(gcnew AimpFileList(Files));
}

HRESULT WINAPI AimpDataStorageCommandReloadTags::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    *ppvObject = NULL;
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
AimpDataStorageCommandReportDialog::AimpDataStorageCommandReportDialog(gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandReportDialog^> instance)
{
    _instance = instance;
}

HRESULT WINAPI AimpDataStorageCommandReportDialog::Execute(HWND OwnerHandle)
{
    System::IntPtr ownerHandle(OwnerHandle);
    return (HRESULT)_instance->Execute(ownerHandle);
}

HRESULT WINAPI AimpDataStorageCommandReportDialog::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    *ppvObject = NULL;
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
AimpDataStorageCommandUserMark::AimpDataStorageCommandUserMark(gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandUserMark^> instance)
{
    _instance = instance;
}

HRESULT WINAPI AimpDataStorageCommandUserMark::SetMark(VARIANT* ID, const DOUBLE Value)
{
    return (HRESULT)_instance->SetMark(AIMP::SDK::AimpConverter::FromVaiant(ID), Value);
}

HRESULT WINAPI AimpDataStorageCommandUserMark::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    *ppvObject = NULL;
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
AimpExtensionDataStorage::AimpExtensionDataStorage(IAIMPCore *aimpCore, gcroot<AIMP::SDK::MusicLibrary::Extension::IAimpExtensionDataStorage^> instance)
{
    _managedInstance = instance;
    _aimpCore = aimpCore;

    Object^ obj = _managedInstance;

    IAimpDataStorageCommandAddFiles^ AddFilesCommand = dynamic_cast<IAimpDataStorageCommandAddFiles^>(obj);
    IAimpDataStorageCommandAddFilesDialog^ AddFilesDialogCommand = dynamic_cast<IAimpDataStorageCommandAddFilesDialog^>(obj);
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
    _aimpDataProvider = NULL;

    if (_addFilesCommand != NULL)
        _addFilesCommand->Release();

    if (_addFilesDialogCommand != NULL)
        _addFilesDialogCommand->Release();

    if (_deleteFilesCommand != NULL)
        _deleteFilesCommand->Release();

    if (_dropDataCommand != NULL)
        _dropDataCommand->Release();

    if (_reloadTagsCommand != NULL)
        _reloadTagsCommand->Release();

    if (_reportDialogCommand != NULL)
        _reportDialogCommand->Release();

    if (_userMarkCommand != NULL)
        _userMarkCommand->Release();

    _managedInstance = nullptr;
}

void WINAPI AimpExtensionDataStorage::Initialize(IAIMPMLDataStorageManager* Manager)
{
    IAimpDataStorageManager ^manager = gcnew AimpDataStorageManager(Manager);
    _managedInstance->Initialize(manager);
}

HRESULT WINAPI AimpExtensionDataStorage::ConfigLoad(IAIMPConfig *Config, IAIMPString* Section)
{
    return (HRESULT)_managedInstance->ConfigLoad(nullptr, AIMP::SDK::AimpConverter::ToManagedString(Section));
}

HRESULT WINAPI AimpExtensionDataStorage::ConfigSave(IAIMPConfig *Config, IAIMPString* Section)
{
    return (HRESULT)_managedInstance->ConfigSave(nullptr, AIMP::SDK::AimpConverter::ToManagedString(Section));
}

HRESULT WINAPI AimpExtensionDataStorage::GetFields(int Schema, IAIMPObjectList** List)
{
    IAIMPObjectList *L = AIMP::SDK::AimpConverter::GetAimpObjectList();

    System::Collections::IList ^collection;
    AimpActionResult result = _managedInstance->GetFields((AIMP::SDK::MusicLibrary::Extension::SchemaType)Schema, collection);

    if (collection == nullptr)
    {
        return (HRESULT)result;
    }

    System::Type^ t = collection->GetType()->GetGenericArguments()[0];
    if (t == AIMP::SDK::MusicLibrary::DataStorage::IAimpDataField::typeid)
    {
        for (int i = 0; i < collection->Count; i++)
        {
            AIMP::SDK::MusicLibrary::DataStorage::IAimpDataField ^dataField = (AIMP::SDK::MusicLibrary::DataStorage::IAimpDataField^)collection[i];
            IAIMPMLDataField *df = AIMP::SDK::AimpConverter::GetAimpDataField();

            AIMP::SDK::PropertyListExtension::SetInt32(df, AIMPML_FIELD_PROPID_TYPE, (int)dataField->Type);
            AIMP::SDK::PropertyListExtension::SetString(df, AIMPML_FIELD_PROPID_NAME, dataField->Name);
            AIMP::SDK::PropertyListExtension::SetInt32(df, AIMPML_FIELD_PROPID_FLAGS, (int)dataField->Flags);

            L->Add(df);
            df->Release();
        }
    }
    else if (t == System::String::typeid)
    {
        for (int i = 0; i < collection->Count; i++)
        {
            System::String^ str = (System::String^)collection[i];
            IAIMPString *s = AIMP::SDK::AimpConverter::ToAimpString(str);
            L->Add(s);
            s->Release();
        }
    }

    *List = L;

    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::GetGroupingPresets(int Schema, IAIMPMLGroupingPresets* Presets)
{
    _managedPresets = gcnew AIMP::SDK::AimpGroupingPresets(Presets);
    return (HRESULT)_managedInstance->GetGroupingPresets((AIMP::SDK::MusicLibrary::Extension::GroupingPresetsSchemaType)Schema, _managedPresets);
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

HRESULT WINAPI AimpExtensionDataStorage::GetValueAsFloat(int PropertyID, double *Value)
{
    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::GetValueAsInt32(int PropertyID, int *Value)
{
    if (PropertyID == AIMPML_DATASTORAGE_PROPID_CAPABILITIES)
    {
        *Value = (int)_managedInstance->Capabilities;
    }

    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::GetValueAsInt64(int PropertyID, INT64 *Value)
{
    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::GetValueAsObject(int PropertyID, REFIID IID, void **Value)
{
    if (PropertyID == AIMPML_DATASTORAGE_PROPID_ID)
    {
        *Value = AIMP::SDK::AimpConverter::ToAimpString(_managedInstance->Id);
    }

    if (PropertyID == AIMPML_DATASTORAGE_PROPID_CAPTION)
    {
        *Value = AIMP::SDK::AimpConverter::ToAimpString(_managedInstance->Caption);
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

HRESULT WINAPI AimpExtensionDataStorage::SetValueAsObject(int PropertyID, IUnknown *Value)
{
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

    if (riid == IID_IAIMPMLDataStorageCommandAddFilesDialog && _addFilesDialogCommand != NULL)
    {
        return _addFilesDialogCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandDeleteFiles && _deleteFilesCommand != NULL)
    {
        return _deleteFilesCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandAddFiles && _addFilesCommand != NULL)
    {
        return _addFilesCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandDropData && _dropDataCommand != NULL)
    {
        return _dropDataCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandReloadTags && _reloadTagsCommand != NULL)
    {
        return _reloadTagsCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandUserMark && _userMarkCommand != NULL)
    {
        return _userMarkCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandReportDialog && _reportDialogCommand != NULL)
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
