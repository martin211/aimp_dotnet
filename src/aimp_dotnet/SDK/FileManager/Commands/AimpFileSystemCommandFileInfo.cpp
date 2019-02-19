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
#include "AimpFileSystemCommandFileInfo.h"

using namespace AIMP::SDK;
using namespace Objects;

AimpFileSystemCommandFileInfo::AimpFileSystemCommandFileInfo(IAIMPFileSystemCommandFileInfo* aimpObject) : AimpObject(aimpObject)
{}

AimpActionResult AimpFileSystemCommandFileInfo::GetFileAttrs(IAimpString^ file, AimpFileAttributes% attr)
{
    // TODO: Complete it
    //IAIMPString *str = AimpConverter::ToAimpString(file);
    attr = AimpFileAttributes();

    //try
    //{
    //    TAIMPFileAttributes *fattr = nullptr;
    //    AimpActionResult result = CheckResult(_aimpObject->GetFileAttrs(str, fattr));
    //    return result;
    //}
    //finally
    //{
    //    if (str != nullptr)
    //    {
    //        str->Release();
    //        str = nullptr;
    //    }
    //}

    return AimpActionResult::Fail;
}

AimpActionResult AimpFileSystemCommandFileInfo::GetFileSize(IAimpString^ file, long long% size)
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

AimpActionResult AimpFileSystemCommandFileInfo::IsFileExists(IAimpString ^file)
{
    // TODO: Complete it
    IAIMPString *str = nullptr;
    try
    {
        //str = AimpConverter::ToAimpString(file);
        //return CheckResult(_aimpObject->IsFileExists(str));

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
