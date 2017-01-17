#pragma once

using namespace AIMP::SDK;


class AimpExtensionCustomVisualization : public IUnknownInterfaceImpl<IAIMPExtensionCustomVisualization>
{
private:
    gcroot<AIMP::SDK::Visuals::IAimpExtensionCustomVisualization^> _managedObject;
    IAIMPCore *_aimpCore;
public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionCustomVisualization> Base;

    AimpExtensionCustomVisualization(IAIMPCore *aimpCore, gcroot<AIMP::SDK::Visuals::IAimpExtensionCustomVisualization^> instance)
    {
        _managedObject = instance;
        _aimpCore = aimpCore;
    }

    virtual int WINAPI GetFlags();

    virtual void WINAPI Draw(PAIMPVisualData Data);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (!ppvObject)
        {
            return E_POINTER;
        }

        if (riid == IID_IAIMPExtensionCustomVisualization) {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }
};

