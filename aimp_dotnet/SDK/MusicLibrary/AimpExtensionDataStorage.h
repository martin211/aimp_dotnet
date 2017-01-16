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

    AimpDataProvider(gcroot<AIMP::SDK::MusicLibrary::Extension::IAimpExtensionDataStorage^> instance)
    {
        _instance = instance;
    }

    virtual HRESULT WINAPI GetData(IAIMPObjectList* Fields, IAIMPMLDataFilter* Filter, IUnknown** Data)
    {
        System::Diagnostics::Debug::WriteLine("Get data");
        System::Object^ obj = _instance;

        IAimpDataProvider^ provider = dynamic_cast<IAimpDataProvider^>(obj);
        if (provider != nullptr)
        {
            System::Object^ o;
            AimpActionResult result = provider->GetData(
                AIMP::SDK::AimpExtension::ToStringCollection(Fields),
                gcnew AimpDataFilter(Filter),
                o);

            if (result == AimpActionResult::Ok)
            {
                IAimpDataProviderSelection^ selection = dynamic_cast<IAimpDataProviderSelection^>(o);

                if (selection != nullptr)
                {
                    *Data = new InternalAimpDataProviderSelection((IAimpDataProviderSelection^)o);
                }
                else
                {
                    *Data = AIMP::SDK::AimpExtension::GetAimpString(o->ToString());
                }
            }
        }

        return S_OK;
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

class AimpDataStorageCommandAddFiles : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandAddFiles>
{
private:
    gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandAddFiles^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandAddFiles> Base;

    AimpDataStorageCommandAddFiles(gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandAddFiles^> instance)
    {
        _instance = instance;
    }

    virtual HRESULT WINAPI Add(IAIMPObjectList* Files)
    {
        return (HRESULT)_instance->Add(nullptr);
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        *ppvObject = NULL;
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
    gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandAddFilesDialog^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandAddFilesDialog> Base;

    AimpDataStorageCommandAddFilesDialog(gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandAddFilesDialog^> instance)
    {
        _instance = instance;
    }

    virtual HRESULT WINAPI Execute(HWND OwnerHandle)
    {
        System::IntPtr ownerHandle(OwnerHandle);
        return (HRESULT)_instance->Execute(ownerHandle);
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
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

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }
};

class AimpDataStorageCommandDeleteFiles : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandDeleteFiles>
{
private:
    gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandDeleteFiles^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandDeleteFiles> Base;

    AimpDataStorageCommandDeleteFiles(gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandDeleteFiles^> instance)
    {
        _instance = instance;
    }

    virtual BOOL WINAPI CanDelete(BOOL Physically)
    {
        return _instance->CanDelete(Physically);
    }

    virtual HRESULT WINAPI Delete(IAIMPMLFileList* Files, BOOL Physically)
    {
        return (HRESULT)_instance->Delete(gcnew AimpFileList(Files), Physically);
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
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

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }
};

class AimpDataStorageCommandDropData : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandDropData>
{
private:
    gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandDropData^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandDropData> Base;

    AimpDataStorageCommandDropData(gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandDropData^> instance)
    {
        _instance = instance;
    }

    virtual HRESULT WINAPI DropData()
    {
        return (HRESULT)_instance->DropData();
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
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

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }
};

class AimpDataStorageCommandReloadTags : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandReloadTags>
{
private:
    gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandReloadTags^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandReloadTags> Base;

    AimpDataStorageCommandReloadTags(gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandReloadTags^> instance)
    {
        _instance = instance;
    }

    virtual HRESULT WINAPI ReloadTags(IAIMPMLFileList* Files)
    {
        return (HRESULT)_instance->ReloadTags(gcnew AimpFileList(Files));
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
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

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }
};

class AimpDataStorageCommandReportDialog : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandReportDialog>
{
private:
    gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandReportDialog^> _instance;

public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandReportDialog> Base;

    AimpDataStorageCommandReportDialog(gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandReportDialog^> instance)
    {
        _instance = instance;
    }

    virtual HRESULT WINAPI Execute(HWND OwnerHandle)
    {
        System::IntPtr ownerHandle(OwnerHandle);
        return (HRESULT)_instance->Execute(ownerHandle);
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
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

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }
};

class AimpDataStorageCommandUserMark : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandUserMark>
{
private:
    gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandUserMark^> _instance;

public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandUserMark> Base;

    AimpDataStorageCommandUserMark(gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandUserMark^> instance)
    {
        _instance = instance;
    }

    virtual HRESULT WINAPI SetMark(VARIANT* ID, const DOUBLE Value)
    {
        return (HRESULT)_instance->SetMark(AIMP::SDK::AimpExtension::FromVaiant(ID), Value);
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
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

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }
};

class AimpExtensionDataStorage :
    public IUnknownInterfaceImpl<IAIMPMLExtensionDataStorage>
{
private:
    AimpDataProvider* _aimpDataProvider;
    AimpDataStorageCommandAddFiles* _addFilesCommand = NULL;
    AimpDataStorageCommandAddFilesDialog* _addFilesDialogCommand = NULL;
    AimpDataStorageCommandDeleteFiles* _deleteFilesCommand = NULL;
    AimpDataStorageCommandDropData* _dropDataCommand = NULL;
    AimpDataStorageCommandReloadTags* _reloadTagsCommand = NULL;
    AimpDataStorageCommandReportDialog* _reportDialogCommand = NULL;
    AimpDataStorageCommandUserMark* _userMarkCommand = NULL;
    gcroot<AIMP::SDK::AimpGroupingPresets^> _managedPresets;

public:
    typedef IUnknownInterfaceImpl<IAIMPMLExtensionDataStorage> Base;

    AimpExtensionDataStorage(IAIMPCore *aimpCore, gcroot<AIMP::SDK::MusicLibrary::Extension::IAimpExtensionDataStorage^> instance)
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

    virtual void WINAPI Finalize()
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

    virtual void WINAPI Initialize(IAIMPMLDataStorageManager* Manager)
    {
        IAimpDataStorageManager ^manager = gcnew AimpDataStorageManager(Manager);
        _managedInstance->Initialize(manager);
    }

    virtual HRESULT WINAPI ConfigLoad(IAIMPConfig *Config, IAIMPString* Section)
    {
        return (HRESULT)_managedInstance->ConfigLoad(nullptr, AIMP::SDK::AimpExtension::GetString(Section));
    }

    virtual HRESULT WINAPI ConfigSave(IAIMPConfig *Config, IAIMPString* Section)
    {
        return (HRESULT)_managedInstance->ConfigSave(nullptr, AIMP::SDK::AimpExtension::GetString(Section));
    }

    virtual HRESULT WINAPI GetFields(int Schema, IAIMPObjectList** List)
    {
        IAIMPObjectList *L = AIMP::SDK::AimpExtension::GetAimpObjectList();

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
                IAIMPMLDataField *df = AIMP::SDK::AimpExtension::GetAimpDataField();

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
                IAIMPString *s = AIMP::SDK::AimpExtension::GetAimpString(str);
                L->Add(s);
                s->Release();
            }
        }

        *List = L;

        return S_OK;
    }

    virtual HRESULT WINAPI GetGroupingPresets(int Schema, IAIMPMLGroupingPresets* Presets)
    {
        _managedPresets = gcnew AIMP::SDK::AimpGroupingPresets(Presets);
        return (HRESULT)_managedInstance->GetGroupingPresets((AIMP::SDK::MusicLibrary::Extension::GroupingPresetsSchemaType)Schema, _managedPresets);
    }

    virtual void WINAPI FlushCache(int Reserved)
    {
        _managedInstance->FlushCache();
    }

    virtual void WINAPI BeginUpdate()
    {
    }

    virtual void WINAPI EndUpdate()
    {

    }

    virtual HRESULT WINAPI Reset()
    {
        return S_OK;
    }

    // Read
    virtual HRESULT WINAPI GetValueAsFloat(int PropertyID, double *Value)
    {
        return S_OK;
    }

    virtual HRESULT WINAPI GetValueAsInt32(int PropertyID, int *Value)
    {
        if (PropertyID == AIMPML_DATASTORAGE_PROPID_CAPABILITIES)
        {
            *Value = (int)_managedInstance->Capabilities;
        }

        return S_OK;
    }

    virtual HRESULT WINAPI GetValueAsInt64(int PropertyID, INT64 *Value)
    {
        return S_OK;
    }

    virtual HRESULT WINAPI GetValueAsObject(int PropertyID, REFIID IID, void **Value)
    {
        if (PropertyID == AIMPML_DATASTORAGE_PROPID_ID)
        {
            *Value = AIMP::SDK::AimpExtension::GetAimpString(_managedInstance->Id);
        }

        if (PropertyID == AIMPML_DATASTORAGE_PROPID_CAPTION)
        {
            *Value = AIMP::SDK::AimpExtension::GetAimpString(_managedInstance->Caption);
        }

        return S_OK;
    }
    // Write
    virtual HRESULT WINAPI SetValueAsFloat(int PropertyID, const double Value)
    {
        return S_OK;
    }

    virtual HRESULT WINAPI SetValueAsInt32(int PropertyID, int Value)
    {
        return S_OK;
    }

    virtual HRESULT WINAPI SetValueAsInt64(int PropertyID, const INT64 Value)
    {
        return S_OK;
    }

    virtual HRESULT WINAPI SetValueAsObject(int PropertyID, IUnknown *Value)
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

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
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

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }

private:
    gcroot<AIMP::SDK::MusicLibrary::Extension::IAimpExtensionDataStorage^> _managedInstance;
    IAIMPCore *_aimpCore;
};
