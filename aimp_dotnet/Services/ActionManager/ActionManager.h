#pragma once

#include "..\..\ManagedAimpCore.h"
#include "..\BaseManager.h"

namespace AIMP
{
	namespace SDK
	{
		using namespace AIMP::SDK::UI::ActionItem;
		using namespace AIMP::SDK::Services::ActionManager;
		using namespace AIMP::SDK360;

		public ref class ActionManager : public AimpBaseManager, public IActionManager
		{
		public:
			explicit ActionManager(ManagedAimpCore^ core);

			virtual void Add(AimpActionItem^ action);

			virtual void AddRange(ActionItemCollection^ actions);

		private:
			ManagedAimpCore^ _core;

			IAIMPServiceActionManager* _manager;

			void RegisterAction(AimpActionItem^ menuItem);

			void OnPropertyChanged(System::Object ^sender, System::ComponentModel::PropertyChangedEventArgs ^e);

			void UpdateItem(AimpActionItem^ menuItem);
		};
	}
}