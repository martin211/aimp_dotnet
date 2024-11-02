#include "plugin.h"

BOOL WINAPI AIMPPluginGetHeader(IAIMPPlugin** Header) {
    *Header = new NativePlugin();
    return true;
}
