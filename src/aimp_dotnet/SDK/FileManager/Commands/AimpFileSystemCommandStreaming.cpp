#include "Stdafx.h"
#include "AimpFileSystemCommandStreaming.h"

using namespace AIMP::SDK;
using namespace Objects;

AimpFileSystemCommandStreaming::AimpFileSystemCommandStreaming(IAIMPFileSystemCommandStreaming* aimpObject) : AimpObject(aimpObject)
{ }

IAimpStream^ AimpFileSystemCommandStreaming::CreateStream(String^ fileName, FileStreamingType flags, long long offset, long long size)
{
    auto str = AimpConverter::ToAimpString(fileName);

    try
    {
        IAIMPStream* aimpStream = nullptr;
        auto result = CheckResult(InternalAimpObject->CreateStream(str, offset, size, DWORD(flags), reinterpret_cast<IAIMPStream**>(&aimpStream)));
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

