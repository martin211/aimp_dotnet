// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpDataStorageCommandDeleteFiles.h"
#include "SDK/MusicLibrary/AimpFileList.h"

AimpDataStorageCommandDeleteFiles::AimpDataStorageCommandDeleteFiles(
    gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandDeleteFiles^> instance)
{
    _instance = instance;
}

BOOL WINAPI AimpDataStorageCommandDeleteFiles::CanDelete(BOOL Physically)
{
    return _instance->CanDelete(Physically);
}

HRESULT WINAPI AimpDataStorageCommandDeleteFiles::Delete(IAIMPMLFileList* Files, BOOL Physically)
{
    return HRESULT(_instance->Delete(gcnew AimpFileList(Files), Physically)->ResultType);
}

HRESULT WINAPI AimpDataStorageCommandDeleteFiles::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    *ppvObject = nullptr;
    if (riid == IID_IAIMPMLDataStorageCommandDeleteFiles)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG WINAPI AimpDataStorageCommandDeleteFiles::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI AimpDataStorageCommandDeleteFiles::Release(void)
{
    return Base::Release();
}
