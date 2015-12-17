#pragma once
#include "..\..\AimpSdk.h"

namespace AIMP
{
	namespace SDK
	{
		using namespace AIMP::SDK;
		using namespace AIMP::SDK::Threading;

		public ref class AimpAsyncTask : public AimpObject<IAIMPTask>, public IAimpAsyncTask
		{
		public:
			AimpAsyncTask()
			{}

			virtual AimpActionResult Execute(IAimpAsyncTaskOwner ^owner)
			{
				return AimpActionResult::Fail;
			}
		private:
			//IAIMPAsyncTask
		};
	}
}