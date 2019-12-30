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

#include "stdafx.h"
#include "AimpStream.h"

using namespace AIMP::SDK;

AimpStream::~AimpStream()
{
    this->!AimpStream();
}

AimpStream::!AimpStream()
{
    if (InternalAimpObject != nullptr)
    {
        try
        {
            //InternalAimpObject->Release();
        }
        catch (const std::exception& e)
        {
            System::Diagnostics::Debugger::Break();
        }
    }
}

AimpStream::AimpStream(IAIMPStream* aimpObject)
{
    _aimpObject = aimpObject;
}

long long AimpStream::GetSize()
{
    return InternalAimpObject->GetSize();
}

AimpActionResult AimpStream::SetSize(long long value)
{
    return CheckResult(InternalAimpObject->SetSize(value));
}

long long AimpStream::GetPosition()
{
    return InternalAimpObject->GetPosition();
}

AimpActionResult AimpStream::Seek(long long offset, System::IO::SeekOrigin mode)
{
    return CheckResult(InternalAimpObject->Seek(offset, (int)mode));
}

int AimpStream::Read(array<unsigned char, 1>^ buffer, int count)
{
    unsigned char* buf = new unsigned char[count];
    int read = InternalAimpObject->Read(buf, (unsigned int)count);

    for (int i = 0; i < read; i++)
    {
        buffer[i] = buf[i];
    }

    return read;
}

AimpActionResult AimpStream::Write(array<unsigned char, 1>^ buffer, int count, int% writen)
{
    unsigned int writenCount;
    writen = 0;

    pin_ptr<unsigned char> buff = &buffer[0];
    AimpActionResult res = CheckResult(InternalAimpObject->Write(buff, count, &writenCount));
    writen = writenCount;
    return res;
}
