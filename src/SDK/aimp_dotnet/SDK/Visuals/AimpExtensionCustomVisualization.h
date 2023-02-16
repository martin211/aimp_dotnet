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

class AimpExtensionCustomVisualization : public IUnknownInterfaceImpl<IAIMPExtensionCustomVisualization> {
private:
    gcroot<AIMP::SDK::Visuals::IAimpExtensionCustomVisualization^> _managedObject;
    IAIMPCore* _aimpCore;
public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionCustomVisualization> Base;

    AimpExtensionCustomVisualization(IAIMPCore* aimpCore,
                                     gcroot<AIMP::SDK::Visuals::IAimpExtensionCustomVisualization^> instance);

    virtual int WINAPI GetFlags();

    virtual void WINAPI Draw(PAIMPVisualData Data);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
