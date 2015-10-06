#pragma once

#include "..\..\ManagedAimpCore.h"
#include "..\BaseManager.h"

namespace AIMP
{
	namespace SDK
	{
		using namespace System;
		using namespace AIMP::SDK::Services::ConfigurationManager;

		public ref class AimpConfigurationManager : public AimpBaseManager, public IAimpConfigurationManager
		{
		public:
			explicit AimpConfigurationManager(ManagedAimpCore^ core) : AimpBaseManager(core)
			{
				IAIMPServiceConfig* service;
				core->GetService(IID_IAIMPServiceConfig, (void**) &service);
				_service = service;
			}

			virtual void Delete(String^ key)
			{
				_service->Delete(ObjectHelper::MakeAimpString(_core->GetAimpCore(), key));
			}

			virtual void FlushCache()
			{
				CheckResult(_service->FlushCache());
			}

			virtual double GetValueAsFloat(String^ key)
			{
				double value;
				CheckResult(_service->GetValueAsFloat(ObjectHelper::MakeAimpString(_core->GetAimpCore(), key), &value));
				return value;
			}

			virtual int GetValueAsInt32(String^ key)
			{
				int value;
				CheckResult(_service->GetValueAsInt32(ObjectHelper::MakeAimpString(_core->GetAimpCore(), key), &value));
				return value;
			}

			virtual Int64 GetValueAsInt64(String^ key)
			{
				Int64 value;
				CheckResult(_service->GetValueAsInt64(ObjectHelper::MakeAimpString(_core->GetAimpCore(), key), &value));
				return value;
			}

			virtual System::IO::Stream^ GetValueAsStream(String^ key)
			{
				// TODO: Complete it. What it should be, some array of bytes?
				return nullptr;
			}

			virtual String^ GetValueAsString(String^ key)
			{
				IAIMPString* val = NULL;

				try
				{
					CheckResult(_service->GetValueAsString(ObjectHelper::MakeAimpString(_core->GetAimpCore(), key), &val));
					return gcnew String(val->GetData());
				}
				finally
				{
					val->Release();
					val = NULL;
				}

				return String::Empty;
			}

			virtual void SetValueAsFloat(String^ key, double value)
			{
				CheckResult(_service->SetValueAsFloat(ObjectHelper::MakeAimpString(_core->GetAimpCore(), key), value));
			}

			virtual void SetValueAsInt32(String^ key, int value)
			{
				CheckResult(_service->SetValueAsInt32(ObjectHelper::MakeAimpString(_core->GetAimpCore(), key), value));
			}

			virtual void SetValueAsInt64(String^ key, Int64 value)
			{
				CheckResult(_service->SetValueAsInt64(ObjectHelper::MakeAimpString(_core->GetAimpCore(), key), value));
			}

			virtual void SetValueAsStream(String^ key, System::IO::Stream^ value)
			{
				// TODO: Complete it. What it should be, some array of bytes?
				//_service->SetValueAsStream(key, value);
			}

			virtual void SetValueAsString(String^ key, String^ value)
			{
				CheckResult(_service->SetValueAsString(ObjectHelper::MakeAimpString(_core->GetAimpCore(), key), ObjectHelper::MakeAimpString(_core->GetAimpCore(), value)));
			}

		private:
			IAIMPServiceConfig* _service;
		};
	}
}