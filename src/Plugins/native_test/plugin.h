#pragma once
#include <Windows.h>
#include <sstream>
#include <shlobj.h>

#include "IUnknownInterfaceImpl.h"
#include "AIMPSDK/AIMP400/apiMenu.h"
#include "AIMPSDK/AIMP400/apiMusicLibrary.h"
#include "AIMPSDK/AIMP400/apiPlugin.h"

class AimpActionEvent : public IUnknownInterfaceImpl<IAIMPActionEvent> {
    typedef IUnknownInterfaceImpl<IAIMPActionEvent> Base;
    IAIMPCore* _core;

public:
    explicit AimpActionEvent(IAIMPCore* core)
        : _core(core) {
    }

private:
    virtual void WINAPI OnExecute(IUnknown* Data) {
        IAIMPServiceMusicLibraryUI* serv;
        _core->QueryInterface(IID_IAIMPServiceMusicLibraryUI, reinterpret_cast<void**>(&serv));

        IAIMPMLFileList* files = nullptr;
        serv->GetFiles(AIMPML_GETFILES_FLAGS_SELECTED, &files);

        if (files->GetCount() > 0) {
            VARIANT newId;
            VariantInit(&newId);

            //newId.bstrVal = ::SysAllocString(L"12345678");


            newId.vt = 123;
            newId.intVal = 123;
            newId.iVal = 123;
            newId.llVal = 123;

            int index = 0;

            if (files->SetID(index, &newId) == S_OK) {

                VARIANT* id;
                files->GetID(index, &id);
                id->intVal = 1234;
            }
        }
    }
    
    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject) {
        if (riid == IID_IAIMPActionEvent) {
            *ppvObject = this;
            return S_OK;
        }

        *ppvObject = nullptr;
        return E_NOTIMPL;
    }

    virtual ULONG WINAPI AddRef(void) {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void) {
        return Base::Release();
    }   
};

class NativePlugin : public IUnknownInterfaceImpl<IAIMPPlugin> {
public:
    virtual PWCHAR WINAPI InfoGet(int Index) {
        switch (Index) {
        case AIMP_PLUGIN_INFO_NAME: {
            return const_cast<WCHAR*>(L"AIMP native plugin");
        }
        case AIMP_PLUGIN_INFO_AUTHOR: {
            return const_cast<WCHAR*>(L"Evgeniy Bogdan");
        }
        case AIMP_PLUGIN_INFO_SHORT_DESCRIPTION: {
            return const_cast<WCHAR*>(L"AIMP native plugin");
        }
        case AIMP_PLUGIN_INFO_FULL_DESCRIPTION: {
            return const_cast<WCHAR*>(L"AIMP native plugin");
        }
        }

        return NULL;
    }

    virtual DWORD WINAPI InfoGetCategories() {
        return AIMP_PLUGIN_CATEGORY_ADDONS;
    }

    // Initialization / Finalization
    virtual HRESULT WINAPI Initialize(IAIMPCore* Core) {
        // IAIMPImageContainer* container = nullptr;
        // auto res = Core->CreateObject(IID_IAIMPImageContainer, reinterpret_cast<void**>(&container));
        //
        // res = container->SetDataSize(10);
        // auto b = container->GetData();
        //
        // b[0] = 1;
        // b[1] = 2;
        // b[2] = 3;
        //
        // IAIMPImage* img = nullptr;
        // res = container->CreateImage(&img);

        IAIMPServiceMenuManager* serviceMenu = nullptr;
        
        IAIMPMenuItem* menuItem = nullptr;
        IAIMPString* menuId = nullptr;
        IAIMPString* menuTitle = nullptr;

        Core->CreateObject(IID_IAIMPMenuItem, reinterpret_cast<void**>(&menuItem));
        Core->CreateObject(IID_IAIMPString, reinterpret_cast<void**>(&menuId));
        Core->CreateObject(IID_IAIMPString, reinterpret_cast<void**>(&menuTitle));
        
        menuTitle->SetData(const_cast<WCHAR*>(L"Test plugin"), 11);

        menuId->SetData(const_cast<WCHAR*>(L"TESTID"), 6);

        menuItem->SetValueAsObject(AIMP_MENUITEM_PROPID_NAME, menuTitle);
        menuItem->SetValueAsObject(AIMP_MENUITEM_PROPID_ID, menuId);
        
        Core->QueryInterface(IID_IAIMPServiceMenuManager, reinterpret_cast<void**>(&serviceMenu));

        IAIMPMenuItem* parentMenu;
        serviceMenu->GetBuiltIn(AIMP_MENUID_ML_TABLE_CONTEXT_FUNCTIONS, &parentMenu);
        menuItem->SetValueAsObject(AIMP_MENUITEM_PROPID_PARENT, parentMenu);

        IAIMPActionEvent* handler = new AimpActionEvent(Core);
        menuItem->SetValueAsObject(AIMP_MENUITEM_PROPID_EVENT, handler);
        
        Core->RegisterExtension(IID_IAIMPServiceMenuManager, menuItem);
        
        return S_OK;
    }

    virtual HRESULT WINAPI Finalize() {
        return S_OK;
    }

    // System Notifications
    virtual void WINAPI SystemNotification(int NotifyID, IUnknown* Data) {
    }
};
