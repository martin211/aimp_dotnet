// ----------------------------------------------------
//
// AIMP DotNet SDK
//
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
//
// Mail: mail4evgeniy@gmail.com
//
// ----------------------------------------------------

#pragma once
#include "SDK/AimpPropertyList.h"

using namespace AIMP::SDK::MusicLibrary::DataFilter;

class InternalAimpDataFilterGroup :
    public IUnknownInterfaceImpl<IAIMPMLDataFilterGroup>,
    public AimpPropertyList
{
private:
    gcroot<IAimpDataFilterGroup^> _managed;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataFilterGroup> Base;

    InternalAimpDataFilterGroup(gcroot<AIMP::SDK::MusicLibrary::DataFilter::IAimpDataFilterGroup^> managed);

    virtual HRESULT WINAPI Add(IUnknown* Field, VARIANT* Value1, VARIANT* Value2, int Operation, IAIMPMLDataFieldFilter** Filter);
    virtual HRESULT WINAPI Add2(IUnknown* Field, VARIANT* Values, int Count, IAIMPMLDataFieldFilterByArray** Filter);
    virtual HRESULT WINAPI AddGroup(IAIMPMLDataFilterGroup** Group);
    virtual HRESULT WINAPI Clear();
    virtual HRESULT WINAPI Delete(int Index);
    virtual HRESULT WINAPI GetChild(int Index, REFIID IID, void **Obj);
    virtual int WINAPI GetChildCount();

    virtual ULONG WINAPI AddRef(void);
    virtual ULONG WINAPI Release(void);
    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    HRESULT WINAPI GetValueAsInt32(int PropertyID, int *Value) override;
    HRESULT WINAPI SetValueAsInt32(int PropertyID, int Value) override;
};
