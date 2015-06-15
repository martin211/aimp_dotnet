#pragma once

#include "AIMP_SDK/aimp3_60_sdk.h"

namespace AIMP36SDK
{
	

	class IUnknownReferencesManager
	{
	private:
		AIMP36SDK::IAIMPOptionsDialogFrame *_frame;
		AIMP36SDK::IAIMPExtensionPlaylistManagerListener *_listner;
	}
}