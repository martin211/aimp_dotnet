#include "Stdafx.h"
#include "AimpFileSystemCommandDropSource.h"

using namespace AIMP::SDK;
using namespace Objects;

AimpFileSystemCommandDropSource::AimpFileSystemCommandDropSource(IAIMPFileSystemCommandDropSource* aimpObject) : AimpObject(aimpObject)
{
}

IAimpStream^ AimpFileSystemCommandDropSource::CreateStream(String^ fileName)
{
    auto str = AimpConverter::ToAimpString(fileName);

    try
    {
        IAIMPStream* aimpStream = nullptr;
        auto result = CheckResult(InternalAimpObject->CreateStream(str, reinterpret_cast<IAIMPStream**>(&aimpStream)));
        if (result == AimpActionResult::OK && aimpStream != nullptr)
        {
            return gcnew AimpStream(aimpStream);
        }
    }
    finally
    {
        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return nullptr;
}

