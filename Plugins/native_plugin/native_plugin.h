#pragma once
#include <Windows.h>
#include <iostream>
#include <sstream>

#include "AIMP400/apiPlugin.h"
#include "AIMP400/apiThreading.h"
#include "AIMP400/apiMusicLibrary.h"

#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

template <typename T>
class IUnknownInterfaceImpl : public T
{
public:

    IUnknownInterfaceImpl()
    {
        _LinkCounter = 1;
    }

    virtual ~IUnknownInterfaceImpl() {}

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (riid == IID_IUnknown)
        {
            return S_OK;
        }
        return E_NOTIMPL;
    }

    virtual ULONG WINAPI AddRef(void)
    {
        _LinkCounter++;
        return _LinkCounter;
    }

    virtual ULONG WINAPI Release(void) {
        _LinkCounter--;

        if (_LinkCounter == 0) {
            delete this;
            return 0;
        }

        return _LinkCounter;
    }

private:
    ULONG _LinkCounter;
};

class AimpTask : public IUnknownInterfaceImpl<IAIMPTask>
{
public:
    typedef IUnknownInterfaceImpl<IAIMPTask> Base;

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (!ppvObject)
        {
            return E_POINTER;
        }

        if (riid == IID_IAIMPTask) {
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

    virtual void WINAPI Execute(IAIMPTaskOwner* Owner)
    {
        DBOUT("Tasl execute");
    }
};

class TDemoExplorerViewDataStorage :
    public IUnknown,
    //public IAIMPPropertyList,
    public IUnknownInterfaceImpl<IAIMPMLExtensionDataStorage>,
    public IAIMPMLDataProvider
{
private:
    ULONG _LinkCounter;
    IAIMPCore* core;

    IAIMPMLDataField* CreateField(std::wstring name, int type, int flags)
    {
        IAIMPMLDataField* df;
        IAIMPString* str;

        core->CreateObject(IID_IAIMPString, (void**)&str);
        str->SetData((WCHAR*)name.c_str(), name.length());

        core->CreateObject(IID_IAIMPMLDataField, (void**)&df);
        df->SetValueAsInt32(AIMPML_FIELD_PROPID_TYPE, type);
        df->SetValueAsObject(AIMPML_FIELD_PROPID_NAME, str);
        df->SetValueAsInt32(AIMPML_FIELD_PROPID_FLAGS, AIMPML_FIELDFLAG_FILTERING | flags);

        return df;
    }

    IAIMPString* MakeString(WCHAR* value)
    {
        IAIMPString* str;
        core->CreateObject(IID_IAIMPString, (void**)&str);
        str->SetData(value, sizeof(value));
        return str;
    }

    WCHAR* EVDS_ID = L"ID";
    WCHAR* EVDS_FileName = L"FileName";
    WCHAR* EVDS_FileFormat = L"FileFormat";
    WCHAR* EVDS_FileAccessTime = L"FileAccessTime";
    WCHAR* EVDS_FileCreationTime = L"FileCreationTime";
    WCHAR* EVDS_FileSize = L"FileSize";
    WCHAR* EVDS_Fake = L"Fake";

public:
    typedef IUnknownInterfaceImpl<IAIMPMLExtensionDataStorage> Base;

    TDemoExplorerViewDataStorage(IAIMPCore* Core)
    {
        core = Core;
    };

    // IAIMPMLDataProvider
    virtual HRESULT WINAPI GetData(IAIMPObjectList* Fields, IAIMPMLDataFilter* Filter, IUnknown** Data)
    {
        return S_OK;
    }

    // IAIMPMLExtensionDataStorage
    virtual void WINAPI Finalize()
    {
        
    };

    virtual void WINAPI Initialize(IAIMPMLDataStorageManager* Manager)
    {
        
    };

    // Config
    virtual HRESULT WINAPI ConfigLoad(IAIMPConfig *Config, IAIMPString* Section)
    {
        return S_OK;
    };

    virtual HRESULT WINAPI ConfigSave(IAIMPConfig *Config, IAIMPString* Section)
    {
        return S_OK;
    };

    // Schemas
    virtual HRESULT WINAPI GetFields(int Schema, IAIMPObjectList** List)
    {
        IAIMPObjectList* list;
        core->CreateObject(IID_IAIMPObjectList, reinterpret_cast<void**>(&list));

        if (Schema == AIMPML_FIELDS_SCHEMA_ALL)
        {
            list->Add(CreateField(EVDS_ID, AIMPML_FIELDTYPE_STRING, AIMPML_FIELDFLAG_INTERNAL));
            list->Add(CreateField(EVDS_FileName, 0, 0));
            list->Add(CreateField(EVDS_FileFormat, AIMPML_FIELDTYPE_STRING, 0));
            list->Add(CreateField(EVDS_FileSize, AIMPML_FIELDTYPE_FILESIZE, 0));
            list->Add(CreateField(EVDS_FileAccessTime, AIMPML_FIELDTYPE_DATETIME, 0));
            list->Add(CreateField(EVDS_FileCreationTime, AIMPML_FIELDTYPE_DATETIME, 0));
            list->Add(CreateField(EVDS_Fake, AIMPML_FIELDTYPE_FILENAME, AIMPML_FIELDFLAG_INTERNAL | AIMPML_FIELDFLAG_GROUPING));

            *List = list;
            return S_OK;
        }

        if (Schema == AIMPML_FIELDS_SCHEMA_TABLE_VIEW_DEFAULT
            || Schema == AIMPML_FIELDS_SCHEMA_TABLE_VIEW_ALBUMTHUMBNAILS
            || Schema == AIMPML_FIELDS_SCHEMA_TABLE_VIEW_GROUPDETAILS)
        {
            list->Add(MakeString(EVDS_FileFormat));
            list->Add(MakeString(EVDS_FileName));
            list->Add(MakeString(EVDS_FileSize));
            list->Add(MakeString(EVDS_FileAccessTime));
            list->Add(MakeString(EVDS_FileCreationTime));
            *List = list;
            return S_OK;
        }

        return S_OK;
    };

    virtual HRESULT WINAPI GetGroupingPresets(int Schema, IAIMPMLGroupingPresets* Presets)
    {
        IAIMPMLGroupingPresetStandard* preset = NULL;
        IAIMPObjectList* list = nullptr;

        if (Schema == AIMPML_GROUPINGPRESETS_SCHEMA_BUILTIN)
        {
            Presets->Add3(MakeString(L"Demo.ExplorerView.GroupingPreset.Default"), MakeString(L"Demo"), 0, MakeString(EVDS_Fake), &preset);
            //preset->GetValueAsObject(AIMPML_GROUPINGPRESETSTD_PROPID_FIELDS, IID_IAIMPObjectList, reinterpret_cast<void**>(&list));

            //int count = list->GetCount();
            //DBOUT("QueryInterface result " << count);
            return S_OK;
        }

        
        if (Schema == AIMPML_GROUPINGPRESETS_SCHEMA_DEFAULT)
        {
            Presets->Add3(MakeString(L"Demo.ExplorerView.GroupingPreset.Default"), MakeString(L"Demo"), 0, MakeString(EVDS_Fake), &preset);
            return S_OK;
        }
    };

    // Build-in Commands
    virtual void WINAPI FlushCache(int Reserved /*= 0*/)
    {
        
    };

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (riid == IID_IUnknown)
        {
            return S_OK;
        }

        if (riid == IID_IAIMPMLDataProvider)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        if (riid == IID_IAIMPMLExtensionDataStorage)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        return E_NOTIMPL;
    }

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }

    virtual void WINAPI BeginUpdate(){};
    virtual void WINAPI EndUpdate(){};
    virtual HRESULT WINAPI Reset() { return S_OK; };
    // Read
    virtual HRESULT WINAPI GetValueAsFloat(int PropertyID, double *Value) { return S_OK; };
    virtual HRESULT WINAPI GetValueAsInt32(int PropertyID, int *Value)
    {
        if (PropertyID == AIMPML_DATASTORAGE_PROPID_CAPABILITIES)
        {
            *Value = 0;
        }
        return S_OK;
    };
    virtual HRESULT WINAPI GetValueAsInt64(int PropertyID, INT64 *Value) { return S_OK; };
    virtual HRESULT WINAPI GetValueAsObject(int PropertyID, REFIID IID, void **Value)
    {
        if (PropertyID == AIMPML_DATASTORAGE_PROPID_ID)
        {
            *Value = MakeString(L"DemoExplorerViewID");
        }

        if (PropertyID == AIMPML_DATASTORAGE_PROPID_CAPTION)
        {
            *Value = MakeString(L"ExplorerViewCaption");
        }

        return S_OK;
    };

    // Write
    virtual HRESULT WINAPI SetValueAsFloat(int PropertyID, const double Value) { return S_OK; };
    virtual HRESULT WINAPI SetValueAsInt32(int PropertyID, int Value) { return S_OK; };
    virtual HRESULT WINAPI SetValueAsInt64(int PropertyID, const INT64 Value) { return S_OK; };
    virtual HRESULT WINAPI SetValueAsObject(int PropertyID, IUnknown *Value) { return S_OK; };
};

class NativePlugin : public IUnknownInterfaceImpl<IAIMPPlugin>
{
public:
    virtual PWCHAR WINAPI InfoGet(int Index)
    {
        switch (Index)
        {
        case AIMP_PLUGIN_INFO_NAME:
        {
            return L"AIMP native plugin";
        }
        case AIMP_PLUGIN_INFO_AUTHOR:
        {
            return L"Evgeniy Bogdan";
        }
        case AIMP_PLUGIN_INFO_SHORT_DESCRIPTION:
        {
            return L"AIMP native plugin";
        }
        case AIMP_PLUGIN_INFO_FULL_DESCRIPTION:
        {
            return L"AIMP native plugin";
        }
        }

        return NULL;
    }

    virtual DWORD WINAPI InfoGetCategories()
    {
        return AIMP_PLUGIN_CATEGORY_ADDONS;
    }

    // Initialization / Finalization
    virtual HRESULT WINAPI Initialize(IAIMPCore* Core)
    {
        //IAIMPServiceThreadPool *service;

        //HRESULT res = Core->QueryInterface(IID_IAIMPServiceThreadPool, (void**)&service);
        //DBOUT("QueryInterface result " << res);

        //AimpTask* task = new AimpTask();

        //DWORD_PTR h;

        ////res = service->Execute(task, &h);
        //DBOUT("Execute result " << res);

        //IAIMPServiceMusicLibrary *mlservice;
        //HRESULT res = Core->QueryInterface(IID_IAIMPServiceMusicLibrary, (void**)&mlservice);
        //DBOUT("QueryInterface result " << res);

        ////IAIMPMLDataStorage *storage;
        ////res = mlservice->GetActiveStorage(IID_IAIMPMLDataStorage, (void**)&storage);
        ////DBOUT("Execute result " << res);

        //IAIMPMLGroupingPresets* presets = NULL;
        //res = mlservice->GetStorage(0, IID_IAIMPMLGroupingPresets, (void**)presets);
        //DBOUT("Execute GetActiveStorage for presets " << res);

        //IAIMPMLGroupingPresetStandard* std;

        //res = presets->Get(0, IID_IAIMPMLGroupingPresetStandard, (void**)&std);
        //DBOUT("Execute Get for IAIMPMLGroupingPresetStandard " << res);

        TDemoExplorerViewDataStorage* demo = new TDemoExplorerViewDataStorage(Core);

        Core->RegisterExtension(IID_IAIMPServiceMusicLibrary, (IAIMPMLExtensionDataStorage*)demo);

        return S_OK;
    }

    virtual HRESULT WINAPI Finalize()
    {
        return S_OK;
    }

    // System Notifications
    virtual void WINAPI SystemNotification(int NotifyID, IUnknown* Data)
    {
        
    }
};