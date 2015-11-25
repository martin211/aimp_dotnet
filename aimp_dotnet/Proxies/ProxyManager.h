#pragma once

#include <gcroot.h>
#include "..\AIMP_SDK\AimpSDK.h"
#include "AimpPlayer.h"
#include "ObjectHelper.h"
#include "InternalLogger.h"
#include "OptionFrameProxy.h"


class ProxyManager
{
    public:
        ProxyManager(IUnknown *proxyPlugin)
        {
            _proxyPlugin = proxyPlugin;
        }

        IAIMPOptionsDialogFrame *GetOptionsDialogFrameProxy()
        {
            if (_optionsDialogFrameProxy == NULL)
            {
                _optionsDialogFrameProxy = new OptionFrameProxy(_proxyPlugin);
            }

            return _optionsDialogFrameProxy;
        }
    private:
        IAIMPOptionsDialogFrame *_optionsDialogFrameProxy;
        IUnknown *_proxyPlugin;
};
