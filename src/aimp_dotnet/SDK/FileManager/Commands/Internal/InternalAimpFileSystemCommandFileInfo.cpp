// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpFileSystemCommandFileInfo.h"

using namespace AIMP::SDK;

InternalAimpFileSystemCommandFileInfo::InternalAimpFileSystemCommandFileInfo(
    gcroot<IAimpFileSystemCommandFileInfo^> instance, IAIMPCore* core)
{
    _instance = instance;
    _core = core;
}

HRESULT WINAPI InternalAimpFileSystemCommandFileInfo::GetFileAttrs(IAIMPString* fileName, TAIMPFileAttributes* attrs)
{
    AimpFileAttributes attr;

    AimpActionResult result = _instance->GetFileAttrs(AimpConverter::ToManagedString(fileName), attr);

    attrs = new TAIMPFileAttributes();
    attrs->Attributes = DWORD(attr.Attributes);
    attrs->TimeCreation = attr.TimeCreation.ToOADate();
    attrs->TimeLastAccess = attr.TimeLastAccess.ToOADate();
    attrs->TimeLastWrite = attr.TimeLastWrite.ToOADate();

    return HRESULT(result);
}

HRESULT WINAPI InternalAimpFileSystemCommandFileInfo::GetFileSize(IAIMPString* fileName, INT64* size)
{
    long long sizeValur = 0;
    AimpActionResult result = _instance->GetFileSize(AimpConverter::ToManagedString(fileName), sizeValur);
    *size = sizeValur;
    return HRESULT(result);
}

HRESULT WINAPI InternalAimpFileSystemCommandFileInfo::IsFileExists(IAIMPString* fileName)
{
    return HRESULT(_instance->IsFileExists(AimpConverter::ToManagedString(fileName)));
}

ULONG WINAPI InternalAimpFileSystemCommandFileInfo::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI InternalAimpFileSystemCommandFileInfo::Release(void)
{
    return Base::Release();
}

HRESULT WINAPI InternalAimpFileSystemCommandFileInfo::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPFileSystemCommandFileInfo)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}
