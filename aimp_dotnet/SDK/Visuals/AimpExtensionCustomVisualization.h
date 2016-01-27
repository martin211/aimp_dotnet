#pragma once

using namespace AIMP::SDK;


class AimpExtensionCustomVisualization : public IUnknownInterfaceImpl<IAIMPExtensionCustomVisualization>
{
private:
    gcroot<AIMP::SDK::Visuals::IAimpExtensionCustomVisualization^> _managedObject;
    IAIMPCore *_aimpCore;
public:
    AimpExtensionCustomVisualization(IAIMPCore *aimpCore, gcroot<AIMP::SDK::Visuals::IAimpExtensionCustomVisualization^> instance)
    {
        _managedObject = instance;
        _aimpCore = aimpCore;
    }

    virtual int WINAPI GetFlags();

    virtual void WINAPI Draw(PAIMPVisualData Data);
};

