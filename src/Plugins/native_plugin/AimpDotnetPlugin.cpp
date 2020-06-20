// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "native_plugin.h"


BOOL WINAPI AIMPPluginGetHeader(IAIMPPlugin** Header)
{
    *Header = new NativePlugin();
    return true;
}
