#pragma once

#include <gcroot.h>
#include "Proxy/OptionFrameProxy.h"

class ProxyManager
{
public:
    ProxyManager(IUnknown *proxyPlugin)
    {
        _proxyPlugin = proxyPlugin;
    }

    //IAIMPOptionsDialogFrame *GetOptionsDialogFrameProxy()
    //{
    //    if (_optionsDialogFrameProxy == NULL)
    //    {
    //        //_optionsDialogFrameProxy = new OptionFrameProxy(_proxyPlugin);
    //    }

    //    return _optionsDialogFrameProxy;
    //}
private:
    //IAIMPOptionsDialogFrame *_optionsDialogFrameProxy;
    IUnknown *_proxyPlugin;
};
