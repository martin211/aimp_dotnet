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
#include "AimpFileSystemCommandFileInfo.h"

using namespace AIMP::SDK;
using namespace Objects;

AimpFileSystemCommandFileInfo::
AimpFileSystemCommandFileInfo(IAIMPFileSystemCommandFileInfo* aimpObject) : AimpObject(aimpObject)
{
}

AimpActionResult AimpFileSystemCommandFileInfo::GetFileAttrs(String^ file, AimpFileAttributes% attr)
{
    auto str = AimpConverter::ToAimpString(file);
    auto result = AimpActionResult::Fail;
    auto atr = AimpFileAttributes();

    try
    {
        TAIMPFileAttributes* fattr = nullptr;
        result = CheckResult(InternalAimpObject->GetFileAttrs(str, fattr));

        if (result == AimpActionResult::OK)
        {
            atr.TimeCreation = fattr->TimeCreation;
            atr.TimeLastAccess = fattr->TimeLastAccess;
            atr.TimeLastWrite = fattr->TimeLastWrite;
            atr.Attributes = static_cast<IO::FileAttributes>(fattr->Attributes);
            attr = atr;
        }
    }
    finally
    {
        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return result;
}

AimpActionResult AimpFileSystemCommandFileInfo::GetFileSize(String^ file, long long% size)
{
    IAIMPString* str = nullptr;
    size = 0;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        str = AimpConverter::ToAimpString(file);
        INT64* fSize = 0;
        result = CheckResult(InternalAimpObject->GetFileSize(str, fSize));
        if (result == AimpActionResult::OK)
        {
            size = reinterpret_cast<long long>(fSize);
        }
    }
    finally
    {
        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return result;
}

AimpActionResult AimpFileSystemCommandFileInfo::IsFileExists(String^ file)
{
    IAIMPString* str = nullptr;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        str = AimpConverter::ToAimpString(file);
        result = CheckResult(InternalAimpObject->IsFileExists(str));
    }
    finally
    {
        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return result;
}
