#pragma once

#include "Stdafx.h"
#include "ActionManager.h"
#include "..\..\DataConversion.h"


namespace AIMP
{
	namespace SDK
	{



		ActionManager::ActionManager(ManagedAimpCore^ core) : AimpBaseManager(core)
		{
			AIMP36SDK::IAIMPServiceActionManager *manager;
			ManagedAimpCore::GetAimpCore()->QueryInterface(AIMP36SDK::IID_IAIMPServiceActionManager, (void**) &manager);
			_manager = manager;
		}

		void ActionManager::Add(AimpActionItem^ action)
		{
			RegisterAction(action);
		}

		void ActionManager::AddRange(ActionItemCollection^ actions)
		{
			for each(AimpActionItem^ item in actions)
			{
				RegisterAction(item);
			}
		}

		void ActionManager::RegisterAction(AimpActionItem ^menuItem)
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

			AIMP36SDK::IAIMPAction* newAction;
			AIMP36SDK::IAIMPString* actionIdString = ObjectHelper::MakeAimpString(_core->GetAimpCore(), menuItem->Id);
			AIMP36SDK::IAIMPString* actionNameString = ObjectHelper::MakeAimpString(_core->GetAimpCore(), menuItem->Text);
			AIMP36SDK::IAIMPString* actionGroupString = ObjectHelper::MakeAimpString(_core->GetAimpCore(), menuItem->GroupName);

			_core->GetAimpCore()->CreateObject(AIMP36SDK::IID_IAIMPAction, (void**) &newAction);

			newAction->SetValueAsObject(AIMP36SDK::AIMP_ACTION_PROPID_ID, actionIdString);
			newAction->SetValueAsObject(AIMP36SDK::AIMP_ACTION_PROPID_NAME, actionNameString);
			newAction->SetValueAsObject(AIMP36SDK::AIMP_ACTION_PROPID_GROUPNAME, actionGroupString);


			_core->GetAimpCore()->RegisterExtension(AIMP36SDK::IID_IAIMPServiceMenuManager, newAction);


		}

		void ActionManager::UpdateItem(AimpActionItem^ menuItem)
		{
			// todo: complete it.
			throw gcnew System::NotImplementedException("Not implemented");
		}

		void ActionManager::OnPropertyChanged(System::Object ^sender, System::ComponentModel::PropertyChangedEventArgs ^e)
		{
			UpdateItem((AimpActionItem^) sender);
		}

	}
}