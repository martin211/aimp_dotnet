#pragma once
#include "AimpDataStorageManager.h"
#include "AimpGroupingPresets.h"

class AimpExtensionDataStorage :
    public IAIMPMLExtensionDataStorage
{
public:
    AimpExtensionDataStorage(IAIMPCore *aimpCore, gcroot<AIMP::SDK::MusicLibrary::Extension::IAimpExtensionDataStorage^> instance)
    {
        _managedInstance = instance;
        _aimpCore = aimpCore;
    }

    virtual void WINAPI Finalize()
    {
        _managedInstance->Dispose();
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
        return (HRESULT)_managedInstance->ConfigLoad(nullptr, AIMP::SDK::AimpExtension::GetString(Section));
    }

    virtual HRESULT WINAPI GetFields(int Schema, IAIMPObjectList** List)
    {
        System::Collections::IList ^collection;
        _managedInstance->GetFields((AIMP::SDK::MusicLibrary::Extension::SchemaType)Schema, collection);

        IAIMPObjectList *L = AIMP::SDK::AimpExtension::MakeObject<IAIMPObjectList>(IID_IAIMPObjectList);

        System::Type^ t = collection->GetType()->GetGenericArguments()[0];
        if (t == AIMP::SDK::MusicLibrary::DataStorage::IAimpDataField::typeid)
        {
            for (int i = 0; i < collection->Count; i++)
            {
                AIMP::SDK::MusicLibrary::DataStorage::IAimpDataField ^dataField = (AIMP::SDK::MusicLibrary::DataStorage::IAimpDataField^)collection[i];
                IAIMPMLDataField *df = AIMP::SDK::AimpExtension::MakeObject<IAIMPMLDataField>(IID_IAIMPMLDataField);

                AIMP::SDK::PropertyListExtension::SetInt32(df, AIMPML_FIELD_PROPID_TYPE, (int)dataField->Type);
                AIMP::SDK::PropertyListExtension::SetString(df, AIMPML_FIELD_PROPID_NAME, dataField->Name);
                AIMP::SDK::PropertyListExtension::SetInt32(df, AIMPML_FIELD_PROPID_FLAGS, (int)dataField->Flags);

                L->Add(df);
            }
        }
        else if (t == System::String::typeid)
        {
            for (int i = 0; i < collection->Count; i++)
            {
                System::String^ str = (System::String^)collection[i];
                L->Add(AIMP::SDK::AimpExtension::GetAimpString(str));
            }
        }

        *List = L;

        return S_OK;
    }

    virtual HRESULT WINAPI GetGroupingPresets(int Schema, IAIMPMLGroupingPresets* Presets)
    {
        AIMP::SDK::AimpGroupingPresets ^managedPresets = gcnew AIMP::SDK::AimpGroupingPresets(Presets);
        return (HRESULT)_managedInstance->GetGroupingPresets((AIMP::SDK::MusicLibrary::Extension::GroupingPresetsSchemaType)Schema, managedPresets);
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

    }

    // Read
    virtual HRESULT WINAPI GetValueAsFloat(int PropertyID, double *Value)
    {
        return S_OK;
    }

    virtual HRESULT WINAPI GetValueAsInt32(int PropertyID, int *Value)
    {
        return S_OK;
    }

    virtual HRESULT WINAPI GetValueAsInt64(int PropertyID, INT64 *Value)
    {
        return S_OK;
    }

    virtual HRESULT WINAPI GetValueAsObject(int PropertyID, REFIID IID, void **Value)
    {
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
        if (PropertyID == AIMPML_DATASTORAGE_PROPID_ID)
        {
            Value = AIMP::SDK::AimpExtension::GetAimpString(_managedInstance->Id);
            return S_OK;
        }

        if (PropertyID == AIMPML_DATASTORAGE_PROPID_CAPTION)
        {
            Value = AIMP::SDK::AimpExtension::GetAimpString(_managedInstance->Caption);
            return S_OK;
        }
    }

private:
    gcroot<AIMP::SDK::MusicLibrary::Extension::IAimpExtensionDataStorage^> _managedInstance;
    IAIMPCore *_aimpCore;
};
