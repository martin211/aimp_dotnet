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
#include "AimpPlaylistPreimageFolders.h"

using namespace AIMP::SDK;

AimpPlaylistPreimageFolders::AimpPlaylistPreimageFolders(IAIMPPlaylistPreimageFolders* aimpObject) 
: AimpPlaylistPreimage(aimpObject)
{
}

AimpActionResult AimpPlaylistPreimageFolders::ItemsAdd(String^ path, bool recursive)
{
    AimpActionResult res = AimpActionResult::Fail;
    IAIMPString* str = AimpConverter::ToAimpString(path);
    res = CheckResult(((IAIMPPlaylistPreimageFolders*)InternalAimpObject)->ItemsAdd(str, recursive));
    str->Release();
    return res;
}

AimpActionResult AimpPlaylistPreimageFolders::ItemsDelete(int index)
{
    return CheckResult(((IAIMPPlaylistPreimageFolders*)InternalAimpObject)->ItemsDelete(index));
}

AimpActionResult AimpPlaylistPreimageFolders::ItemsDeleteAll()
{
    return CheckResult(((IAIMPPlaylistPreimageFolders*)InternalAimpObject)->ItemsDeleteAll());
}

AimpActionResult AimpPlaylistPreimageFolders::ItemsGet(int index, String^% path, bool% recursive)
{
    IAIMPString *str = NULL;
    BOOL *b = NULL;
    AimpActionResult res = CheckResult(((IAIMPPlaylistPreimageFolders*)InternalAimpObject)->ItemsGet(index, str, b));
    path = AimpConverter::ToManagedString(str);
    recursive = b;
    str->Release();
    return res;
}

int AimpPlaylistPreimageFolders::ItemsGetCount()
{
    return ((IAIMPPlaylistPreimageFolders*)InternalAimpObject)->ItemsGetCount();
}
