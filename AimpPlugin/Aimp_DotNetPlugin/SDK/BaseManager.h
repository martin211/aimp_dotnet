#pragma once

#include "..\ManagedAimpCore.h"

namespace AIMP
{
	namespace SDK
	{
		using namespace AIMP::SDK::Services;

		public ref class AimpBaseManager abstract
		{
		public:
			AimpBaseManager(ManagedAimpCore^ core)
			{
				_core = core;
			}
		protected:
			AimpActionResult CheckResult(HRESULT result)
			{
				AimpActionResult res = Utils::CheckResult(result);
				if (res != AIMP::SDK::Services::AimpActionResult::Ok)
				{
					//AIMP::SDK::InternalLogger::Instance->Write("Invalid operation: result " + result);
				}

				return res;
			}

			ManagedAimpCore^ _core;
		};
	}
}