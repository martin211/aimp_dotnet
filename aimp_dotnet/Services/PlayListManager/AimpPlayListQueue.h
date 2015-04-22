#pragma once

#include "..\..\AIMP_SDK\aimp3_60_sdk.h"
#include "..\..\ObjectHelper.h"

namespace AIMP
{
	namespace SDK
	{
		namespace PlayList
		{
			using namespace AIMP36SDK;
			using namespace AIMP::SDK;

			public ref class AimpPlaylistQueue : public AimpObject<AIMP36SDK::IAIMPPlaylistQueue>, public IAimpPlaylistQueue
			{
			public:
				virtual property bool IsSuspended
				{
					bool get()
					{

					}
					void set(bool value)
					{

					}
				}
			}
		}
	}
}