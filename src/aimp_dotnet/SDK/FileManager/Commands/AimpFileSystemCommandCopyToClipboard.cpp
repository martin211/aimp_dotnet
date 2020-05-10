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
#include "AimpFileSystemCommandCopyToClipboard.h"

using namespace AIMP::SDK;
using namespace Objects;

AimpFileSystemCommandCopyToClipboard::AimpFileSystemCommandCopyToClipboard(
    IAIMPFileSystemCommandCopyToClipboard* aimpObject) : AimpObject(aimpObject)
{
}

VoidResult AimpFileSystemCommandCopyToClipboard::CopyToClipboard(List<String^>^ files)
{
    auto collection = AimpConverter::ToAimpObjectList(files);
    auto result = CheckResult(InternalAimpObject->CopyToClipboard(collection));
    return VOID_RESULT(result);
}
