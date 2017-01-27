/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 */
 
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

    virtual HRESULT WINAPI Initialize(int Width, int Height);

    virtual void WINAPI Finalize();

    virtual void WINAPI Click(int X, int Y, int Button);

    virtual void WINAPI Draw(HDC DC, PAIMPVisualData Data);

    virtual void WINAPI Resize(int NewWidth, int NewHeight);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
