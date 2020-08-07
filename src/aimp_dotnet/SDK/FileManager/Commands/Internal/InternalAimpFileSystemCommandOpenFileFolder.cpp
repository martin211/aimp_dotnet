// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpFileSystemCommandOpenFileFolder.h"

using namespace AIMP::SDK;

InternalAimpFileSystemCommandOpenFileFolder::InternalAimpFileSystemCommandOpenFileFolder(
    gcroot<IAimpFileSystemCommandOpenFileFolder^> instance) {
    _instance = instance;
}

HRESULT WINAPI InternalAimpFileSystemCommandOpenFileFolder::CanProcess(IAIMPString* FileName) {
    return HRESULT(_instance->CanProcess(AimpConverter::ToManagedString(FileName))->ResultType);
}

HRESULT WINAPI InternalAimpFileSystemCommandOpenFileFolder::Process(IAIMPString* FileName) {
    return HRESULT(_instance->Process(AimpConverter::ToManagedString(FileName))->ResultType);
}

ULONG WINAPI InternalAimpFileSystemCommandOpenFileFolder::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI InternalAimpFileSystemCommandOpenFileFolder::Release(void) {
    return Base::Release();
}

HRESULT WINAPI InternalAimpFileSystemCommandOpenFileFolder::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPFileSystemCommandOpenFileFolder) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}
