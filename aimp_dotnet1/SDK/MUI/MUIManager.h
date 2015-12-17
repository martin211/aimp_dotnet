#pragma once

#include "..\..\ManagedAimpCore.h"
#include "..\BaseManager.h"
#include "ObjectHelper.h"

namespace AIMP
{
	namespace SDK
	{
		using namespace System;
		using namespace AIMP::SDK::Services::MUIManager;

		public ref class AimpMIUManager : public AimpBaseManager, public IAimpMUIManager
		{
		public:
			explicit AimpMIUManager(ManagedAimpCore^ core) : AimpBaseManager(core)
			{
				// TODO: Add logging.
				IAIMPServiceMUI* service;
				core->GetService(IID_IAIMPServiceMUI, (void**) &service);
				_muiService = service;
			}

			virtual String^ GetName()
			{
				IAIMPString *str;
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
				IAIMPString *str;
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
				IAIMPString *str;
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
			IAIMPServiceMUI* _muiService;
		};
	}
}