// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

class AimpPropertyList : public IAIMPPropertyList, IAIMPPropertyList2 {
public:
    virtual void WINAPI BeginUpdate() {
    };

    virtual void WINAPI EndUpdate() {
    };
    virtual HRESULT WINAPI Reset() { return E_NOTIMPL; }
    // Read
    virtual HRESULT WINAPI GetValueAsFloat(int PropertyID, double* Value) { return E_NOTIMPL; }
    virtual HRESULT WINAPI GetValueAsInt32(int PropertyID, int* Value) { return E_NOTIMPL; }
    virtual HRESULT WINAPI GetValueAsInt64(int PropertyID, INT64* Value) { return E_NOTIMPL; }
    virtual HRESULT WINAPI GetValueAsObject(int PropertyID, REFIID IID, void** Value) { return E_NOTIMPL; }
    // Write
    virtual HRESULT WINAPI SetValueAsFloat(int PropertyID, const double Value) { return E_NOTIMPL; }
    virtual HRESULT WINAPI SetValueAsInt32(int PropertyID, int Value) { return E_NOTIMPL; }
    virtual HRESULT WINAPI SetValueAsInt64(int PropertyID, const INT64 Value) { return E_NOTIMPL; }
    virtual HRESULT WINAPI SetValueAsObject(int PropertyID, IUnknown* Value) { return E_NOTIMPL; }

    HRESULT WINAPI GetValueAsVariant(int PropertyID, VARIANT* Value) { return E_NOTIMPL; }
    HRESULT WINAPI SetValueAsVariant(int PropertyID, VARIANT* Value) { return E_NOTIMPL; }
};
