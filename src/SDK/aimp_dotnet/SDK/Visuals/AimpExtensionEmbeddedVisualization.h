//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

using namespace AIMP::SDK;

class AimpExtensionEmbeddedVisualization : public IUnknownInterfaceImpl<IAIMPExtensionEmbeddedVisualization> {
private:
    gcroot<AIMP::SDK::Visuals::IAimpExtensionEmbeddedVisualization^> _managedObject;
    IAIMPCore* _aimpCore;

public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionEmbeddedVisualization> Base;

    AimpExtensionEmbeddedVisualization(IAIMPCore* aimpCore,
                                       gcroot<AIMP::SDK::Visuals::IAimpExtensionEmbeddedVisualization^> instance) {
        _managedObject = instance;
        _aimpCore = aimpCore;
    }

    virtual int WINAPI GetFlags();

    virtual HRESULT WINAPI GetMaxDisplaySize(int* Width, int* Height);

    virtual HRESULT WINAPI GetName(IAIMPString** S);

    virtual HRESULT WINAPI Initialize(int Width, int Height);

    virtual void WINAPI Finalize();

    virtual void WINAPI Click(int X, int Y, int Button);

    virtual void WINAPI Draw(HDC DC, PAIMPVisualData Data);

    virtual void WINAPI Resize(int NewWidth, int NewHeight);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
