#pragma once
#include <Windows.h>
#include <sstream>
#include <shlobj.h>

#include "IUnknownInterfaceImpl.h"
#include "AIMPSDK/AIMP400/apiPlugin.h"


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
        IAIMPImageContainer* container = nullptr;
        auto res = Core->CreateObject(IID_IAIMPImageContainer, reinterpret_cast<void**>(&container));

        res = container->SetDataSize(10);
        auto b = container->GetData();

        b[0] = 1;
        b[1] = 2;
        b[2] = 3;

        IAIMPImage* img = nullptr;
        res = container->CreateImage(&img);

        return S_OK;
    }

    virtual HRESULT WINAPI Finalize() {
        return S_OK;
    }

    // System Notifications
    virtual void WINAPI SystemNotification(int NotifyID, IUnknown* Data) {
    }
};
