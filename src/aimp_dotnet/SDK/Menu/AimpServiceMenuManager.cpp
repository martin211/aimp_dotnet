// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpMenuItem.h"
#include "AimpServiceMenuManager.h"

/// <summary>
/// Initializes a new instance of the <see cref="ServiceMenuManager"/> class.
/// </summary>
/// <param name="core">The core.</param>
AimpServiceMenuManager::AimpServiceMenuManager(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceMenuManager>(core) {
}

ActionResult AimpServiceMenuManager::Add(IAimpMenuItem^ item) {
    auto result = ActionResultType::Unexpected;
    IAIMPServiceMenuManager* service = GetAimpService();
    try {
        if (service != nullptr) {
            result = CheckResult(_core->GetAimpCore()->RegisterExtension(
                IID_IAIMPServiceMenuManager,
                static_cast<AimpMenuItem^>(item)->InternalAimpObject));
        }
    }
    finally {
        ReleaseObject(service);
        //ReleaseObject(static_cast<AimpMenuItem^>(item)->InternalAimpObject);
    }

    return ACTION_RESULT(result);
}

/// <summary>
/// Adds the menu item.
/// </summary>
/// <param name="parentMenuType">Type of the parent menu.</param>
/// <param name="item">The item.</param>
ActionResult AimpServiceMenuManager::Add(ParentMenuType parentMenuType, IAimpMenuItem^ item) {
    auto result = ActionResultType::Unexpected;
    IAIMPServiceMenuManager* service = GetAimpService();
    try {
        if (service != nullptr) {
            // gets the parent menu item.
            IAIMPMenuItem* parentMenu;
            result = CheckResult(service->GetBuiltIn(int(parentMenuType), &parentMenu));

            if (result == ActionResultType::OK && parentMenu != nullptr) {
                static_cast<AimpMenuItem^>(item)->InternalAimpObject->SetValueAsObject(
                    AIMP_MENUITEM_PROPID_PARENT, parentMenu);

                result = CheckResult(_core->GetAimpCore()->RegisterExtension(
                    IID_IAIMPServiceMenuManager,
                    static_cast<AimpMenuItem^>(item)->InternalAimpObject));

                ReleaseObject(parentMenu);
            }
        }
    }
    finally {
        ReleaseObject(service);
        //ReleaseObject(static_cast<AimpMenuItem^>(item)->InternalAimpObject);
    }

    return ACTION_RESULT(result);
}

/// <summary>
/// Deletes the menu item.
/// </summary>
/// <param name="item">The item.</param>
ActionResult AimpServiceMenuManager::Delete(IAimpMenuItem^ item) {
    const auto result = this->Delete(item->Id);
    return ACTION_RESULT(result->ResultType);
}

/// <summary>
/// Deletes the menu item.
/// </summary>
/// <param name="id">The identifier.</param>
ActionResult AimpServiceMenuManager::Delete(String^ id) {
    IAIMPServiceMenuManager* service = GetAimpService();
    IAIMPString* idString = nullptr;
    IAIMPMenuItem* aimpMenuItem = nullptr;
    auto result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            Assert::NotNull(id, "id");

            idString = AimpConverter::ToAimpString(id);

            result = CheckResult(service->GetByID(idString, &aimpMenuItem));

            if (result == ActionResultType::OK) {
                result = CheckResult(UnregisterMenu(aimpMenuItem));
            }

            //if (CheckResult(ManagedAimpCore::GetAimpCore()->UnregisterExtension(aimpMenuItem)) != ActionResultType::OK)
            //{
            //    System::Diagnostics::Debugger::Break();
            //}
        }
    }
    finally {
        ReleaseObject(idString);
        ReleaseObject(service);
        //ReleaseObject(aimpMenuItem);
    }

    return ACTION_RESULT(result);
}

MenuItemResult AimpServiceMenuManager::GetById(String^ id) {
    IAIMPServiceMenuManager* service = GetAimpService();
    IAIMPString* menuId = nullptr;
    IAIMPMenuItem* aimpMenuItem = nullptr;
    auto result = ActionResultType::Unexpected;
    IAimpMenuItem^ item = nullptr;

    try {
        if (service != nullptr) {
            Assert::NotNull(id, "id");

            menuId = AimpConverter::ToAimpString(id);
            result = CheckResult(service->GetByID(menuId, &aimpMenuItem));

            if (result == ActionResultType::OK && aimpMenuItem != nullptr) {
                item = gcnew AimpMenuItem(aimpMenuItem);
            }
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(menuId);
        //ReleaseObject(aimpMenuItem);
    }

    return gcnew AimpActionResult<IAimpMenuItem^>(result, item);
}

MenuItemResult AimpServiceMenuManager::GetBuiltIn(ParentMenuType parentMenuType) {
    IAIMPServiceMenuManager* service = GetAimpService();
    IAIMPMenuItem* aimpMenuItem = nullptr;
    auto result = ActionResultType::Unexpected;
    IAimpMenuItem^ item = nullptr;

    try {
        result = GetService(IID_IAIMPServiceMenuManager, &service);

        if (result == ActionResultType::OK) {
            result = CheckResult(service->GetBuiltIn(static_cast<int>(parentMenuType), &aimpMenuItem));
            if (result == ActionResultType::OK) {
                item = gcnew AimpMenuItem(aimpMenuItem);
            }
        }
    }
    finally {
        ReleaseObject(service);
        //ReleaseObject(aimpMenuItem);
    }

    return gcnew AimpActionResult<IAimpMenuItem^>(result, item);
}

/// <summary>
/// Unregisters the menu.
/// </summary>
/// <param name="menuItem">The menu item.</param>
HRESULT AimpServiceMenuManager::UnregisterMenu(IAIMPMenuItem* menuItem) {
    return _core->UnregisterExtension(menuItem);
}

IAIMPServiceMenuManager* AimpServiceMenuManager::GetAimpService() {
    IAIMPServiceMenuManager* service = nullptr;
    GetService(IID_IAIMPServiceMenuManager, &service);
    return service;
}
