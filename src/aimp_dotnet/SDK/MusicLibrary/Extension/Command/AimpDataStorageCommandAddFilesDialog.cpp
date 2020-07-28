// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpDataStorageCommandAddFilesDialog.h"

AimpDataStorageCommandAddFilesDialog::AimpDataStorageCommandAddFilesDialog(
    gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandAddFilesDialog^> instance)
{
    _instance = instance;
}

HRESULT WINAPI AimpDataStorageCommandAddFilesDialog::Execute(HWND OwnerHandle)
{
    IntPtr ownerHandle(OwnerHandle);
    return HRESULT(_instance->Execute(ownerHandle)->ResultType);
}

HRESULT WINAPI AimpDataStorageCommandAddFilesDialog::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    *ppvObject = nullptr;
    if (riid == IID_IAIMPMLDataStorageCommandAddFilesDialog)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG WINAPI AimpDataStorageCommandAddFilesDialog::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI AimpDataStorageCommandAddFilesDialog::Release(void)
{
    return Base::Release();
}
