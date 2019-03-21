// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpFileSystemCommandFileInfo.h"

using namespace AIMP::SDK;

InternalAimpFileSystemCommandFileInfo::InternalAimpFileSystemCommandFileInfo(gcroot<IAimpFileSystemCommandFileInfo^> instance, IAIMPCore* core)
{
    _instance = instance;
    _core = core;
}

HRESULT WINAPI InternalAimpFileSystemCommandFileInfo::GetFileAttrs(IAIMPString* FileName, TAIMPFileAttributes* Attrs)
{
    AimpFileAttributes attr;

    AimpActionResult result = _instance->GetFileAttrs(AimpConverter::ToManagedString(FileName), attr);

    Attrs = new TAIMPFileAttributes();
    Attrs->Attributes = DWORD(attr.Attributes);
    Attrs->TimeCreation = attr.TimeCreation.ToOADate();
    Attrs->TimeLastAccess = attr.TimeLastAccess.ToOADate();
    Attrs->TimeLastWrite = attr.TimeLastWrite.ToOADate();

    return HRESULT(result);
}

HRESULT WINAPI InternalAimpFileSystemCommandFileInfo::GetFileSize(IAIMPString* FileName, INT64* Size)
{
    long long size = 0;
    AimpActionResult result = _instance->GetFileSize(AimpConverter::ToManagedString(FileName), size);
    *Size = size;
    return HRESULT(result);
}

HRESULT WINAPI InternalAimpFileSystemCommandFileInfo::IsFileExists(IAIMPString* FileName)
{
    return HRESULT(_instance->IsFileExists(AimpConverter::ToManagedString(FileName)));
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
