#include "IUnknownInterfaceImpl.h"
#include "AimpSDK.h"


class AimpExtensionDataStorage :
    //public IUnknown,
    public IUnknownInterfaceImpl<IAIMPMLExtensionDataStorage>
    //public IAIMPMLDataProvider
    //public IAIMPMLDataStorageCommandAddFiles,
    //public IAIMPMLDataStorageCommandAddFilesDialog,
    //public IAIMPMLDataStorageCommandDeleteFiles,
    //public IAIMPMLDataStorageCommandDropData,
    //public IAIMPMLDataStorageCommandReloadTags,
    //public IAIMPMLDataStorageCommandReportDialog,
    //public IAIMPMLDataStorageCommandUserMark
{
private:
    bool _implementsAddFilesCommand = false;
    bool _implementsAddFilesDialogCommand = false;
    bool _implementsDeleteFilesCommand = false;
    bool _implementsDropDataCommand = true;
    bool _implementsReloadTagsCommand = false;
    bool _implementsReportDialogCommand = false;
    bool _implementsUserMarkCommand = false;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLExtensionDataStorage> Base;

    AimpExtensionDataStorage(IAIMPCore *aimpCore)
    {
        _aimpCore = aimpCore;
    }

    virtual void WINAPI Finalize()
    {
    }

    virtual void WINAPI Initialize(IAIMPMLDataStorageManager* Manager)
    {
    }

    virtual HRESULT WINAPI ConfigLoad(IAIMPConfig *Config, IAIMPString* Section)
    {
        return S_OK;
    }

    virtual HRESULT WINAPI ConfigSave(IAIMPConfig *Config, IAIMPString* Section)
    {
        return S_OK;
    }

    virtual HRESULT WINAPI GetFields(int Schema, IAIMPObjectList** List)
    {
        //System::Collections::IList ^collection;
        //_managedInstance->GetFields((AIMP::SDK::MusicLibrary::Extension::SchemaType)Schema, collection);

        //IAIMPObjectList *L = AIMP::SDK::AimpExtension::MakeObject<IAIMPObjectList>(IID_IAIMPObjectList);

        //System::Type^ t = collection->GetType()->GetGenericArguments()[0];
        //if (t == AIMP::SDK::MusicLibrary::DataStorage::IAimpDataField::typeid)
        //{
        //    for (int i = 0; i < collection->Count; i++)
        //    {
        //        AIMP::SDK::MusicLibrary::DataStorage::IAimpDataField ^dataField = (AIMP::SDK::MusicLibrary::DataStorage::IAimpDataField^)collection[i];
        //        IAIMPMLDataField *df = AIMP::SDK::AimpExtension::MakeObject<IAIMPMLDataField>(IID_IAIMPMLDataField);

        //        AIMP::SDK::PropertyListExtension::SetInt32(df, AIMPML_FIELD_PROPID_TYPE, (int)dataField->Type);
        //        AIMP::SDK::PropertyListExtension::SetString(df, AIMPML_FIELD_PROPID_NAME, dataField->Name);
        //        AIMP::SDK::PropertyListExtension::SetInt32(df, AIMPML_FIELD_PROPID_FLAGS, (int)dataField->Flags);

        //        L->Add(df);
        //    }
        //}
        //else if (t == System::String::typeid)
        //{
        //    for (int i = 0; i < collection->Count; i++)
        //    {
        //        System::String^ str = (System::String^)collection[i];
        //        L->Add(AIMP::SDK::AimpExtension::GetAimpString(str));
        //    }
        //}

        //*List = L;

        return S_OK;
    }

    IAIMPString* MakeString(WCHAR* value)
    {
        IAIMPString* str;
        _aimpCore->CreateObject(IID_IAIMPString, (void**)&str);
        str->SetData(value, sizeof(value));
        return str;
    }

    virtual HRESULT WINAPI GetGroupingPresets(int Schema, IAIMPMLGroupingPresets* Presets)
    {
        //AIMP::SDK::AimpGroupingPresets ^managedPresets = gcnew AIMP::SDK::AimpGroupingPresets(Presets);
        //return (HRESULT)_managedInstance->GetGroupingPresets((AIMP::SDK::MusicLibrary::Extension::GroupingPresetsSchemaType)Schema, managedPresets);
        IAIMPMLGroupingPresetStandard* preset = NULL;
        IAIMPObjectList* list = nullptr;
        if (Schema == AIMPML_GROUPINGPRESETS_SCHEMA_BUILTIN)
        {
            //Presets->Add3(MakeString(L"Demo.ExplorerView.GroupingPreset.Default"), MakeString(L"Demo"), 0, MakeString(L"Fake"), &preset);
            //preset->GetValueAsObject(AIMPML_GROUPINGPRESETSTD_PROPID_FIELDS, IID_IAIMPObjectList, reinterpret_cast<void**>(&list));
            //int count = list->GetCount();
        }

        return S_OK;
    }

    virtual HRESULT WINAPI GetData(IAIMPObjectList* Fields, IAIMPMLDataFilter* Filter, IUnknown** Data)
    {
        return S_OK;
    }

    virtual void WINAPI FlushCache(int Reserved /*= 0*/)
    {}

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
        //if (PropertyID == AIMPML_DATASTORAGE_PROPID_CAPABILITIES)
        //{
        //    *Value = (int)0;
        //}

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
           // *Value = MakeString(L"ID");
        }

        if (PropertyID == AIMPML_DATASTORAGE_PROPID_CAPTION)
        {
            //*Value = MakeString(L"Caption");
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
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (!ppvObject)
        {
            return E_POINTER;
        }

        //if (riid == IID_IAIMPMLDataProvider)
        //{
        //    *ppvObject = this;
        //    AddRef();
        //    return S_OK;
        //}

        if (riid == IID_IAIMPMLExtensionDataStorage)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        //if (riid == IID_IAIMPMLExtensionDataStorage
        //    || (riid == IID_IAIMPMLDataStorageCommandAddFiles && _implementsAddFilesCommand)
        //    || (riid == IID_IAIMPMLDataStorageCommandAddFilesDialog && _implementsAddFilesDialogCommand)
        //    || (riid == IID_IAIMPMLDataStorageCommandDeleteFiles && _implementsDeleteFilesCommand)
        //    || (riid == IID_IAIMPMLDataStorageCommandDropData && _implementsDropDataCommand)
        //    || (riid == IID_IAIMPMLDataStorageCommandReloadTags && _implementsReloadTagsCommand)
        //    || (riid == IID_IAIMPMLDataStorageCommandReportDialog && _implementsReportDialogCommand)
        //    || (riid == IID_IAIMPMLDataStorageCommandUserMark && _implementsUserMarkCommand))
        //{
        //    *ppvObject = this;
        //    AddRef();
        //    return S_OK;
        //}

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

    virtual HRESULT WINAPI Add(IAIMPObjectList* Files)
    {
        return S_OK;
    }

    virtual HRESULT WINAPI Execute(HWND OwnerHandle)
    {
        return S_OK;
    }

    virtual BOOL WINAPI CanDelete(BOOL Physically)
    {
        return S_OK;
    }

    virtual HRESULT WINAPI Delete(IAIMPMLFileList* Files, BOOL Physically)
    {
        return S_OK;
    }

    virtual HRESULT WINAPI DropData()
    {
        return S_OK;
    }

    virtual HRESULT WINAPI ReloadTags(IAIMPMLFileList* Files)
    {
        return S_OK;
    }

    virtual HRESULT WINAPI SetMark(const VARIANT ID, const DOUBLE Value)
    {
        return S_OK;
    }

private:
    IAIMPCore *_aimpCore;
};