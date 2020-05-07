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
#include "AimpFileSystemCommandOpenFileFolder.h"

using namespace AIMP::SDK;
using namespace Objects;

AimpFileSystemCommandOpenFileFolder::AimpFileSystemCommandOpenFileFolder(
    IAIMPFileSystemCommandOpenFileFolder* aimpObject) : AimpObject(aimpObject)
{
}

ActionResultType AimpFileSystemCommandOpenFileFolder::CanProcess(String^ file)
{
    auto str = AimpConverter::ToAimpString(file);
    auto result = CheckResult(InternalAimpObject->CanProcess(str));
    str->Release();
    str = nullptr;
    return result;
}

ActionResultType AimpFileSystemCommandOpenFileFolder::Process(String^ file)
{
    auto str = AimpConverter::ToAimpString(file);
    auto result = CheckResult(InternalAimpObject->Process(str));
    str->Release();
    str = nullptr;
    return result;
}
