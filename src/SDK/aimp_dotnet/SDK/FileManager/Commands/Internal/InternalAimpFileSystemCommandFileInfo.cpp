//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpFileSystemCommandFileInfo.h"

using namespace AIMP::SDK;

InternalAimpFileSystemCommandFileInfo::InternalAimpFileSystemCommandFileInfo(
    gcroot<IAimpFileSystemCommandFileInfo^> instance, IAIMPCore* core) {
    _instance = instance;
    _core = core;
}

HRESULT WINAPI InternalAimpFileSystemCommandFileInfo::GetFileAttrs(IAIMPString* fileName, TAIMPFileAttributes* attrs) {
    const auto result = _instance->GetFileAttrs(AimpConverter::ToManagedString(fileName));
    AimpFileAttributes attr = result->Result;

    attrs = new TAIMPFileAttributes();
    attrs->Attributes = DWORD(attr.Attributes);
    attrs->TimeCreation = attr.TimeCreation;
    attrs->TimeLastAccess = attr.TimeLastAccess;
    attrs->TimeLastWrite = attr.TimeLastWrite;

    return HRESULT(result->ResultType);
}

HRESULT WINAPI InternalAimpFileSystemCommandFileInfo::GetFileSize(IAIMPString* fileName, INT64* size) {
    long long sizeValur = 0;
    const auto result = _instance->GetFileSize(AimpConverter::ToManagedString(fileName));
    *size = result->Result;
    return HRESULT(result->ResultType);
}

HRESULT WINAPI InternalAimpFileSystemCommandFileInfo::IsFileExists(IAIMPString* fileName) {
    return HRESULT(_instance->IsFileExists(AimpConverter::ToManagedString(fileName))->ResultType);
}

ULONG WINAPI InternalAimpFileSystemCommandFileInfo::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI InternalAimpFileSystemCommandFileInfo::Release(void) {
    return Base::Release();
}

HRESULT WINAPI InternalAimpFileSystemCommandFileInfo::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPFileSystemCommandFileInfo) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}
