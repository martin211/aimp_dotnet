// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpMemoryStream.h"

AimpMemoryStream::AimpMemoryStream(IAIMPMemoryStream* aimpObject) : AimpStream(static_cast<IAIMPStream*>(aimpObject)) {
}

AimpActionResult<array<unsigned char>^>^ AimpMemoryStream::GetData() {
    const auto size = InternalAimpObject->GetSize();
    array<unsigned char>^ arr = gcnew array<unsigned char>(size);
    IAIMPMemoryStream* stream = static_cast<IAIMPMemoryStream*>(InternalAimpObject);
    byte* pointer = static_cast<byte*>(stream->GetData());

    for (int i = 0; i < size; i++) {
        arr[i] = pointer[i];
    }

    return gcnew AimpActionResult<array<unsigned char>^>(ActionResultType::OK, arr);
}
