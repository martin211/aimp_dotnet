#pragma once
#include "SDK/AimpPropertyList.h"

class InternalDataFieldFilter :
    public IUnknownInterfaceImpl<IAIMPMLDataFieldFilter>,
    public AimpPropertyList {
private:
    gcroot<IAimpDataFieldFilter^> _managed;
    typedef IUnknownInterfaceImpl<IAIMPMLDataFieldFilter> Base;
public:
    InternalDataFieldFilter(gcroot<IAimpDataFieldFilter^> managed) : _managed(managed) {        
    }

    HRESULT __stdcall GetValueAsInt32(int PropertyID, int* Value) override {
        if (PropertyID == AIMPML_FIELDFILTER_OPERATION) {
            *Value = static_cast<int>(_managed->Operation);
            return S_OK;
        }

        return E_NOTIMPL;
    }

    HRESULT __stdcall SetValueAsInt32(int PropertyID, int Value) override {
        if (PropertyID == AIMPML_FIELDFILTER_OPERATION) {
            _managed->Operation = static_cast<FieldFilterOperationType>(Value);
            return S_OK;
        }

        return E_NOTIMPL;
    }

    HRESULT __stdcall GetValueAsObject(int PropertyID, const IID& IID, void** Value) override {
        if (PropertyID == AIMPML_FIELDFILTER_FIELD) {
            const auto f = AimpConverter::ToAimpString(_managed->Field);
            *Value = f;
            return S_OK;
        }

        return E_NOTIMPL;
    }

    HRESULT __stdcall SetValueAsObject(int PropertyID, IUnknown* Value) override {
        if (PropertyID == AIMPML_FIELDFILTER_FIELD) {
            _managed->Field = AimpConverter::ToManagedString(static_cast<IAIMPString*>(Value));
            return S_OK;
        }

        return E_NOTIMPL;
    }

    HRESULT __stdcall GetValueAsVariant(int PropertyID, VARIANT* Value) override {
        if (PropertyID == AIMPML_FIELDFILTER_VALUE1) {
            *Value = AimpConverter::ToNativeVariant(_managed->Value1);
            return S_OK;
        }

        if (PropertyID == AIMPML_FIELDFILTER_VALUE2) {
            *Value = AimpConverter::ToNativeVariant(_managed->Value2);
            return S_OK;
        }

        return E_NOTIMPL;
    }

    HRESULT __stdcall SetValueAsVariant(int PropertyID, VARIANT* Value) override {
        if (PropertyID == AIMPML_FIELDFILTER_VALUE1) {
            _managed->Value1 = AimpConverter::FromVariant(Value);
            return S_OK;
        }

        if (PropertyID == AIMPML_FIELDFILTER_VALUE2) {
            _managed->Value2 = AimpConverter::FromVariant(Value);
            return S_OK;
        }

        return E_NOTIMPL;
    }

    virtual ULONG WINAPI AddRef(void) {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void) {
        return Base::Release();
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject) {
        const HRESULT res = Base::QueryInterface(riid, ppvObject);

        if (riid == IID_IAIMPMLDataFieldFilter) {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        *ppvObject = nullptr;
        return res;
    }
};
