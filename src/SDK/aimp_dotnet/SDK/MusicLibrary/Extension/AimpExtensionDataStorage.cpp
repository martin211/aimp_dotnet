//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "SDK/AimpConfig.h"
#include "AimpExtensionDataStorage.h"
#include "Command/AimpDataStorageCommandAddFiles.h"
#include "Command/AimpDataStorageCommandAddFilesDialog.h"
#include "Command/AimpDataStorageCommandDeleteFiles.h"
#include "Command/AimpDataStorageCommandDropData.h"
#include "Command/AimpDataStorageCommandReloadTags.h"
#include "Command/AimpDataStorageCommandReportDialog.h"
#include "Command/AimpDataStorageCommandUserMark.h"
#include "SDK/MusicLibrary/AimpDataStorageManager.h"
#include "SDK/MusicLibrary/InternalAimpDataProviderSelection.h"
#include "SDK/MusicLibrary/DataFilter/AimpDataFilter.h"

using namespace AIMP::SDK;
using namespace AIMP::SDK::MusicLibrary;
using namespace AIMP::SDK::MusicLibrary::Extension;
using namespace AIMP::SDK::MusicLibrary::Extension::Command;

#pragma region AimpDataProvider

AimpDataProvider::AimpDataProvider(gcroot<IAimpExtensionDataStorage^> instance) {
    _instance = instance;
}

HRESULT WINAPI AimpDataProvider::GetData(IAIMPObjectList* Fields, IAIMPMLDataFilter* Filter, IUnknown** Data) {
    Object^ obj = _instance;

    IAimpDataProvider^ provider = dynamic_cast<IAimpDataProvider^>(obj);
    if (provider != nullptr) {
        const auto result = provider->GetData(AimpConverter::ToStringCollection(Fields), gcnew AimpDataFilter(Filter));

        if (result->ResultType == ActionResultType::OK) {
            IAimpDataProviderSelection^ selection = dynamic_cast<IAimpDataProviderSelection^>(result->Result);

            if (selection != nullptr) {
                *Data = new InternalAimpDataProviderSelection(static_cast<IAimpDataProviderSelection^>(result->Result));
            }
            else {
                *Data = AimpConverter::ToAimpString(result->Result->ToString());
            }
        }

        return static_cast<HRESULT>(result->ResultType);
    }

    return E_FAIL;
}

ULONG WINAPI AimpDataProvider::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI AimpDataProvider::Release(void) {
    return Base::Release();
}

#pragma endregion

#pragma region AimpDataProvider2

AimpDataProvider2::AimpDataProvider2(gcroot<IAimpExtensionDataStorage^> instance) {
    _instance = instance;
}

HRESULT AimpDataProvider2::GetData(IAIMPObjectList* Fields, IAIMPMLDataFilter* Filter, IUnknown* Reserved, IUnknown** PageID, IUnknown** Data) {
    Object^ obj = _instance;

    IAimpDataProvider2^ provider = dynamic_cast<IAimpDataProvider2^>(obj);
    if (provider != nullptr) {
        String^ page = nullptr;

        if (*PageID != nullptr) {
            page = AimpConverter::ToManagedString(static_cast<IAIMPString*>(*PageID));
        }

        const auto result = provider->GetData(
            AimpConverter::ToStringCollection(Fields),
            gcnew AimpDataFilter(Filter),
            page);

        if (result->ResultType == ActionResultType::OK) {
            if (result->Result->PageId != nullptr) {
                *PageID = AimpConverter::ToAimpString(result->Result->PageId);
            }

            if (result->Result->IsEmpty) {
                *Data = AimpConverter::ToAimpString(result->Result->NoData);
            } else {
                IAimpDataProviderSelection^ selection = dynamic_cast<IAimpDataProviderSelection^>(result->Result->Data);

                if (selection != nullptr) {
                    *Data = new InternalAimpDataProviderSelection(static_cast<IAimpDataProviderSelection^>(result->Result->Data));
                } else {
                    return E_FAIL;
                }
            }
        }

        return static_cast<HRESULT>(result->ResultType);
    }

    return E_FAIL;
}

ULONG AimpDataProvider2::AddRef() {
    return Base::AddRef();
}

ULONG AimpDataProvider2::Release() {
    return Base::Release();
}

#pragma endregion


#pragma region AimpExtensionDataStorage
AimpExtensionDataStorage::AimpExtensionDataStorage(IAIMPCore* aimpCore, gcroot<IAimpExtensionDataStorage^> instance) {
    _managedInstance = instance;
    _aimpCore = aimpCore;

    Object^ obj = _managedInstance;

    const auto addFilesCommand = dynamic_cast<IAimpDataStorageCommandAddFiles^>(obj);
    const auto addFilesDialogCommand = dynamic_cast<IAimpDataStorageCommandAddFilesDialog^>(obj);
    const auto deleteFilesCommand = dynamic_cast<IAimpDataStorageCommandDeleteFiles^>(obj);
    const auto dropDataCommand = dynamic_cast<IAimpDataStorageCommandDropData^>(obj);
    const auto reloadTagsCommand = dynamic_cast<IAimpDataStorageCommandReloadTags^>(obj);
    const auto userMarkCommand = dynamic_cast<IAimpDataStorageCommandUserMark^>(obj);
    const auto reportDialogCommand = dynamic_cast<IAimpDataStorageCommandReportDialog^>(obj);
    const auto deleteFilesCommand2 = dynamic_cast<IAimpDataStorageCommandDeleteFiles2^>(obj);
    const auto findInLibraryCommand = dynamic_cast<IAimpDataStorageCommandFindInLibrary^>(obj);
    const auto albumArtProvider = dynamic_cast<IAimpAlbumArtProvider^>(obj);
    const auto albumArtProvider2 = dynamic_cast<IAimpAlbumArtProvider2^>(obj);

    if (addFilesDialogCommand != nullptr) {
        _addFilesDialogCommand = new AimpDataStorageCommandAddFilesDialog(addFilesDialogCommand);
    }

    if (addFilesCommand != nullptr) {
        _addFilesCommand = new AimpDataStorageCommandAddFiles(addFilesCommand);
    }

    if (deleteFilesCommand != nullptr) {
        _deleteFilesCommand = new AimpDataStorageCommandDeleteFiles(deleteFilesCommand);
    }

    if (dropDataCommand != nullptr) {
        _dropDataCommand = new AimpDataStorageCommandDropData(dropDataCommand);
    }

    if (reloadTagsCommand != nullptr) {
        _reloadTagsCommand = new AimpDataStorageCommandReloadTags(reloadTagsCommand);
    }

    if (reportDialogCommand != nullptr) {
        _reportDialogCommand = new AimpDataStorageCommandReportDialog(reportDialogCommand);
    }

    if (userMarkCommand != nullptr) {
        _userMarkCommand = new AimpDataStorageCommandUserMark(userMarkCommand);
    }

    if (deleteFilesCommand2 != nullptr) {
        _deleteFilesCommand2 = new AimpDataStorageCommandDeleteFiles2(deleteFilesCommand2);
    }

    if (findInLibraryCommand != nullptr) {
        _findInLibraryCommand = new AimpDataStorageCommandFindInLibrary(findInLibraryCommand);
    }

    const auto provider2 = dynamic_cast<IAimpDataProvider2^>(obj);

    if (provider2 != nullptr) {
        _aimpDataProvider2 = new AimpDataProvider2(instance);
    } else {
        _aimpDataProvider = new AimpDataProvider(instance);
    }

    if (albumArtProvider != nullptr) {
        _albumArtProvider = new InternalAimpAlbumArtProvider(albumArtProvider);
    }

    if (albumArtProvider2 != nullptr) {
        _albumArtProvider2 = new InternalAimpAlbumArtProvider2(albumArtProvider2);
    }
}

void WINAPI AimpExtensionDataStorage::Finalize() {
    if (_disposed) {
        return;
    }

    if (static_cast<IAimpExtensionDataStorage^>(_managedInstance) != nullptr) {
        _managedInstance->Terminate();
        _managedInstance = nullptr;
    }

    if (_aimpDataProvider != nullptr)
        _aimpDataProvider->Release();

    if (_aimpDataProvider2 != nullptr)
        _aimpDataProvider2->Release();

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

    if (_albumArtProvider != nullptr)
        _albumArtProvider->Release();

    if (_albumArtProvider2 != nullptr)
        _albumArtProvider2->Release();

    _disposed = true;
}

void WINAPI AimpExtensionDataStorage::Initialize(IAIMPMLDataStorageManager* Manager) {
    IAimpDataStorageManager^ manager = gcnew AimpDataStorageManager(Manager);
    _managedInstance->Initialize(manager);
}

HRESULT WINAPI AimpExtensionDataStorage::ConfigLoad(IAIMPConfig* Config, IAIMPString* Section) {
    IAimpConfig^ cfg = gcnew AimpConfig(Config);
    return HRESULT(_managedInstance->ConfigLoad(cfg, AimpConverter::ToManagedString(Section))->ResultType);
}

HRESULT WINAPI AimpExtensionDataStorage::ConfigSave(IAIMPConfig* Config, IAIMPString* Section) {
    IAimpConfig^ cfg = gcnew AimpConfig(Config);
    return HRESULT(_managedInstance->ConfigSave(cfg, AimpConverter::ToManagedString(Section))->ResultType);
}

HRESULT WINAPI AimpExtensionDataStorage::GetFields(int Schema, IAIMPObjectList** List) {
    IAIMPObjectList* objects = AimpConverter::GetAimpObjectList();

    auto result = _managedInstance->GetFields(static_cast<Extension::SchemaType>(Schema));
    Collections::IList^ collection = result->Result;

    if (collection == nullptr) {
        return HRESULT(result->ResultType);
    }

    auto t = collection->GetType()->GetGenericArguments()[0];
    if (t == DataStorage::IAimpDataField::typeid) {
        for (int i = 0; i < collection->Count; i++) {
            auto dataField = static_cast<DataStorage::IAimpDataField^>(collection[i]);
            IAIMPMLDataField* df = AimpConverter::GetAimpDataField();

            PropertyListExtension::SetInt32(df, AIMPML_FIELD_PROPID_TYPE, static_cast<int>(dataField->Type));
            PropertyListExtension::SetString(df, AIMPML_FIELD_PROPID_NAME, dataField->Name);
            PropertyListExtension::SetInt32(df, AIMPML_FIELD_PROPID_FLAGS, static_cast<int>(dataField->Flags));

            objects->Add(df);
            df->Release();
        }
    }
    else if (t == String::typeid) {
        for (int i = 0; i < collection->Count; i++) {
            auto str = static_cast<String^>(collection[i]);
            IAIMPString* s = AimpConverter::ToAimpString(str);
            objects->Add(s);
            s->Release();
        }
    }

    *List = objects;

    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::GetGroupingPresets(int Schema, IAIMPMLGroupingPresets* Presets) {
    _managedPresets = gcnew AimpGroupingPresets(Presets);
    return HRESULT(_managedInstance->GetGroupingPresets(static_cast<Extension::GroupingPresetsSchemaType>(Schema),
                                                        _managedPresets)->ResultType);
}

void WINAPI AimpExtensionDataStorage::FlushCache(int Reserved) {
    _managedInstance->FlushCache();
}

void WINAPI AimpExtensionDataStorage::BeginUpdate() {
}

void WINAPI AimpExtensionDataStorage::EndUpdate() {
}

HRESULT WINAPI AimpExtensionDataStorage::Reset() {
    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::GetValueAsFloat(int PropertyID, double* Value) {
    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::GetValueAsInt32(int PropertyID, int* Value) {
    if (PropertyID == AIMPML_DATASTORAGE_PROPID_CAPABILITIES) {
        *Value = static_cast<int>(_managedInstance->Capabilities);
    }

    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::GetValueAsInt64(int PropertyID, INT64* Value) {
    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::GetValueAsObject(int PropertyID, REFIID IID, void** Value) {
    if (PropertyID == AIMPML_DATASTORAGE_PROPID_ID) {
        *Value = AimpConverter::ToAimpString(_managedInstance->Id);
    }

    if (PropertyID == AIMPML_DATASTORAGE_PROPID_CAPTION) {
        *Value = AimpConverter::ToAimpString(_managedInstance->Caption);
    }

    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::SetValueAsFloat(int PropertyID, const double Value) {
    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::SetValueAsInt32(int PropertyID, int Value) {
    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::SetValueAsInt64(int PropertyID, const INT64 Value) {
    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::SetValueAsObject(int PropertyID, IUnknown* Value) {
    // TODO complete it
    return S_OK;

    if (PropertyID == AIMPML_DATASTORAGE_PROPID_ID) {
        AIMP::SDK::PropertyListExtension::SetString(this, AIMPML_DATASTORAGE_PROPID_ID, _managedInstance->Id);
    }

    if (PropertyID == AIMPML_DATASTORAGE_PROPID_CAPTION) {
        AIMP::SDK::PropertyListExtension::SetString(this, AIMPML_DATASTORAGE_PROPID_CAPTION, _managedInstance->Caption);
    }

    return S_OK;
}

HRESULT WINAPI AimpExtensionDataStorage::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    if (!ppvObject) {
        return E_POINTER;
    }

    if (riid == IID_IAIMPMLDataProvider) {
        *ppvObject = _aimpDataProvider;
        _aimpDataProvider->AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPMLDataProvider2 && _aimpDataProvider2 != nullptr) {
        *ppvObject = _aimpDataProvider2;
        _aimpDataProvider2->AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPMLExtensionDataStorage) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPMLDataStorageCommandAddFilesDialog && _addFilesDialogCommand != nullptr) {
        return _addFilesDialogCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandDeleteFiles && _deleteFilesCommand != nullptr) {
        return _deleteFilesCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandAddFiles && _addFilesCommand != nullptr) {
        return _addFilesCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandDropData && _dropDataCommand != nullptr) {
        return _dropDataCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandReloadTags && _reloadTagsCommand != nullptr) {
        return _reloadTagsCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandUserMark && _userMarkCommand != nullptr) {
        return _userMarkCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandReportDialog && _reportDialogCommand != nullptr) {
        return _reportDialogCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandDeleteFiles2 && _deleteFilesCommand2 != nullptr) {
        return _deleteFilesCommand2->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLDataStorageCommandFindInLibrary && _findInLibraryCommand != nullptr) {
        return _findInLibraryCommand->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLGroupingTreeDataProvider) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPMLAlbumArtProvider && _albumArtProvider != nullptr) {
        return _albumArtProvider->QueryInterface(riid, ppvObject);
    }

    if (riid == IID_IAIMPMLAlbumArtProvider2 && _albumArtProvider2 != nullptr) {
        return _albumArtProvider2->QueryInterface(riid, ppvObject);
    }

    return E_NOINTERFACE;
}

ULONG WINAPI AimpExtensionDataStorage::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI AimpExtensionDataStorage::Release(void) {
    return Base::Release();
}
#pragma endregion
