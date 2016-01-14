#include "..\..\Stdafx.h"
#include "AimpMenuManager.h"
#include "..\Converter.h"

namespace AIMP
{
    namespace SDK
    {
        /// <summary>
        /// Somes the callback proxy.
        /// </summary>
        /// <param name="This">The this.</param>
        void SomeCallbackProxy(gcroot<MenuItem^> This)
        {
            This->OnClick();
        }

        void BeforeShowCallback(gcroot<MenuItem^> This)
        {
            This->OnBeforeShow();
        }

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

        /// <summary>
        /// Adds the menu item.
        /// </summary>
        /// <param name="parentMenuType">Type of the parent menu.</param>
        /// <param name="items">The items.</param>
        void AimpMenuManager::AddRange(ParentMenuType parentMenuType, MenuItemCollection^ items)
        {
            IAIMPServiceMenuManager *service = NULL;

            try
            {
                if (GetService(IID_IAIMPServiceMenuManager, &service) == AimpActionResult::Ok)
                {
                    // gets the parent menu item. 
                    IAIMPMenuItem* parentMenu;
                    service->GetBuiltIn((int)parentMenuType, &parentMenu);

                    if (parentMenu == nullptr || items->Count == 0)
                    {
                        return;
                    }

                    for each(MenuItem^ item in items)
                    {
                        RegisterMenu(parentMenu, item);
                    }
                }
            }
            finally
            {
                service = NULL;
            }
        }

        /// <summary>
        /// Adds the menu item.
        /// </summary>
        /// <param name="parentMenuType">Type of the parent menu.</param>
        /// <param name="item">The item.</param>
        void AimpMenuManager::Add(ParentMenuType parentMenuType, MenuItem^ item)
        {
            IAIMPServiceMenuManager *service = NULL;
            try
            {
                if (GetService(IID_IAIMPServiceMenuManager, &service) == AimpActionResult::Ok)
                {
                    // gets the parent menu item. 
                    IAIMPMenuItem* parentMenu;
                    service->GetBuiltIn((int)parentMenuType, &parentMenu);

                    if (parentMenu == nullptr)
                    {
                        return;
                    }

                    RegisterMenu(parentMenu, item);
                    parentMenu->Release();
                }
            }
            finally
            {
                service->Release();
            }
        }

        /// <summary>
        /// Deletes the menu item.
        /// </summary>
        /// <param name="item">The item.</param>
        void AimpMenuManager::Delete(MenuItem^ item)
        {
            if (String::IsNullOrWhiteSpace(item->Id))
            {
                return;
            }

            Delete(item->Id);
        }

        /// <summary>
        /// Deletes the menu item.
        /// </summary>
        /// <param name="id">The identifier.</param>
        void AimpMenuManager::Delete(String^ id)
        {
            IAIMPServiceMenuManager *service = NULL;
            try
            {
                if (GetService(IID_IAIMPServiceMenuManager, &service) == AimpActionResult::Ok)
                {
                    if (String::IsNullOrWhiteSpace(id))
                    {
                        return;
                    }

                    IAIMPString* idString = Converter::MakeAimpString(_core->GetAimpCore(), id);
                    IAIMPMenuItem *aimpMenuItem;
                    service->GetByID(idString, &aimpMenuItem);
                    
                    idString->Release();

                    if (aimpMenuItem == NULL)
                    {
                        return;
                    }

                    if (CheckResult(ManagedAimpCore::GetAimpCore()->UnregisterExtension(aimpMenuItem)) != AimpActionResult::Ok)
                    {
                        System::Diagnostics::Debugger::Break();
                    }

                    UnregisterMenu(aimpMenuItem);
                    aimpMenuItem->Release();
                }
            }
            finally
            {
                service->Release();
            }
        }

        /// <summary>
        /// Deletes the specified items.
        /// </summary>
        /// <param name="items">The items.</param>
        void AimpMenuManager::Delete(MenuItemCollection^ items)
        {
            if (items != nullptr)
            {
                for each (MenuItem^ item in items)
                {
                    Delete(item);
                }
            }
        }

        MenuItem^ AimpMenuManager::GetById(String^ id)
        {
            IAIMPServiceMenuManager *service = NULL;
            try
            {
                if (GetService(IID_IAIMPServiceMenuManager, &service) == AimpActionResult::Ok)
                {
                    if (String::IsNullOrWhiteSpace(id))
                    {
                        return nullptr;
                    }

                    IAIMPString* menuId = Converter::MakeAimpString(_core->GetAimpCore(), id);
                    IAIMPMenuItem *aimpMenuItem;
                    service->GetByID(menuId, &aimpMenuItem);

                    if (aimpMenuItem == NULL)
                    {
                        return nullptr;
                    }

                    MenuItem^ result;

                    int menuType;
                    aimpMenuItem->GetValueAsInt32(AIMP_MENUITEM_PROPID_STYLE, &menuType);

                    int checked;
                    aimpMenuItem->GetValueAsInt32(AIMP_MENUITEM_PROPID_CHECKED, &checked);

                    IAIMPString* idString;
                    IAIMPString* nameString;
                    aimpMenuItem->GetValueAsObject(AIMP_MENUITEM_PROPID_ID, IID_IAIMPString, (void**)&idString);
                    aimpMenuItem->GetValueAsObject(AIMP_MENUITEM_PROPID_NAME, IID_IAIMPString, (void**)&nameString);

                    if (menuType == AIMP_MENUITEM_STYLE_CHECKBOX)
                    {
                        result = gcnew CheckBoxMenuItem(gcnew String(nameString->GetData()));
                        ((CheckBoxMenuItem^)result)->Checked = checked > 0;
                    }
                    else if (menuType == AIMP_MENUITEM_STYLE_RADIOBOX)
                    {
                        result = gcnew RadioButtonMenuItem(gcnew String(nameString->GetData()));
                        ((RadioButtonMenuItem^)result)->Checked = checked > 0;
                    }
                    else if (menuType == AIMP_MENUITEM_STYLE_NORMAL)
                    {
                        result = gcnew StandartMenuItem(gcnew String(nameString->GetData()));
                    }

                    result->Id = gcnew String(idString->GetData());
                    int visible;

                    aimpMenuItem->GetValueAsInt32(AIMP_MENUITEM_PROPID_VISIBLE, &visible);

                    result->Visible = visible > 0;

                    idString->Release();
                    nameString->Release();
                    
                    return result;
                }
            }
            finally
            {
                service->Release();
            }
        }

        MenuItem ^AimpMenuManager::GetBuiltIn(ParentMenuType parentMenuType)
        {
            IAIMPServiceMenuManager *service = NULL;
            try
            {
                if (GetService(IID_IAIMPServiceMenuManager, &service) == AimpActionResult::Ok)
                {
                    IAIMPMenuItem *aimpMenuItem = nullptr;
                    if (CheckResult(service->GetBuiltIn((int)parentMenuType, &aimpMenuItem)) == AimpActionResult::Ok)
                    {
                        return Converter::ConvertToMenu(aimpMenuItem);
                    }

                    return nullptr;
                }
            }
            finally
            {
                service->Release();
            }
        }

        /*** Private */
        /// <summary>
        /// Registers the menu.
        /// </summary>
        /// <param name="parentMenuItem">The parent menu item.</param>
        /// <param name="menuItem">The menu item.</param>
        void AimpMenuManager::RegisterMenu(IAIMPMenuItem* parentMenuItem, MenuItem^ menuItem)
        {
            IAIMPMenuItem *newItem = Converter::CreateMenuItem(_core->GetAimpCore());

            if (newItem == NULL)
            {
                return;
            }

            menuItem->PropertyChanged += gcnew System::ComponentModel::PropertyChangedEventHandler(this, &AIMP::AimpMenuManager::OnPropertyChanged);

            IAIMPString* idString = Converter::MakeAimpString(_core->GetAimpCore(), menuItem->Id);

            newItem->SetValueAsObject(AIMP_MENUITEM_PROPID_ID, idString);
            newItem->SetValueAsObject(AIMP_MENUITEM_PROPID_PARENT, parentMenuItem);


            // setup property for checkbox menu item.
            if (menuItem->GetType() == CheckBoxMenuItem::typeid)
            {
                newItem->SetValueAsInt32(AIMP_MENUITEM_PROPID_STYLE, AIMP_MENUITEM_STYLE_CHECKBOX);
            }
            else if (menuItem->GetType() == RadioButtonMenuItem::typeid)
            {
                newItem->SetValueAsInt32(AIMP_MENUITEM_PROPID_STYLE, AIMP_MENUITEM_STYLE_RADIOBOX);
            }
            else
            {
                newItem->SetValueAsInt32(AIMP_MENUITEM_PROPID_STYLE, AIMP_MENUITEM_STYLE_NORMAL);
            }

            MenuItemEvent* itemEvent = new MenuItemEvent();
            if (newItem->SetValueAsObject(AIMP_MENUITEM_PROPID_EVENT, itemEvent) == S_OK)
            {
                EventCallback *callback = new EventCallback;
                *callback = itemEvent->RegisterCallback(boost::bind(SomeCallbackProxy, gcroot<MenuItem^>(menuItem)));

                menuItem->AimpMenuItemHeader = IntPtr::IntPtr(newItem);// System::Runtime::InteropServices::Marshal::GetIUnknownForObject(newItem);

                // register on subitems evnts.
                menuItem->ChildItems->ItemAdded += gcnew AIMP::SDK::UI::MenuItem::ItemAddedHandler(this, &AIMP::SDK::AimpMenuManager::OnSubitemAdded);
            }

            MenuItemEvent* beforeShowEvent = new MenuItemEvent();
            if (newItem->SetValueAsObject(AIMP_MENUITEM_PROPID_EVENT_ONSHOW, beforeShowEvent) == S_OK)
            {
                EventCallback *callbackBeforeShow = new EventCallback;
                *callbackBeforeShow = beforeShowEvent->RegisterCallback(boost::bind(BeforeShowCallback, gcroot<MenuItem^>(menuItem)));
            }

            FillMenuData(newItem, menuItem);
            newItem->Release();
            idString->Release();

            // TODO: FIX IT!
            //_core->RegisterExtension(IID_IAIMPServiceMenuManager, newItem);

            if (menuItem->ChildItems != nullptr && menuItem->ChildItems->Count > 0)
            {
                for each(MenuItem^ item in menuItem->ChildItems)
                {
                    RegisterMenu(newItem, item);
                }
            }
        }

        /// <summary>
        /// Fills the menu data.
        /// </summary>
        /// <param name="aimpMenuItem">The aimp menu item.</param>
        /// <param name="menuItem">The menu item.</param>
        void AimpMenuManager::FillMenuData(IAIMPMenuItem* aimpMenuItem, MenuItem^ menuItem)
        {
            IAIMPString *sName = Converter::MakeAimpString(_core->GetAimpCore(), menuItem->Text);

            aimpMenuItem->SetValueAsObject(AIMP_MENUITEM_PROPID_NAME, sName);
            aimpMenuItem->SetValueAsInt32(AIMP_MENUITEM_PROPID_VISIBLE, menuItem->Visible ? 1 : 0);
            aimpMenuItem->SetValueAsInt32(AIMP_MENUITEM_PROPID_ENABLED, menuItem->Enabled ? 1 : 0);

            sName->Release();

            if (menuItem->GetType() == CheckBoxMenuItem::typeid)
            {
                aimpMenuItem->SetValueAsInt32(AIMP_MENUITEM_PROPID_CHECKED, ((CheckedMenuItem^)menuItem)->Checked ? 1 : 0);
            }
            else if (menuItem->GetType() == RadioButtonMenuItem::typeid)
            {
                aimpMenuItem->SetValueAsInt32(AIMP_MENUITEM_PROPID_CHECKED, ((CheckedMenuItem^)menuItem)->Checked ? 1 : 0);
            }

            if (menuItem->ActionItem != nullptr)
            {
                aimpMenuItem->SetValueAsObject(AIMP_MENUITEM_PROPID_ACTION, Converter::CreateActionItem(_core->GetAimpCore(), (AIMP::SDK::UI::ActionItem::AimpActionItem^)menuItem->ActionItem));
            }

            if (menuItem->Image != nullptr)
            {
                IAIMPImage *image = Converter::CreateImage(menuItem->Image);
                aimpMenuItem->SetValueAsObject(AIMP_MENUITEM_PROPID_GLYPH, image);
                image->Release();
            }
        }

        /// <summary>
        /// Updates the menu item.
        /// </summary>
        /// <param name="menuItem">The menu item.</param>
        void AimpMenuManager::UpdateMenuItem(MenuItem^ menuItem)
        {
            if (String::IsNullOrWhiteSpace(menuItem->Id))
            {
                return;
            }

            IAIMPServiceMenuManager *service = NULL;
            try
            {
                if (GetService(IID_IAIMPServiceMenuManager, &service) == AimpActionResult::Ok)
                {
                    IAIMPString* id = Converter::MakeAimpString(_core->GetAimpCore(), menuItem->Id);
                    IAIMPMenuItem *aimpMenuItem;
                    service->GetByID(id, &aimpMenuItem);

                    id->Release();

                    if (aimpMenuItem == NULL)
                    {
                        return;
                    }

                    FillMenuData(aimpMenuItem, menuItem);
                    aimpMenuItem->Release();
                    
                }
            }
            finally
            {
                service->Release();
            }
        }

        /// <summary>
        /// Unregisters the menu.
        /// </summary>
        /// <param name="menuItem">The menu item.</param>
        void AimpMenuManager::UnregisterMenu(IAIMPMenuItem* menuItem)
        {
            _core->UnregisterExtension(menuItem);
        }

        /// <summary>
        /// Called when [property changed].
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="e">The e.</param>
        void AimpMenuManager::OnPropertyChanged(System::Object ^sender, System::ComponentModel::PropertyChangedEventArgs ^e)
        {
            UpdateMenuItem((MenuItem^)sender);
        }


        void AimpMenuManager::OnSubitemAdded(MenuItem ^parent, MenuItem ^item)
        {
            RegisterMenu((IAIMPMenuItem*)parent->AimpMenuItemHeader.ToPointer(), item);
        }

        void AimpMenuManager::OnSubItemDeleted(System::Object ^item)
        {
            UpdateMenuItem((MenuItem^)item);
        }
    }
}