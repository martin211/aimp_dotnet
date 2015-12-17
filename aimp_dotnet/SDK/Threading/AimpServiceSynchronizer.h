#pragma once
#include "AimpAsyncTask.h"

namespace AIMP
{
	namespace SDK
	{
		using namespace AIMP::SDK::Threading;

		public ref class AimpServiceSynchronizer : public IAimpServiceSynchronizer
		{
		public:
			virtual AimpActionResult ExecuteInMainThread(IAimpAsyncTask^ task, bool executeNow)
			{
				return AIMP::SDK::AimpActionResult::Fail;
			}
		};
	}
}