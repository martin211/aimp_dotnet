// This is the main DLL file.

#include "native_plugin.h"


BOOL WINAPI AIMPPluginGetHeader(IAIMPPlugin **Header)
{
	*Header = new NativePlugin();
	return true;
}
