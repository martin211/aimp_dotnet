// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpFileSystemCommandCopyToClipboard.h"

using namespace AIMP::SDK;
using namespace Objects;

AimpFileSystemCommandCopyToClipboard::AimpFileSystemCommandCopyToClipboard(
    IAIMPFileSystemCommandCopyToClipboard* aimpObject) : AimpObject(aimpObject) {
}

ActionResult AimpFileSystemCommandCopyToClipboard::CopyToClipboard(List<String^>^ files) {
    auto collection = AimpConverter::ToAimpObjectList(files);
    auto result = CheckResult(InternalAimpObject->CopyToClipboard(collection));
    return ACTION_RESULT(result);
}
