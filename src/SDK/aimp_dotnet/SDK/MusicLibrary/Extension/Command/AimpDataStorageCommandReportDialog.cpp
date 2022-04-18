// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpDataStorageCommandReportDialog.h"

#pragma region AimpDataStorageCommandReportDialog
AimpDataStorageCommandReportDialog::AimpDataStorageCommandReportDialog(
    gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandReportDialog^> instance) {
    _instance = instance;
}

HRESULT WINAPI AimpDataStorageCommandReportDialog::Execute(HWND OwnerHandle) {
    IntPtr ownerHandle(OwnerHandle);
    return HRESULT(_instance->Execute(ownerHandle)->ResultType);
}

HRESULT WINAPI AimpDataStorageCommandReportDialog::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    *ppvObject = nullptr;
    if (riid == IID_IAIMPMLDataStorageCommandReportDialog) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG WINAPI AimpDataStorageCommandReportDialog::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI AimpDataStorageCommandReportDialog::Release(void) {
    return Base::Release();
}
#pragma endregion
