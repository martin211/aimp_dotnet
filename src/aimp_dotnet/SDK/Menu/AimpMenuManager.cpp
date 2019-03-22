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
#include "AimpMenuManager.h"
#include "AimpMenuItem.h"

namespace AIMP
{
    namespace SDK
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="ServiceMenuManager"/> class.
        /// </summary>
        /// <param name="core">The core.</param>
        AimpMenuManager::AimpMenuManager(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceMenuManager>(core)
        {
        }

        AimpMenuManager::~AimpMenuManager()
        {
            Diagnostics::Debug::WriteLine("Dispose AimpMenuManager");
        }

        AimpActionResult AimpMenuManager::CreateMenuItem(IAimpMenuItem^% item)
        {
            IAIMPMenuItem* i = nullptr;
            item = nullptr;

            const auto result = CheckResult(_core->CreateMenuItem(&i));
            if (result == AimpActionResult::OK && i != nullptr)
            {
                item = gcnew AimpMenuItem(i);
                item->Style = AimpMenuItemStyle::Normal;
            }

            return result;
        }

        AimpActionResult AimpMenuManager::Add(IAimpMenuItem^ item)
        {
            auto result = AimpActionResult::Unexpected;
            IAIMPServiceMenuManager* service = nullptr;
            try
            {
                if (GetService(IID_IAIMPServiceMenuManager, &service) == AimpActionResult::OK && service != nullptr)
                {
                    result = CheckResult(_core->GetAimpCore()->RegisterExtension(
                        IID_IAIMPServiceMenuManager,
                        static_cast<AimpMenuItem^>(item)->InternalAimpObject));
                }
            }
            finally
            {
                static_cast<AimpMenuItem^>(item)->InternalAimpObject->Release();
                service->Release();
                service = nullptr;
            }

            return result;
        }

        /// <summary>
        /// Adds the menu item.
        /// </summary>
        /// <param name="parentMenuType">Type of the parent menu.</param>
        /// <param name="item">The item.</param>
        AimpActionResult AimpMenuManager::Add(ParentMenuType parentMenuType, IAimpMenuItem^ item)
        {
            auto result = AimpActionResult::Unexpected;
            IAIMPServiceMenuManager* service = nullptr;
            try
            {
                if (GetService(IID_IAIMPServiceMenuManager, &service) == AimpActionResult::OK && service != nullptr)
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
                    parentMenu->Release();
                    parentMenu = nullptr;
                }
            }
            finally
            {
                static_cast<AimpMenuItem^>(item)->InternalAimpObject->Release();
                service->Release();
                service = nullptr;
            }

            return result;
        }

        /// <summary>
        /// Deletes the menu item.
        /// </summary>
        /// <param name="item">The item.</param>
        AimpActionResult AimpMenuManager::Delete(IAimpMenuItem^ item)
        {
            return this->Delete(item->Id);
        }

        /// <summary>
        /// Deletes the menu item.
        /// </summary>
        /// <param name="id">The identifier.</param>
        AimpActionResult AimpMenuManager::Delete(String^ id)
        {
            IAIMPServiceMenuManager* service = nullptr;
            IAIMPString* idString = nullptr;
            IAIMPMenuItem* aimpMenuItem = nullptr;
            auto result = AimpActionResult::Fail;

            try
            {
                if (GetService(IID_IAIMPServiceMenuManager, &service) == AimpActionResult::OK && service != nullptr)
                {
                    if (String::IsNullOrWhiteSpace(id))
                    {
                        return AimpActionResult::Fail;
                    }

                    idString = AimpConverter::ToAimpString(id);

                    result = CheckResult(service->GetByID(idString, &aimpMenuItem));

                    if (aimpMenuItem == nullptr)
                    {
                        return AimpActionResult::Fail;
                    }

                    //if (CheckResult(ManagedAimpCore::GetAimpCore()->UnregisterExtension(aimpMenuItem)) != AimpActionResult::OK)
                    //{
                    //    System::Diagnostics::Debugger::Break();
                    //}

                    result = CheckResult(UnregisterMenu(aimpMenuItem));
                }
            }
            finally
            {
                idString->Release();
                service->Release();
                aimpMenuItem->Release();
            }

            return result;
        }

        AimpActionResult AimpMenuManager::GetById(String^ id, IAimpMenuItem^% item)
        {
            IAIMPServiceMenuManager* service = nullptr;
            IAIMPString* menuId = nullptr;
            IAIMPMenuItem* aimpMenuItem = nullptr;
            auto result = AimpActionResult::Unexpected;
            item = nullptr;

            try
            {
                if (GetService(IID_IAIMPServiceMenuManager, &service) == AimpActionResult::OK && service != nullptr)
                {
                    if (String::IsNullOrWhiteSpace(id))
                    {
                        return AimpActionResult::Fail;
                    }

                    menuId = AimpConverter::ToAimpString(id);
                    result = CheckResult(service->GetByID(menuId, &aimpMenuItem));

                    if (result != AimpActionResult::OK)
                    {
                        return result;
                    }

                    if (aimpMenuItem == nullptr)
                    {
                        return AimpActionResult::Handle;
                    }

                    AimpMenuItem^ resultItem = gcnew AimpMenuItem(aimpMenuItem);
                    item = resultItem;
                }
            }
            finally
            {
                service->Release();
                menuId->Release();
                aimpMenuItem->Release();
                menuId = nullptr;
                service = nullptr;
                aimpMenuItem = nullptr;
            }

            return result;
        }

        AimpActionResult AimpMenuManager::GetBuiltIn(ParentMenuType parentMenuType, IAimpMenuItem^% item)
        {
            IAIMPServiceMenuManager* service = nullptr;
            IAIMPMenuItem* aimpMenuItem = nullptr;
            auto result = AimpActionResult::Unexpected;
            item = nullptr;

            try
            {
                result = GetService(IID_IAIMPServiceMenuManager, &service);

                if (result != AimpActionResult::OK)
                {
                    return result;
                }

                result = CheckResult(service->GetBuiltIn(int(parentMenuType), &aimpMenuItem));
                if (result != AimpActionResult::OK)
                {
                    return result;
                }

                if (aimpMenuItem == nullptr)
                {
                    return AimpActionResult::Handle;
                }

                AimpMenuItem^ resultItem = gcnew AimpMenuItem(aimpMenuItem);
                item = resultItem;
            }
            finally
            {
                service->Release();
                aimpMenuItem->Release();
                service = nullptr;
                aimpMenuItem = nullptr;
            }

            return result;
        }

        /// <summary>
        /// Unregisters the menu.
        /// </summary>
        /// <param name="menuItem">The menu item.</param>
        HRESULT AimpMenuManager::UnregisterMenu(IAIMPMenuItem* menuItem)
        {
            return _core->UnregisterExtension(menuItem);
        }
    }
}
