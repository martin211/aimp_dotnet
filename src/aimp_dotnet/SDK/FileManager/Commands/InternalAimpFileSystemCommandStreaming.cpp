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

#include "Stdafx.h"
#include "InternalAimpFileSystemCommandStreaming.h"

using namespace AIMP::SDK;

InternalAimpFileSystemCommandStreaming::InternalAimpFileSystemCommandStreaming(gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCommandStreaming^> instance)
{
    _instance = instance;
}

HRESULT WINAPI InternalAimpFileSystemCommandStreaming::CreateStream(IAIMPString* FileName, const INT64 Offset, const INT64 Size, DWORD Flags, IAIMPStream** Stream)
{
    AimpStream^ aimpStream = nullptr;
    System::IO::Stream^ stream = nullptr;
    AimpActionResult res = _instance->CreateStream(AIMP::SDK::AimpConverter::ToManagedString(FileName), (FileStreamingType)Flags, Offset, Size, %*stream);
    if (res == AimpActionResult::Ok && stream != nullptr)
    {

    }

    return (HRESULT)res;
}

ULONG WINAPI InternalAimpFileSystemCommandStreaming::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI InternalAimpFileSystemCommandStreaming::Release(void)
{
    return Base::Release();
}

HRESULT WINAPI InternalAimpFileSystemCommandStreaming::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPFileSystemCommandStreaming)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = NULL;
    return res;
}
