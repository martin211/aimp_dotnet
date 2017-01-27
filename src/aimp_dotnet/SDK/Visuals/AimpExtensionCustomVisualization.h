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

class AimpExtensionCustomVisualization : public IUnknownInterfaceImpl<IAIMPExtensionCustomVisualization>
{
private:
    gcroot<AIMP::SDK::Visuals::IAimpExtensionCustomVisualization^> _managedObject;
    IAIMPCore *_aimpCore;
public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionCustomVisualization> Base;

    AimpExtensionCustomVisualization(IAIMPCore *aimpCore, gcroot<AIMP::SDK::Visuals::IAimpExtensionCustomVisualization^> instance);

    virtual int WINAPI GetFlags();

    virtual void WINAPI Draw(PAIMPVisualData Data);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
