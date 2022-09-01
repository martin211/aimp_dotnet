//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "SDK/AimpPropertyList.h"

class InternalAimpDataFieldFilterByArray :
    public IUnknownInterfaceImpl<IAIMPMLDataFieldFilterByArray>,
    public AimpPropertyList {
private:
    gcroot<IAimpDataFieldFilterByArray^> _managed;
    typedef IUnknownInterfaceImpl<IAIMPMLDataFieldFilterByArray> Base;
public:
    InternalAimpDataFieldFilterByArray(gcroot<IAimpDataFieldFilterByArray^> managed): _managed(managed) {
    }

    HRESULT __stdcall GetValueAsObject(int PropertyID, const IID& IID, void** Value) override {
        if (PropertyID == AIMPML_FIELDFILTERBYARRAY_FIELD) {
            const auto f = AimpConverter::ToAimpString(_managed->Field);
            *Value = f;
            return S_OK;
        }

        return E_NOTIMPL;
    }

    HRESULT __stdcall SetValueAsObject(int PropertyID, IUnknown* Value) override {
        if (PropertyID == AIMPML_FIELDFILTERBYARRAY_FIELD) {
            _managed->Field = AimpConverter::ToManagedString(static_cast<IAIMPString*>(Value));
            return S_OK;
        }

        return E_NOTIMPL;
    }

    virtual HRESULT WINAPI GetData(VARIANT* Values, int* Count) {
        const auto data = _managed->GetData();
        if (data->ResultType == ActionResultType::OK) {
            Values = new VARIANT[data->Result->Count];

            for (int i = 0; i < data->Result->Count; i++) {
                Values[i] = AimpConverter::ToNativeVariant(data->Result[i]);
            }
        }

        return static_cast<HRESULT>(data->ResultType);
    }

    virtual HRESULT WINAPI SetData(VARIANT* Values, int Count) {
        const auto result = gcnew List<Object^>(Count);
        for (int i = 0; i < Count; i++) {
            result->Add(AimpConverter::FromVariant(&Values[0]));
        }

        const auto res = _managed->SetData(result);
        return static_cast<HRESULT>(res->ResultType);
    }

    virtual ULONG WINAPI AddRef(void) {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void) {
        return Base::Release();
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject) {
        const HRESULT res = Base::QueryInterface(riid, ppvObject);

        if (riid == IID_IAIMPMLDataFieldFilterByArray) {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        *ppvObject = nullptr;
        return res;
    }
};
