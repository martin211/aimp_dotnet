// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "stdafx.h"
#include "AimpStream.h"

AIMP::SDK::AimpStream::~AimpStream()
{
    this->!AimpStream();
}

AIMP::SDK::AimpStream::!AimpStream()
{
    _aimpObject->Release();
}

AIMP::SDK::AimpStream::AimpStream(IAIMPStream *aimpObject)
{
    _aimpObject = aimpObject;
}

long long AIMP::SDK::AimpStream::GetSize()
{
    return _aimpObject->GetSize();
}

AIMP::SDK::AimpActionResult AIMP::SDK::AimpStream::SetSize(long long value)
{
    return CheckResult(_aimpObject->SetSize(value));
}

long long AIMP::SDK::AimpStream::GetPosition()
{
    return _aimpObject->GetPosition();
}

AIMP::SDK::AimpActionResult AIMP::SDK::AimpStream::Seek(long long offset, System::IO::SeekOrigin mode)
{
    return CheckResult(_aimpObject->Seek(offset, (int)mode));
}

int AIMP::SDK::AimpStream::Read(array<unsigned char, 1> ^buffer, int count)
{
    unsigned char *buf = new unsigned char[count];
    int read = _aimpObject->Read(buf, (unsigned int)count);

    for (int i = 0; i < read; i++)
    {
        buffer[i] = buf[i];
    }

    return read;
}

AIMP::SDK::AimpActionResult AIMP::SDK::AimpStream::Write(array<unsigned char, 1> ^buffer, int count, int %writen)
{
    return AIMP::SDK::AimpActionResult();
}
