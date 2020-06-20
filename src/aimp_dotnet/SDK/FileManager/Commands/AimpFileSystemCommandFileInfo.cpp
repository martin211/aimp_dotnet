// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpFileSystemCommandFileInfo.h"

using namespace AIMP::SDK;
using namespace Objects;

AimpFileSystemCommandFileInfo::
AimpFileSystemCommandFileInfo(IAIMPFileSystemCommandFileInfo* aimpObject) : AimpObject(aimpObject)
{
}

AimpActionResult<AimpFileAttributes>^ AimpFileSystemCommandFileInfo::GetFileAttrs(String^ file)
{
    auto str = AimpConverter::ToAimpString(file);
    auto result = ActionResultType::Fail;
    auto atr = AimpFileAttributes();

    try
    {
        TAIMPFileAttributes* fattr = nullptr;
        result = CheckResult(InternalAimpObject->GetFileAttrs(str, fattr));

        if (result == ActionResultType::OK)
        {
            atr.TimeCreation = fattr->TimeCreation;
            atr.TimeLastAccess = fattr->TimeLastAccess;
            atr.TimeLastWrite = fattr->TimeLastWrite;
            atr.Attributes = static_cast<IO::FileAttributes>(fattr->Attributes);
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

    return gcnew AimpActionResult<AimpFileAttributes>(result, atr);
}

LongResult AimpFileSystemCommandFileInfo::GetFileSize(String^ file)
{
    IAIMPString* str = nullptr;
    long long size = 0;
    ActionResultType result = ActionResultType::Fail;

    try
    {
        str = AimpConverter::ToAimpString(file);
        INT64* fSize = 0;
        result = CheckResult(InternalAimpObject->GetFileSize(str, fSize));
        if (result == ActionResultType::OK)
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

    return gcnew AimpActionResult<long long>(result, size);
}

VoidResult AimpFileSystemCommandFileInfo::IsFileExists(String^ file)
{
    IAIMPString* str = nullptr;
    ActionResultType result = ActionResultType::Fail;

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

    return VOID_RESULT(result);
}
