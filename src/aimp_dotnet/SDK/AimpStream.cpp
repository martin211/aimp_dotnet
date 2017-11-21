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

using namespace AIMP::SDK;

AimpStream::~AimpStream()
{
    this->!AimpStream();
}

AimpStream::!AimpStream()
{
    if (_aimpObject != nullptr)
    {
        _aimpObject->Release();
    }
}

AimpStream::AimpStream(IAIMPStream *aimpObject)
{
    _aimpObject = aimpObject;
}

long long AimpStream::GetSize()
{
    return _aimpObject->GetSize();
}

AimpActionResult AimpStream::SetSize(long long value)
{
    return CheckResult(_aimpObject->SetSize(value));
}

long long AimpStream::GetPosition()
{
    return _aimpObject->GetPosition();
}

AimpActionResult AimpStream::Seek(long long offset, System::IO::SeekOrigin mode)
{
    return CheckResult(_aimpObject->Seek(offset, (int)mode));
}

int AimpStream::Read(array<unsigned char, 1> ^buffer, int count)
{
    unsigned char *buf = new unsigned char[count];
    int read = _aimpObject->Read(buf, (unsigned int)count);

    for (int i = 0; i < read; i++)
    {
        buffer[i] = buf[i];
    }

    return read;
}

AimpActionResult AimpStream::Write(array<unsigned char, 1> ^buffer, int count, int %writen)
{
    unsigned int writenCount;
    writen = 0;

    pin_ptr<unsigned char>buff = &buffer[0];
    AimpActionResult res = CheckResult(InternalAimpObject->Write(buff, count, &writenCount));
    writen = writenCount;
    return res;
}
