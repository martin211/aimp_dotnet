#include "..\..\Stdafx.h"
#include "AimpMenuManager.h"
#include "..\Converter.h"

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
            System::Diagnostics::Debug::WriteLine("Dispose AimpMenuManager");
        }

        AimpActionResult AimpMenuManager::CreateMenuItem(IAimpMenuItem ^%item)
        {
            IAIMPMenuItem *i;
            AimpActionResult result = CheckResult(_core->CreateMenuItem(&i));
            if (result == AimpActionResult::Ok)
            {
                item = gcnew AimpMenuItem(i);
                item->Style = AimpMenuItemStyle::Normal;
            }

            return result;
        }

        AimpActionResult AimpMenuManager::Add(IAimpMenuItem ^item)
        {
            AimpActionResult result = AimpActionResult::Unexpected;
            IAIMPServiceMenuManager *service = NULL;
            try
            {
                if (GetService(IID_IAIMPServiceMenuManager, &service) == AimpActionResult::Ok)
                {
                    result = CheckResult(_core->GetAimpCore()->RegisterExtension(IID_IAIMPServiceMenuManager, ((AimpMenuItem^)item)->InternalAimpObject));
                }

                return result;
            }
            finally
            {
                ((AimpMenuItem^)item)->InternalAimpObject->Release();
                service->Release();
                service = NULL;
            }
        }

        /// <summary>
        /// Adds the menu item.
        /// </summary>
        /// <param name="parentMenuType">Type of the parent menu.</param>
        /// <param name="item">The item.</param>
        AimpActionResult AimpMenuManager::Add(ParentMenuType parentMenuType, IAimpMenuItem ^item)
        {
            AimpActionResult result = AimpActionResult::Unexpected;
            IAIMPServiceMenuManager *service = NULL;
            try
            {
                if (GetService(IID_IAIMPServiceMenuManager, &service) == AimpActionResult::Ok)
                {
                    // gets the parent menu item. 
                    IAIMPMenuItem* parentMenu;
                    service->GetBuiltIn((int)parentMenuType, &parentMenu);

                    if (parentMenu == NULL)
                    {
                        return result;
                    }

                    ((AimpMenuItem^)item)->InternalAimpObject->SetValueAsObject(AIMP_MENUITEM_PROPID_PARENT, parentMenu);
                    result = CheckResult(_core->GetAimpCore()->RegisterExtension(IID_IAIMPServiceMenuManager, ((AimpMenuItem^)item)->InternalAimpObject));
                    parentMenu->Release();
                    parentMenu = NULL;
                }

                return result;
            }
            finally
            {
                ((AimpMenuItem^)item)->InternalAimpObject->Release();
                service->Release();
                service = NULL;
            }
        }

        /// <summary>
        /// Deletes the menu item.
        /// </summary>
        /// <param name="item">The item.</param>
        AimpActionResult AimpMenuManager::Delete(IAimpMenuItem ^item)
        {
            delete item;
            return AimpActionResult::Ok;
        }

        /// <summary>
        /// Deletes the menu item.
        /// </summary>
        /// <param name="id">The identifier.</param>
        AimpActionResult AimpMenuManager::Delete(String^ id)
        {
            IAIMPServiceMenuManager *service = NULL;
            IAIMPString* idString = NULL;
            IAIMPMenuItem *aimpMenuItem = NULL;
            try
            {
                if (GetService(IID_IAIMPServiceMenuManager, &service) == AimpActionResult::Ok)
                {
                    if (String::IsNullOrWhiteSpace(id))
                    {
                        return AimpActionResult::Fail;
                    }

                    idString = Converter::MakeAimpString(_core->GetAimpCore(), id);
                    
                    service->GetByID(idString, &aimpMenuItem);

                    if (aimpMenuItem == NULL)
                    {
                        return AimpActionResult::Fail;
                    }

                    //if (CheckResult(ManagedAimpCore::GetAimpCore()->UnregisterExtension(aimpMenuItem)) != AimpActionResult::Ok)
                    //{
                    //    System::Diagnostics::Debugger::Break();
                    //}

                    UnregisterMenu(aimpMenuItem);
                    
                }

                return AimpActionResult::Unexpected;
            }
            finally
            {
                idString->Release();
                service->Release();
                aimpMenuItem->Release();
            }
        }

        AimpActionResult AimpMenuManager::GetById(String^ id, IAimpMenuItem ^%item)
        {
            IAIMPServiceMenuManager *service = NULL;
            IAIMPString* menuId = NULL;
            IAIMPMenuItem *aimpMenuItem = NULL;
            AimpActionResult result = AimpActionResult::Unexpected;
            try
            {
                if (GetService(IID_IAIMPServiceMenuManager, &service) == AimpActionResult::Ok)
                {
                    if (String::IsNullOrWhiteSpace(id))
                    {
                        return AimpActionResult::Fail;
                    }

                    menuId = Converter::MakeAimpString(_core->GetAimpCore(), id);
                    result = CheckResult(service->GetByID(menuId, &aimpMenuItem));
                    
                    if (result != AimpActionResult::Ok)
                    {
                        return result;
                    }

                    if (aimpMenuItem == NULL)
                    {
                        return AimpActionResult::Handle;
                    }

                    AimpMenuItem ^resultItem = gcnew AimpMenuItem(aimpMenuItem);
                    item = resultItem;

                    return AimpActionResult::Fail;
                }
            }
            finally
            {
                service->Release();
                menuId->Release();
                aimpMenuItem->Release();
                menuId = NULL;
                service = NULL;
                aimpMenuItem = NULL;
            }

            return result;
        }

        AimpActionResult AimpMenuManager::GetBuiltIn(ParentMenuType parentMenuType, IAimpMenuItem ^%item)
        {
            IAIMPServiceMenuManager *service = NULL;
            IAIMPMenuItem *aimpMenuItem = NULL;
            AimpActionResult result = AimpActionResult::Unexpected;
            try
            {
                result = GetService(IID_IAIMPServiceMenuManager, &service);

                if (result != AimpActionResult::Ok)
                {
                    return result;
                }

                result = CheckResult(service->GetBuiltIn((int)parentMenuType, &aimpMenuItem));
                if (result != AimpActionResult::Ok)
                {
                    return result;
                }

                if (aimpMenuItem == NULL)
                {
                    return AimpActionResult::Handle;
                }

                AimpMenuItem ^resultItem = gcnew AimpMenuItem(aimpMenuItem);
                item = resultItem;
            }
            finally
            {
                service->Release();
                aimpMenuItem->Release();
                service = NULL;
                aimpMenuItem = NULL;
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