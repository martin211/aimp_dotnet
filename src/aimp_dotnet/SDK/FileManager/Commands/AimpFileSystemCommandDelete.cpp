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
#include "AimpFileSystemCommandDelete.h"

using namespace AIMP::SDK;
using namespace Objects;

AimpFileSystemCommandDelete::
AimpFileSystemCommandDelete(IAIMPFileSystemCommandDelete* aimpObject) : AimpObject(aimpObject)
{
}

AimpActionResult AimpFileSystemCommandDelete::CanProcess(String^ file)
{
    auto str = AimpConverter::ToAimpString(file);
    auto result = CheckResult(InternalAimpObject->CanProcess(str));
    str->Release();
    str = nullptr;
    return result;
}

AimpActionResult AimpFileSystemCommandDelete::Process(String^ file)
{
    auto str = AimpConverter::ToAimpString(file);
    auto result = CheckResult(InternalAimpObject->Process(str));
    str->Release();
    str = nullptr;
    return result;
}
