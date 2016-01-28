#pragma once

using namespace AIMP::SDK;

class AimpExtensionEmbeddedVisualization : public IUnknownInterfaceImpl<IAIMPExtensionEmbeddedVisualization>
{
private:
    gcroot<AIMP::SDK::Visuals::IAimpExtensionEmbeddedVisualization^> _managedObject;
    IAIMPCore *_aimpCore;

public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionEmbeddedVisualization> Base;

    AimpExtensionEmbeddedVisualization(IAIMPCore *aimpCore, gcroot<AIMP::SDK::Visuals::IAimpExtensionEmbeddedVisualization^> instance)
    {
        _managedObject = instance;
        _aimpCore = aimpCore;
    }

    virtual int WINAPI GetFlags();

    virtual HRESULT WINAPI GetMaxDisplaySize(int *Width, int *Height);

    virtual HRESULT WINAPI GetName(IAIMPString **S);

    virtual void WINAPI Initialize(int Width, int Height);

    virtual void WINAPI Finalize();

    virtual void WINAPI Click(int X, int Y, int Button);

    virtual void WINAPI Draw(HDC DC, PAIMPVisualData Data);

    virtual void WINAPI Resize(int NewWidth, int NewHeight);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (!ppvObject)
        {
            return E_POINTER;
        }

        if (riid == IID_IAIMPExtensionEmbeddedVisualization) {
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
