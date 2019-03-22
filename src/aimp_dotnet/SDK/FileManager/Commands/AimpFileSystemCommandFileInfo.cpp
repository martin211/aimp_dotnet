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
    // TODO: Complete it
    //auto str = AimpConverter::ToAimpString(file);
    AimpActionResult result = AimpActionResult::Fail;
    //attr = AimpFileAttributes();

    try
    {
        //TAIMPFileAttributes* fattr = nullptr;
        //AimpActionResult result = CheckResult(InternalAimpObject->GetFileAttrs(str, fattr));
        //if (result == AimpActionResult::OK)
        //{
        //    auto atr = AimpFileAttributes();
        //    //atr.TimeCreation = gcnew System::DateTime(fattr->TimeCreation);
        //    attr = atr;
        //}
    }
    finally
    {
        //if (str != nullptr)
        //{
        //    str->Release();
        //    str = nullptr;
        //}
    }

    return result;
}

AimpActionResult AimpFileSystemCommandFileInfo::GetFileSize(String^ file, long long% size)
{
    // TODO: Complete it

    IAIMPString* str = nullptr;
    size = 0;

    try
    {
        //str = AimpConverter::ToAimpString(file);
        //INT64 *fSize = 0;
        //AimpActionResult result = CheckResult(_aimpObject->GetFileSize(str, fSize));
        //if (result == AimpActionResult::OK)
        //{
        //    size = (long long)fSize;
        //}

        return AimpActionResult::OK;
    }
    finally
    {
        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }
}

AimpActionResult AimpFileSystemCommandFileInfo::IsFileExists(String^ file)
{
    // TODO: Complete it
    //IAIMPString *str = nullptr;
    AimpActionResult result = AimpActionResult::Fail;

    //try
    //{
    //    //str = AimpConverter::ToAimpString(file);
    //    //return CheckResult(_aimpObject->IsFileExists(str));

    //    return AimpActionResult::OK;
    //}
    //finally
    //{
    //    //if (str != nullptr)
    //    //{
    //    //    str->Release();
    //    //    str = nullptr;
    //    //}
    //}

    return result;
}
