// This is the main DLL file.

#include "stdafx.h"
#include "DotNetPlugin.h"


BOOL WINAPI AIMPPluginGetHeader(IAIMPPlugin **Header)
{
	*Header = new DotNetPlugin();
	return true;
}