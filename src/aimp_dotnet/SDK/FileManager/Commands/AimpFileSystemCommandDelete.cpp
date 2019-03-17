#include "Stdafx.h"
#include "AimpFileSystemCommandDelete.h"

using namespace AIMP::SDK;
using namespace Objects;

AimpFileSystemCommandDelete::AimpFileSystemCommandDelete(IAIMPFileSystemCommandDelete* aimpObject) : AimpObject(aimpObject)
{}

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
