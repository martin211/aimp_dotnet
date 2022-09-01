//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "stdafx.h"
#include "AimpDataStorageCommandDeleteFiles2.h"

#include "SDK/MusicLibrary/DataFilter/AimpDataFilter.h"

using namespace Extension::Command;

AimpDataStorageCommandDeleteFiles2::AimpDataStorageCommandDeleteFiles2(gcroot<IAimpDataStorageCommandDeleteFiles2^> instance): AimpDataStorageCommandDeleteFiles(static_cast<IAimpDataStorageCommandDeleteFiles^>(instance)) {
    _instance = instance;
}

HRESULT AimpDataStorageCommandDeleteFiles2::Delete2(IAIMPMLDataFilter* Filter, BOOL Physically) {
    return static_cast<HRESULT>(_instance->Delete2(gcnew AimpDataFilter(Filter), Physically)->ResultType);
}

BOOL AimpDataStorageCommandDeleteFiles2::CanDelete(BOOL Physically) {
    return AimpDataStorageCommandDeleteFiles::CanDelete(Physically);
}

HRESULT AimpDataStorageCommandDeleteFiles2::Delete(IAIMPMLFileList* Files, BOOL Physically) {
    return AimpDataStorageCommandDeleteFiles::Delete(Files, Physically);
}

HRESULT AimpDataStorageCommandDeleteFiles2::QueryInterface(const IID& riid, LPVOID* ppvObject) {
    *ppvObject = nullptr;
    if (riid == IID_IAIMPMLDataStorageCommandDeleteFiles2) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG AimpDataStorageCommandDeleteFiles2::AddRef() {
    return Base::AddRef();
}

ULONG AimpDataStorageCommandDeleteFiles2::Release() {
    return Base::Release();
}
