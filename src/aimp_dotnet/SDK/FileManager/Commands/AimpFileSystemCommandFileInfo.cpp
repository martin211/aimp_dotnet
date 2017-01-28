/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#include "Stdafx.h"
#include "AimpFileSystemCommandFileInfo.h"

using namespace AIMP::SDK;

AimpFileSystemCommandFileInfo::AimpFileSystemCommandFileInfo(IAIMPFileSystemCommandFileInfo *aimpObject) : AimpObject(aimpObject)
{}

AimpActionResult AimpFileSystemCommandFileInfo::GetFileAttrs(String ^file, AimpFileAttributes %attr)
{
    IAIMPString *str = AimpConverter::ToAimpString(file);
    try
    {
        TAIMPFileAttributes *fattr = NULL;
        AimpActionResult result = CheckResult(_aimpObject->GetFileAttrs(str, fattr));
        return result;
    }
    finally
    {
        if (str != NULL)
        {
            str->Release();
            str = NULL;
        }
    }
}

AimpActionResult AimpFileSystemCommandFileInfo::GetFileSize(String ^file, long long %size)
{
    IAIMPString *str = NULL;

    try
    {
        str = AimpConverter::ToAimpString(file);
        INT64 *fSize = 0;
        AimpActionResult result = CheckResult(_aimpObject->GetFileSize(str, fSize));
        if (result == AimpActionResult::Ok)
        {
            size = (long long)fSize;
        }

        return result;
    }
    finally
    {
        if (str != NULL)
        {
            str->Release();
            str = NULL;
        }
    }
}

AimpActionResult AimpFileSystemCommandFileInfo::IsFileExists(String ^file)
{
    IAIMPString *str = NULL;
    try
    {
        str = AimpConverter::ToAimpString(file);
        return CheckResult(_aimpObject->IsFileExists(str));
    }
    finally
    {
        if (str != NULL)
        {
            str->Release();
            str = NULL;
        }
    }
}
