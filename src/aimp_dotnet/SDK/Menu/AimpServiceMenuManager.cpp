// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpMenuItem.h"
#include "AimpServiceMenuManager.h"

/// <summary>
/// Initializes a new instance of the <see cref="ServiceMenuManager"/> class.
/// </summary>
/// <param name="core">The core.</param>
AimpServiceMenuManager::AimpServiceMenuManager(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceMenuManager>(core)
{
}

ActionResultType AimpServiceMenuManager::CreateMenuItem(IAimpMenuItem^% item)
{
    IAIMPMenuItem* i = nullptr;
    item = nullptr;

    const auto result = CheckResult(_core->CreateMenuItem(&i));
    if (result == ActionResultType::OK && i != nullptr)
    {
        item = gcnew AimpMenuItem(i);
        item->Style = AimpMenuItemStyle::Normal;
    }

    return result;
}

ActionResultType AimpServiceMenuManager::Add(IAimpMenuItem^ item)
{
    auto result = ActionResultType::Unexpected;
    IAIMPServiceMenuManager* service = GetAimpService();
    try
    {
        if (service != nullptr)
        {
            result = CheckResult(_core->GetAimpCore()->RegisterExtension(
                IID_IAIMPServiceMenuManager,
                static_cast<AimpMenuItem^>(item)->InternalAimpObject));
        }
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(static_cast<AimpMenuItem^>(item)->InternalAimpObject);
    }

    return result;
}

/// <summary>
/// Adds the menu item.
/// </summary>
/// <param name="parentMenuType">Type of the parent menu.</param>
/// <param name="item">The item.</param>
ActionResultType AimpServiceMenuManager::Add(ParentMenuType parentMenuType, IAimpMenuItem^ item)
{
    auto result = ActionResultType::Unexpected;
    IAIMPServiceMenuManager* service = GetAimpService();
    try
    {
        if (service != nullptr)
        {
            // gets the parent menu item.
            IAIMPMenuItem* parentMenu;
            service->GetBuiltIn(int(parentMenuType), &parentMenu);

            if (parentMenu == nullptr)
            {
                return result;
            }

            static_cast<AimpMenuItem^>(item)->InternalAimpObject->SetValueAsObject(
                AIMP_MENUITEM_PROPID_PARENT, parentMenu);
            result = CheckResult(_core->GetAimpCore()->RegisterExtension(
                IID_IAIMPServiceMenuManager,
                static_cast<AimpMenuItem^>(item)->InternalAimpObject));
            ReleaseObject(parentMenu);
        }
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(static_cast<AimpMenuItem^>(item)->InternalAimpObject);
    }

    return result;
}

/// <summary>
/// Deletes the menu item.
/// </summary>
/// <param name="item">The item.</param>
ActionResultType AimpServiceMenuManager::Delete(IAimpMenuItem^ item)
{
    return this->Delete(item->Id);
}

/// <summary>
/// Deletes the menu item.
/// </summary>
/// <param name="id">The identifier.</param>
ActionResultType AimpServiceMenuManager::Delete(String^ id)
{
    IAIMPServiceMenuManager* service = GetAimpService();
    IAIMPString* idString = nullptr;
    IAIMPMenuItem* aimpMenuItem = nullptr;
    auto result = ActionResultType::Fail;

    try
    {
        if (service != nullptr)
        {
            if (String::IsNullOrWhiteSpace(id))
            {
                return ActionResultType::Fail;
            }

            idString = AimpConverter::ToAimpString(id);

            result = CheckResult(service->GetByID(idString, &aimpMenuItem));

            if (aimpMenuItem == nullptr)
            {
                return ActionResultType::Fail;
            }

            //if (CheckResult(ManagedAimpCore::GetAimpCore()->UnregisterExtension(aimpMenuItem)) != ActionResultType::OK)
            //{
            //    System::Diagnostics::Debugger::Break();
            //}

            result = CheckResult(UnregisterMenu(aimpMenuItem));
        }
    }
    finally
    {
        ReleaseObject(idString);
        ReleaseObject(service);
        ReleaseObject(aimpMenuItem);
    }

    return result;
}

ActionResultType AimpServiceMenuManager::GetById(String^ id, IAimpMenuItem^% item)
{
    IAIMPServiceMenuManager* service = GetAimpService();
    IAIMPString* menuId = nullptr;
    IAIMPMenuItem* aimpMenuItem = nullptr;
    auto result = ActionResultType::Unexpected;
    item = nullptr;

    try
    {
        if (service != nullptr)
        {
            if (String::IsNullOrWhiteSpace(id))
            {
                return ActionResultType::Fail;
            }

            menuId = AimpConverter::ToAimpString(id);
            result = CheckResult(service->GetByID(menuId, &aimpMenuItem));

            if (result != ActionResultType::OK)
            {
                return result;
            }

            if (aimpMenuItem == nullptr)
            {
                return ActionResultType::Handle;
            }

            AimpMenuItem^ resultItem = gcnew AimpMenuItem(aimpMenuItem);
            item = resultItem;
        }
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(menuId);
        ReleaseObject(aimpMenuItem);
    }

    return result;
}

ActionResultType AimpServiceMenuManager::GetBuiltIn(ParentMenuType parentMenuType, IAimpMenuItem^% item)
{
    IAIMPServiceMenuManager* service = GetAimpService();
    IAIMPMenuItem* aimpMenuItem = nullptr;
    auto result = ActionResultType::Unexpected;
    item = nullptr;

    try
    {
        result = GetService(IID_IAIMPServiceMenuManager, &service);

        if (result != ActionResultType::OK)
        {
            return result;
        }

        result = CheckResult(service->GetBuiltIn(int(parentMenuType), &aimpMenuItem));
        if (result != ActionResultType::OK)
        {
            return result;
        }

        if (aimpMenuItem == nullptr)
        {
            return ActionResultType::Handle;
        }

        AimpMenuItem^ resultItem = gcnew AimpMenuItem(aimpMenuItem);
        item = resultItem;
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(aimpMenuItem);
    }

    return result;
}

/// <summary>
/// Unregisters the menu.
/// </summary>
/// <param name="menuItem">The menu item.</param>
HRESULT AimpServiceMenuManager::UnregisterMenu(IAIMPMenuItem* menuItem)
{
    return _core->UnregisterExtension(menuItem);
}

IAIMPServiceMenuManager* AimpServiceMenuManager::GetAimpService()
{
    IAIMPServiceMenuManager* service = nullptr;
    GetService(IID_IAIMPServiceMenuManager, &service);
    return service;
}
