// This is the main DLL file.

#include "stdafx.h"
#include "DotNetPlugin.h"
#include "AIMP_SDK\aimp3_60_sdk.h"


BOOL WINAPI AIMPPluginGetHeader(AIMP36SDK::IAIMPPlugin **Header)
{
	*Header = new DotNetPlugin();
	return true;
}