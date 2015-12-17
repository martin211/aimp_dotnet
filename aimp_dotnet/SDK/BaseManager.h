#pragma once

#include "..\ManagedAimpCore.h"

namespace AIMP
{
	namespace SDK
	{
		using namespace AIMP::SDK;

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
				if (res != AimpActionResult::Ok)
				{
					//AIMP::SDK::InternalLogger::Instance->Write("Invalid operation: result " + result);
				}

				return res;
			}

			ManagedAimpCore^ _core;
		};
	}
}