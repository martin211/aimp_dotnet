// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "SDK/AimpPropertyList.h"
#include "InternalAimpDataFilterGroup.h"

class InternalAimpDataFilter :
    public IUnknownInterfaceImpl<IAIMPMLDataFilter>,
    public InternalAimpDataFilterGroup {
private:
    gcroot<AIMP::SDK::MusicLibrary::IAimpDataFilter^> _managedInstance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataFilter> Base;

    InternalAimpDataFilter(gcroot<AIMP::SDK::MusicLibrary::IAimpDataFilter^> managedInstance);

    virtual HRESULT WINAPI Assign(IAIMPMLDataFilter* Source);
    virtual HRESULT WINAPI Clone(void** Filter);

    virtual ULONG WINAPI AddRef(void);
    virtual ULONG WINAPI Release(void);
    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    HRESULT WINAPI GetValueAsInt32(int PropertyID, int* Value) override;
    HRESULT WINAPI GetValueAsObject(int PropertyID, REFIID IID, void** Value) override;
    HRESULT WINAPI SetValueAsInt32(int PropertyID, int Value) override;
    HRESULT WINAPI SetValueAsObject(int PropertyID, IUnknown* Value) override;
};
