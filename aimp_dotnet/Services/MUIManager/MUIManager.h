#pragma once

#include "..\..\ManagedAimpCore.h"
#include "..\BaseManager.h"

namespace AIMP36SDK
{
	namespace MUI
	{
		#include "..\..\AIMP_SDK\AIMP360\apiMUI.h"
	}
}

namespace AIMP
{
	namespace SDK
	{
		using namespace System;
		using namespace AIMP::SDK::Services::MUIManager;

		public ref class MIUManager : public AimpBaseManager, public IMUIManager
		{
		public:
			explicit MIUManager(ManagedAimpCore^ core) : AimpBaseManager(core)
			{
				// TODO: Add logging.
				AIMP36SDK::MUI::IAIMPServiceMUI* service;
				core->GetService(AIMP36SDK::MUI::IID_IAIMPServiceMUI, (void**) &service);
				_muiService = service;
			}

			virtual String^ GetName()
			{
				AIMP36SDK::IAIMPString *str;
				try
				{
					_muiService->GetName(&str);
					return gcnew String(str->GetData());
				}
				finally
				{
					str->Release();
					str = NULL;
				}

				return String::Empty;
			}

			virtual String^ GetValue(String^ key)
			{
				AIMP36SDK::IAIMPString *str;
				try
				{
					_muiService->GetValue(ObjectHelper::MakeAimpString(_core->GetAimpCore(), key), &str);
					if (str == NULL)
					{
						return String::Empty;
					}

					return gcnew String(str->GetData());
				}
				finally
				{
					str->Release();
					str = NULL;
				}

				return String::Empty;
			}

			virtual String^ GetValuePart(String^ key, int index)
			{
				AIMP36SDK::IAIMPString *str;
				try
				{
					_muiService->GetValuePart(ObjectHelper::MakeAimpString(_core->GetAimpCore(), key), index, &str);

					if (str == NULL)
					{
						return String::Empty;
					}

					return gcnew String(str->GetData());
				}
				finally
				{
					str->Release();
					str = NULL;
				}

				return String::Empty;
			}

		private:
			AIMP36SDK::MUI::IAIMPServiceMUI* _muiService;
		};
	}
}