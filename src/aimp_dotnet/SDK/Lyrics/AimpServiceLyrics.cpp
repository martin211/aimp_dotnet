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

#include "Stdafx.h"
#include "AimpServiceLyrics.h"
#include "SDK/FileManager/AimpFileInfo.h"
#include "AimpLyrics.h"

using namespace AIMP::SDK;

void AimpServiceLyrics::OnAimpServiceLyricsReceive(IAIMPLyrics* lyrics, void* userData)
{
    auto l = gcnew AimpLyrics(lyrics);
    // TODO add user data
    LyricsReceive(l, nullptr);
}

AimpServiceLyrics::AimpServiceLyrics(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceLyrics>(core)
{
}

AimpServiceLyrics::~AimpServiceLyrics()
{
    delete _callBack;
}

AimpActionResult AimpServiceLyrics::Get(IAimpFileInfo^ fileInfo, LyricsFlags flags, Object^ userData, IntPtr% taskId)
{
    IAIMPServiceLyrics* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    taskId = IntPtr(0);

    try
    {
        result = GetService(IID_IAIMPServiceLyrics, &service);
        if (result == AimpActionResult::Ok && service != nullptr)
        {
            _callBack = gcnew OnAimpServiceLyricsReceiveCallback(
                this, &AIMP::AimpServiceLyrics::OnAimpServiceLyricsReceive);
            IntPtr procPtr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_callBack);
            void** task = nullptr;

            result = CheckResult(service->Get(
                static_cast<AimpFileInfo^>(fileInfo)->InternalAimpObject,
                (DWORD)flags,
                (TAIMPServiceLyricsReceiveProc(_stdcall *))procPtr.ToPointer(),
                reinterpret_cast<void*>(&userData),
                task
            ));

            if (result == AimpActionResult::Ok)
            {
                taskId = IntPtr(task);
            }
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return result;
}

AimpActionResult AimpServiceLyrics::Cancel(IntPtr taskId, LyricsFlags flags)
{
    IAIMPServiceLyrics* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        result = GetService(IID_IAIMPServiceLyrics, &service);
        if (result == AimpActionResult::Ok && service != nullptr)
        {
            result = CheckResult(service->Cancel(static_cast<void**>(taskId.ToPointer()), (DWORD)flags));
        }

        return result;
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return result;
}

void AimpServiceLyrics::LyricsReceive::raise(IAimpLyrics^ lyrics, Object^ userData)
{
    if (_eventCallBack != nullptr)
    {
        _eventCallBack(lyrics, userData);
    }
}

void AimpServiceLyrics::LyricsReceive::remove(AimpServiceLyricsReceive^ handler)
{
    delete _eventCallBack;
    _eventCallBack = nullptr;
}

void AimpServiceLyrics::LyricsReceive::add(AimpServiceLyricsReceive^ handler)
{
    if (_eventCallBack == nullptr)
    {
        _eventCallBack = static_cast<AimpServiceLyricsReceive^>(Delegate::Combine(this->_eventCallBack, handler));
    }
}
