// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpFileStream.h"
#include "SDK/AimpString.h"

AimpFileStream::AimpFileStream(IAIMPFileStream* aimpObject) : AimpStream(aimpObject) {
}

AimpActionResult<Clipping^>^ AimpFileStream::GetClipping() {
    IAIMPFileStream* stream = static_cast<IAIMPFileStream*>(InternalAimpObject);
    INT64* offset = new INT64();
    INT64* size = new INT64();
    const auto res = CheckResult(stream->GetClipping(offset, size));

    if (res == ActionResultType::OK) {
        return gcnew AimpActionResult<Clipping^>(
            res,
            gcnew Clipping(reinterpret_cast<int>(offset), reinterpret_cast<int>(size)));
    }

    return nullptr;
}

AimpActionResult<IAimpString^>^ AimpFileStream::GetFileName() {
    IAIMPFileStream* stream = static_cast<IAIMPFileStream*>(InternalAimpObject);
    IAIMPString* fn = nullptr;
    IAimpString^ result = nullptr;
    const auto res = CheckResult(stream->GetFileName(&fn));
    if (res == ActionResultType::OK) {
        result = gcnew AimpString(fn);
    }

    return gcnew AimpActionResult<IAimpString^>(res, result);
}
