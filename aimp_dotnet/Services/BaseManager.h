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
				if (result == S_OK)
				{
					return true;
				}

				//System::Diagnostics::Debugger::Break();
				AIMP::SDK::InternalLogger::Instance->Write("Invalid operation: result " + result);
				return false;
			}

			ManagedAimpCore^ _core;
		};
	}
}