//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpExtensionFileFormat.h"

HRESULT InternalAimpExtensionFileFormat::GetDescription(IAIMPString** s) {
    const auto val = _managedInstance->Description;
    if (val->ResultType == ActionResultType::OK) {
        *s = AimpConverter::ToAimpString(val->Result);
    }

    return static_cast<HRESULT>(val->ResultType);
}

HRESULT InternalAimpExtensionFileFormat::GetExtList(IAIMPString** s) {
    const auto val = _managedInstance->ExtList;
    if (val->ResultType == ActionResultType::OK) {
        *s = AimpConverter::ToAimpString(val->Result);
    }

    return static_cast<HRESULT>(val->ResultType);
}

HRESULT InternalAimpExtensionFileFormat::GetFlags(DWORD* s) {
    const auto val = _managedInstance->Flags;
    if (val->ResultType == ActionResultType::OK) {
        *s = static_cast<DWORD>(val->Result);
    }

    return static_cast<HRESULT>(val->ResultType);
}

HRESULT InternalAimpExtensionFileFormat::QueryInterface(const IID& riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionFileFormat) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}

ULONG InternalAimpExtensionFileFormat::AddRef() {
    return Base::AddRef();
}

ULONG InternalAimpExtensionFileFormat::Release() {
    return Base::Release();
}