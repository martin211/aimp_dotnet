#include "Stdafx.h"
#include "AimpFileSystemCommandOpenFileFolder.h"

using namespace AIMP::SDK;
using namespace Objects;

AimpFileSystemCommandOpenFileFolder::AimpFileSystemCommandOpenFileFolder(IAIMPFileSystemCommandOpenFileFolder* aimpObject) : AimpObject(aimpObject)
{ }

AimpActionResult AimpFileSystemCommandOpenFileFolder::CanProcess(String^ file)
{
    auto str = AimpConverter::ToAimpString(file);
    auto result = CheckResult(InternalAimpObject->CanProcess(str));
    str->Release();
    str = nullptr;
    return result;
}

AimpActionResult AimpFileSystemCommandOpenFileFolder::Process(String^ file)
{
    auto str = AimpConverter::ToAimpString(file);
    auto result = CheckResult(InternalAimpObject->Process(str));
    str->Release();
    str = nullptr;
    return result;
}
