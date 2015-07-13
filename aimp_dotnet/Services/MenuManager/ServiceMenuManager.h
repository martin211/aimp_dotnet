#pragma once

#include "..\..\ManagedAimpCore.h"
#include "..\BaseManager.h"
#include "MenuItemEvent.h"
#include "ICallBackHeader.h"


namespace AIMP36SDK
{
	#include "..\..\AIMP_SDK\AIMP360\apiMenu.h"	
}
		
namespace AIMP
{
	namespace SDK
	{
		using namespace AIMP::SDK::UI::MenuItem;
		using namespace AIMP::SDK::Services::MenuManager;
		using namespace AIMP::SDK360;

		public ref class ServiceMenuManager : public AimpBaseManager, public IMenuManager
		{
		public:
			explicit ServiceMenuManager(ManagedAimpCore^ core);

			virtual void AddRange(ParentMenuType parentMenuType, MenuItemCollection^ items);

			virtual void Add(ParentMenuType parentMenuType, MenuItem^ item);

			virtual void Delete(MenuItem^ item);

			virtual void Delete(String^ id);

			virtual void Delete(MenuItemCollection^ items);

			virtual MenuItem^ GetById(String^ id);

			virtual MenuItem ^GetBuiltIn(ParentMenuType parentMenuType);

		private:
			AIMP36SDK::IAIMPServiceMenuManager* _aimpMenuManager;

			AIMP36SDK::IAIMPServiceActionManager* _aimpActionManager;

			void RegisterMenu(IAIMPMenuItem* parentMenuItem, MenuItem^ menuItem);

			void UnregisterMenu(IAIMPMenuItem* menuItem);

			void UpdateMenuItem(MenuItem^ menuItem);

			void FillMenuData(IAIMPMenuItem* aimpMenuItem, MenuItem^ menuItem);

			void OnPropertyChanged(System::Object ^sender, System::ComponentModel::PropertyChangedEventArgs ^e);

			void OnSubitemAdded(MenuItem ^parent, MenuItem ^item);

			void OnSubItemDeleted(System::Object ^item);
		};
	}
}