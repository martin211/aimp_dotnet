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
#include "AimpPlaylistPreimageFolders.h"

using namespace AIMP::SDK;

AimpPlaylistPreimageFolders::AimpPlaylistPreimageFolders(IAIMPPlaylistPreimageFolders* aimpObject)
    : AimpPlaylistPreimage(aimpObject)
{
}

ActionResultType AimpPlaylistPreimageFolders::ItemsAdd(String^ path, bool recursive)
{
    ActionResultType res = ActionResultType::Fail;
    IAIMPString* str = AimpConverter::ToAimpString(path);

    IAIMPPlaylistPreimageFolders* folders = static_cast<IAIMPPlaylistPreimageFolders*>(InternalAimpObject);
    if (folders != nullptr)
    {
        res = CheckResult(folders->ItemsAdd(str, BOOL(recursive)));
    }

    str->Release();
    return res;
}

ActionResultType AimpPlaylistPreimageFolders::ItemsDelete(int index)
{
    return CheckResult(static_cast<IAIMPPlaylistPreimageFolders*>(InternalAimpObject)->ItemsDelete(index));
}

ActionResultType AimpPlaylistPreimageFolders::ItemsDeleteAll()
{
    return CheckResult(static_cast<IAIMPPlaylistPreimageFolders*>(InternalAimpObject)->ItemsDeleteAll());
}

ActionResultType AimpPlaylistPreimageFolders::ItemsGet(int index, String^% path, bool% recursive)
{
    IAIMPString* str = nullptr;
    BOOL* b = nullptr;
    ActionResultType res = CheckResult(
        static_cast<IAIMPPlaylistPreimageFolders*>(InternalAimpObject)->ItemsGet(index, str, b));
    path = AimpConverter::ToManagedString(str);
    recursive = b;
    str->Release();
    return res;
}

int AimpPlaylistPreimageFolders::ItemsGetCount()
{
    return static_cast<IAIMPPlaylistPreimageFolders*>(InternalAimpObject)->ItemsGetCount();
}
