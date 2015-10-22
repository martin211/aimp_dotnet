#pragma once
#include "AIMP_SDK/AimpSDK.h"

namespace AIMP
{
	namespace SDK
	{
		using namespace AIMP::SDK;
		using namespace AIMP::SDK::Services;
		using namespace AIMP::SDK::Services::Threading;

		public ref class AimpAsyncTask : public AimpObject<IAIMPTask>, public IAimpAsyncTask
		{
		public:
			AimpAsyncTask()
			{}

			virtual AimpActionResult Execute(IAimpAsyncTaskOwner ^owner)
			{
				
			}
		private:
			//IAIMPAsyncTask
		};
	}
}