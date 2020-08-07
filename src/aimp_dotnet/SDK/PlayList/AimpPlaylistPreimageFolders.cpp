// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpPlaylistPreimageFolders.h"

using namespace AIMP::SDK;

AimpPlaylistPreimageFolders::AimpPlaylistPreimageFolders(IAIMPPlaylistPreimageFolders* aimpObject)
    : AimpPlaylistPreimage(aimpObject) {
}

ActionResult AimpPlaylistPreimageFolders::ItemsAdd(String^ path, bool recursive) {
    ActionResultType res = ActionResultType::Fail;
    IAIMPString* str = AimpConverter::ToAimpString(path);

    IAIMPPlaylistPreimageFolders* folders = static_cast<IAIMPPlaylistPreimageFolders*>(InternalAimpObject);
    if (folders != nullptr) {
        res = CheckResult(folders->ItemsAdd(str, BOOL(recursive)));
    }

    str->Release();
    return ACTION_RESULT(res);
}

ActionResult AimpPlaylistPreimageFolders::ItemsDelete(int index) {
    return ACTION_RESULT(CheckResult(static_cast<IAIMPPlaylistPreimageFolders*>(InternalAimpObject)->ItemsDelete(index)));
}

ActionResult AimpPlaylistPreimageFolders::ItemsDeleteAll() {
    return ACTION_RESULT(CheckResult(static_cast<IAIMPPlaylistPreimageFolders*>(InternalAimpObject)->ItemsDeleteAll()));
}

AimpActionResult<String^, bool>^ AimpPlaylistPreimageFolders::ItemsGet(int index) {
    IAIMPString* str = nullptr;
    BOOL* b = nullptr;
    ActionResultType res = CheckResult(
        static_cast<IAIMPPlaylistPreimageFolders*>(InternalAimpObject)->ItemsGet(index, str, b));
    auto path = AimpConverter::ToManagedString(str);
    str->Release();
    return gcnew AimpActionResult<String^, bool>(res, path, b);
}

int AimpPlaylistPreimageFolders::ItemsGetCount() {
    return static_cast<IAIMPPlaylistPreimageFolders*>(InternalAimpObject)->ItemsGetCount();
}
