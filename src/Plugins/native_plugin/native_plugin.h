#pragma once
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <shlobj.h>
#include <gcroot.h>
#include <vcclr.h>

#include "AIMP400/apiPlugin.h"
#include "AIMP400/apiThreading.h"
#include "TDemoExplorerViewDataStorage.h"
#include "IUnknownInterfaceImpl.h"
#include "TMyMusicFileSystem.h"


#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

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

class AimpActionEvent : public IUnknownInterfaceImpl<IAIMPActionEvent>
{
public:
    typedef IUnknownInterfaceImpl<IAIMPActionEvent> Base;
    IAIMPCore* _core;

    AimpActionEvent(IAIMPCore* core)
    {
        _core = core;
    }

    virtual void WINAPI OnExecute(IUnknown *Data)
    {
        System::Diagnostics::Debugger::Launch();

        System::String^ folder = System::Environment::GetFolderPath(System::Environment::SpecialFolder::MyMusic);
        gcroot<array<System::String^>^> arr = System::IO::Directory::GetFiles(folder, "*.mp3");
        IAIMPObjectList* list;
        _core->CreateObject(IID_IAIMPObjectList, (void**)&list);

        for (int i = 0; i < arr->Length; i++)
        {
            IAIMPString* str = nullptr;
            _core->CreateObject(IID_IAIMPString, (void**)&str);
            System::String^ value = arr[i];
            pin_ptr<const WCHAR> strDate = PtrToStringChars(L"mymusic:\\\\" + value);
            str->SetData((PWCHAR)strDate, value->Length);
            list->Add(str);
        }

        IAIMPServicePlaylistManager2* service;
        _core->QueryInterface(IID_IAIMPServicePlaylistManager2, (void**)&service);
        IAIMPPlaylist* playlist;
        service->GetActivePlaylist(&playlist);
        playlist->AddList(list, 1, -1);
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (riid == IID_IAIMPActionEvent)
        {
            *ppvObject = this;
            return S_OK;
        }

        ppvObject = NULL;
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

        //IUnknown* demo = new AimpExtensionDataStorage(Core);
        //Core->RegisterExtension(IID_IAIMPServiceMusicLibrary, demo);

        RegisterMenu(Core);

        IUnknown* fs = (IAIMPExtensionFileSystem*)new TMyMusicFileSystem();

        HRESULT res = Core->RegisterExtension(IID_IAIMPExtensionFileSystem, fs);
        DBOUT("RegisterExtension result " << res);

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

    void RegisterMenu(IAIMPCore* core)
    {
        IAIMPMenuItem* item = nullptr;
        IAIMPMenuItem* parentItem = nullptr;
        IAIMPServiceMenuManager *service = nullptr;

        core->CreateObject(IID_IAIMPMenuItem, (void**)&item);
        if (item != nullptr)
        {
            IAIMPString* id = nullptr;
            IAIMPString* name = nullptr;

            core->CreateObject(IID_IAIMPString, (void**)&id);
            core->CreateObject(IID_IAIMPString, (void**)&name);

            id->SetData(L"AIMP_DEMO_MENU", 15);
            item->SetValueAsObject(AIMP_MENUITEM_PROPID_ID, id);

            name->SetData(L"MyMusic: Add All Files", 23);
            item->SetValueAsObject(AIMP_MENUITEM_PROPID_NAME, name);

            core->QueryInterface(IID_IAIMPServiceMenuManager, (void**)&service);
            service->GetBuiltIn(20, &parentItem);

            item->SetValueAsObject(AIMP_MENUITEM_PROPID_PARENT, parentItem);

            IAIMPActionEvent* action = new AimpActionEvent(core);
            core->CreateObject(IID_IAIMPActionEvent, (void**)&action);

            item->SetValueAsObject(AIMP_MENUITEM_PROPID_EVENT, action);

            core->RegisterExtension(IID_IAIMPServiceMenuManager, item);
        }
    }
};