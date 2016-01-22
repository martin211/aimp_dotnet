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

                    //result = CheckResult(_core->GetAimpCore()->UnregisterExtension(((AimpMenuItem^)item)->InternalAimpObject));

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
            ((AimpMenuItem^)item)->InternalAimpObject->Release();
            AimpActionResult result = CheckResult(UnregisterMenu(((AimpMenuItem^)item)->InternalAimpObject));
            if (result != AimpActionResult::Ok)
            {
                return result;
            }


            delete item;

            return result;
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
            try
            {
                //if (GetService(IID_IAIMPServiceMenuManager, &service) == AimpActionResult::Ok)
                //{
                //    if (String::IsNullOrWhiteSpace(id))
                //    {
                //        return AimpActionResult::Fail;
                //    }

                //    IAIMPString* menuId = Converter::MakeAimpString(_core->GetAimpCore(), id);
                //    IAIMPMenuItem *aimpMenuItem;
                //    service->GetByID(menuId, &aimpMenuItem);

                //    if (aimpMenuItem == NULL)
                //    {
                //        return AimpActionResult::Fail;
                //    }

                //    MenuItem^ result;

                //    int menuType;
                //    aimpMenuItem->GetValueAsInt32(AIMP_MENUITEM_PROPID_STYLE, &menuType);

                //    int checked;
                //    aimpMenuItem->GetValueAsInt32(AIMP_MENUITEM_PROPID_CHECKED, &checked);

                //    IAIMPString* idString;
                //    IAIMPString* nameString;
                //    aimpMenuItem->GetValueAsObject(AIMP_MENUITEM_PROPID_ID, IID_IAIMPString, (void**)&idString);
                //    aimpMenuItem->GetValueAsObject(AIMP_MENUITEM_PROPID_NAME, IID_IAIMPString, (void**)&nameString);

                //    if (menuType == AIMP_MENUITEM_STYLE_CHECKBOX)
                //    {
                //        //result = gcnew CheckBoxMenuItem(gcnew String(nameString->GetData()));
                //        //((CheckBoxMenuItem^)result)->Checked = checked > 0;
                //    }
                //    else if (menuType == AIMP_MENUITEM_STYLE_RADIOBOX)
                //    {
                //        result = gcnew RadioButtonMenuItem(gcnew String(nameString->GetData()));
                //        ((RadioButtonMenuItem^)result)->Checked = checked > 0;
                //    }
                //    else if (menuType == AIMP_MENUITEM_STYLE_NORMAL)
                //    {
                //        result = gcnew StandartMenuItem(gcnew String(nameString->GetData()));
                //    }

                //    result->Id = gcnew String(idString->GetData());
                //    int visible;

                //    aimpMenuItem->GetValueAsInt32(AIMP_MENUITEM_PROPID_VISIBLE, &visible);

                //    result->Visible = visible > 0;

                //    idString->Release();
                //    nameString->Release();
                    
                    return AimpActionResult::Fail;
                //}
            }
            finally
            {
                service->Release();
            }
        }

        AimpActionResult AimpMenuManager::GetBuiltIn(ParentMenuType parentMenuType, IAimpMenuItem ^%item)
        {
            IAIMPServiceMenuManager *service = NULL;
            try
            {
                if (GetService(IID_IAIMPServiceMenuManager, &service) == AimpActionResult::Ok)
                {
                    IAIMPMenuItem *aimpMenuItem = nullptr;
                    if (CheckResult(service->GetBuiltIn((int)parentMenuType, &aimpMenuItem)) == AimpActionResult::Ok)
                    {
                        return AimpActionResult::Fail;//Converter::ConvertToMenu(aimpMenuItem);
                    }

                    return AimpActionResult::Fail;
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
        //void AimpMenuManager::RegisterMenu(IAIMPMenuItem* parentMenuItem, MenuItem^ menuItem)
        //{
        //    IAIMPMenuItem *newItem = Converter::CreateMenuItem(_core->GetAimpCore());

        //    if (newItem == NULL)
        //    {
        //        return;
        //    }

        //    menuItem->PropertyChanged += gcnew System::ComponentModel::PropertyChangedEventHandler(this, &AIMP::AimpMenuManager::OnPropertyChanged);
        //    IAIMPString* idString = Converter::MakeAimpString(_core->GetAimpCore(), menuItem->Id);
        //    newItem->SetValueAsObject(AIMP_MENUITEM_PROPID_ID, idString);
        //    newItem->SetValueAsObject(AIMP_MENUITEM_PROPID_PARENT, parentMenuItem);


        //    // setup property for checkbox menu item.
        //    if (menuItem->GetType() == CheckBoxMenuItem::typeid)
        //    {
        //        newItem->SetValueAsInt32(AIMP_MENUITEM_PROPID_STYLE, AIMP_MENUITEM_STYLE_CHECKBOX);
        //    }
        //    else if (menuItem->GetType() == RadioButtonMenuItem::typeid)
        //    {
        //        newItem->SetValueAsInt32(AIMP_MENUITEM_PROPID_STYLE, AIMP_MENUITEM_STYLE_RADIOBOX);
        //    }
        //    else
        //    {
        //        newItem->SetValueAsInt32(AIMP_MENUITEM_PROPID_STYLE, AIMP_MENUITEM_STYLE_NORMAL);
        //    }

        //    MenuItemEvent* itemEvent = new MenuItemEvent();
        //    if (newItem->SetValueAsObject(AIMP_MENUITEM_PROPID_EVENT, itemEvent) == S_OK)
        //    {
        //        EventCallback *callback = new EventCallback;
        //        *callback = itemEvent->RegisterCallback(boost::bind(SomeCallbackProxy, gcroot<MenuItem^>(menuItem)));
        //        menuItem->AimpMenuItemHeader = IntPtr::IntPtr(newItem);
        //        // register on subitems evnts.
        //        menuItem->ChildItems->ItemAdded += gcnew AIMP::SDK::UI::MenuItem::ItemAddedHandler(this, &AIMP::SDK::AimpMenuManager::OnSubitemAdded);
        //    }

        //    MenuItemEvent* beforeShowEvent = new MenuItemEvent();
        //    if (newItem->SetValueAsObject(AIMP_MENUITEM_PROPID_EVENT_ONSHOW, beforeShowEvent) == S_OK)
        //    {
        //        EventCallback *callbackBeforeShow = new EventCallback;
        //        *callbackBeforeShow = beforeShowEvent->RegisterCallback(boost::bind(BeforeShowCallback, gcroot<MenuItem^>(menuItem)));
        //    }

        //    FillMenuData(newItem, menuItem);
        //    newItem->Release();
        //    idString->Release();

        //    // TODO: FIX IT!
        //    //_core->RegisterExtension(IID_IAIMPServiceMenuManager, newItem);

        //    if (menuItem->ChildItems != nullptr && menuItem->ChildItems->Count > 0)
        //    {
        //        for each(MenuItem^ item in menuItem->ChildItems)
        //        {
        //            RegisterMenu(newItem, item);
        //        }
        //    }
        //}

        /// <summary>
        /// Fills the menu data.
        /// </summary>
        /// <param name="aimpMenuItem">The aimp menu item.</param>
        /// <param name="menuItem">The menu item.</param>
        //void AimpMenuManager::FillMenuData(IAIMPMenuItem* aimpMenuItem, MenuItem^ menuItem)
        //{
        //    IAIMPString *sName = Converter::MakeAimpString(_core->GetAimpCore(), menuItem->Text);

        //    aimpMenuItem->SetValueAsObject(AIMP_MENUITEM_PROPID_NAME, sName);
        //    aimpMenuItem->SetValueAsInt32(AIMP_MENUITEM_PROPID_VISIBLE, menuItem->Visible ? 1 : 0);
        //    aimpMenuItem->SetValueAsInt32(AIMP_MENUITEM_PROPID_ENABLED, menuItem->Enabled ? 1 : 0);

        //    sName->Release();

        //    if (menuItem->GetType() == CheckBoxMenuItem::typeid)
        //    {
        //        aimpMenuItem->SetValueAsInt32(AIMP_MENUITEM_PROPID_CHECKED, ((CheckedMenuItem^)menuItem)->Checked ? 1 : 0);
        //    }
        //    else if (menuItem->GetType() == RadioButtonMenuItem::typeid)
        //    {
        //        aimpMenuItem->SetValueAsInt32(AIMP_MENUITEM_PROPID_CHECKED, ((CheckedMenuItem^)menuItem)->Checked ? 1 : 0);
        //    }

        //    if (menuItem->ActionItem != nullptr)
        //    {
        //        aimpMenuItem->SetValueAsObject(AIMP_MENUITEM_PROPID_ACTION, Converter::CreateActionItem(_core->GetAimpCore(), (AIMP::SDK::UI::ActionItem::AimpActionItem^)menuItem->ActionItem));
        //    }

        //    if (menuItem->Image != nullptr)
        //    {
        //        IAIMPImage *image = Converter::CreateImage(menuItem->Image);
        //        aimpMenuItem->SetValueAsObject(AIMP_MENUITEM_PROPID_GLYPH, image);
        //        image->Release();
        //    }
        //}

        /// <summary>
        /// Updates the menu item.
        /// </summary>
        /// <param name="menuItem">The menu item.</param>
        //void AimpMenuManager::UpdateMenuItem(MenuItem^ menuItem)
        //{
        //    if (String::IsNullOrWhiteSpace(menuItem->Id))
        //    {
        //        return;
        //    }

        //    IAIMPServiceMenuManager *service = NULL;
        //    try
        //    {
        //        if (GetService(IID_IAIMPServiceMenuManager, &service) == AimpActionResult::Ok)
        //        {
        //            IAIMPString* id = Converter::MakeAimpString(_core->GetAimpCore(), menuItem->Id);
        //            IAIMPMenuItem *aimpMenuItem;
        //            service->GetByID(id, &aimpMenuItem);

        //            id->Release();

        //            if (aimpMenuItem == NULL)
        //            {
        //                return;
        //            }

        //            //FillMenuData(aimpMenuItem, menuItem);
        //            aimpMenuItem->Release();
        //            
        //        }
        //    }
        //    finally
        //    {
        //        service->Release();
        //    }
        //}

        /// <summary>
        /// Unregisters the menu.
        /// </summary>
        /// <param name="menuItem">The menu item.</param>
        HRESULT AimpMenuManager::UnregisterMenu(IAIMPMenuItem* menuItem)
        {
            return _core->UnregisterExtension(menuItem);
        }

        /// <summary>
        /// Called when [property changed].
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="e">The e.</param>
        //void AimpMenuManager::OnPropertyChanged(System::Object ^sender, System::ComponentModel::PropertyChangedEventArgs ^e)
        //{
        //    UpdateMenuItem((MenuItem^)sender);
        //}


        //void AimpMenuManager::OnSubitemAdded(MenuItem ^parent, MenuItem ^item)
        //{
        //    //RegisterMenu((IAIMPMenuItem*)parent->AimpMenuItemHeader.ToPointer(), item);
        //}

        //void AimpMenuManager::OnSubItemDeleted(System::Object ^item)
        //{
        //    UpdateMenuItem((MenuItem^)item);
        //}
    }
}