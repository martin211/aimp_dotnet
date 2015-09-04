#pragma once
#include "..\..\AIMP_SDK\aimp3_60_sdk.h"
#include "..\..\ObjectHelper.h"

namespace AIMP
{
	namespace SDK
	{		
		namespace Playback
		{
			using namespace AIMP::SDK::Services::Playback

				public ref class AimpPlaybackQueueItem : public AimpObject<AIMP36SDK::IAIMPPlaybackQueueItem>, public IAimpPlaybackQueueItem
			{

			};
		}		
	}
}