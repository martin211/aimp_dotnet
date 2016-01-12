#pragma once

#include "..\..\Stdafx.h"
#include "AimpActionManager.h"
#include "..\Converter.h"

namespace AIMP
{
    namespace SDK
    {
        AimpActionManager::AimpActionManager(ManagedAimpCore^ core) : AimpBaseManager(core)
        {
            IAIMPServiceActionManager *manager;
            ManagedAimpCore::GetAimpCore()->QueryInterface(IID_IAIMPServiceActionManager, (void**)&manager);
            _manager = manager;
        }

        AimpActionManager::~AimpActionManager()
        {
            System::Diagnostics::Debug::WriteLine("Dispose AimpActionManager");
            _manager->Release();
        }

        void AimpActionManager::Add(AimpActionItem^ action)
        {
            RegisterAction(action);
        }

        void AimpActionManager::AddRange(ActionItemCollection^ actions)
        {
            for each(AimpActionItem^ item in actions)
            {
                RegisterAction(item);
            }
        }

        void AimpActionManager::RegisterAction(AimpActionItem ^menuItem)
        {
            //IAIMPAction* newAction = AimpObjectExtension::CreateActionItem(ManagedAimpCore::GetAimpCore());
            //IAIMPString* idString = AimpObjectExtension::MakeAimpString(_core->GetAimpCore(), menuItem->Id);
            //IAIMPString* nameString = AimpObjectExtension::MakeAimpString(_core->GetAimpCore(), menuItem->Text);
            //
            //bool checkResult = false;

            //checkResult = CheckResult(newAction->SetValueAsObject(AIMP_ACTION_PROPID_ID, idString));
            //checkResult &= CheckResult(newAction->SetValueAsObject(AIMP_ACTION_PROPID_NAME, nameString));

            //if (!System::String::IsNullOrEmpty(menuItem->GroupName))
            //{
            //	checkResult &= CheckResult(newAction->SetValueAsObject(AIMP_ACTION_PROPID_GROUPNAME, AimpObjectExtension::MakeAimpString(_core->GetAimpCore(), menuItem->GroupName)));
            //}

            ////checkResult &= CheckResult(newAction->SetValueAsInt32(AIMP_ACTION_PROPID_ENABLED, menuItem->Enabled ? 1 : 0));

            //_core->GetAimpCore()->RegisterExtension(AIMP36SDK::IID_IAIMPServiceMenuManager, newAction);

            IAIMPAction* newAction;
            IAIMPString* actionIdString = Converter::MakeAimpString(_core->GetAimpCore(), menuItem->Id);
            IAIMPString* actionNameString = Converter::MakeAimpString(_core->GetAimpCore(), menuItem->Text);
            IAIMPString* actionGroupString = Converter::MakeAimpString(_core->GetAimpCore(), menuItem->GroupName);

            _core->GetAimpCore()->CreateObject(IID_IAIMPAction, (void**)&newAction);

            CheckResult(newAction->SetValueAsObject(AIMP_ACTION_PROPID_ID, actionIdString));
            CheckResult(newAction->SetValueAsObject(AIMP_ACTION_PROPID_NAME, actionNameString));
            CheckResult(newAction->SetValueAsObject(AIMP_ACTION_PROPID_GROUPNAME, actionGroupString));
            CheckResult(_core->GetAimpCore()->RegisterExtension(IID_IAIMPServiceMenuManager, newAction));

            actionIdString->Release();
            actionNameString->Release();
            actionGroupString->Release();
            newAction->Release();
        }

        void AimpActionManager::UpdateItem(AimpActionItem^ menuItem)
        {
            // todo: complete it.
            throw gcnew System::NotImplementedException("Not implemented");
        }

        void AimpActionManager::OnPropertyChanged(System::Object ^sender, System::ComponentModel::PropertyChangedEventArgs ^e)
        {
            UpdateItem((AimpActionItem^)sender);
        }
    }
}