#pragma once

#include "..\ManagedAimpCore.h"
#include "..\InternalLogger.h"

namespace AIMP
{
	namespace SDK
	{
		using namespace AIMP::SDK360;

		public ref class AimpBaseManager abstract
		{
		public:
			AimpBaseManager(ManagedAimpCore^ core)
			{
				_core = core;
			}
		protected:
			bool CheckResult(HRESULT result)
			{
				if (Utils::CheckResult(result) == AIMP::SDK::Services::ActionResult::Ok)
				{
					return true;
				}

				AIMP::SDK::InternalLogger::Instance->Write("Invalid operation: result " + result);
				return false;
			}

			ManagedAimpCore^ _core;
		};
	}
}