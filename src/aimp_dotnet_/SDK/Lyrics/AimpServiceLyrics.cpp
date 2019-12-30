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

AimpServiceLyrics::AimpServiceLyrics(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceLyrics>(core)
{
}

AimpServiceLyrics::~AimpServiceLyrics()
{
    delete _callBack;
}

AimpActionResult AimpServiceLyrics::Get(IAimpFileInfo^ fileInfo, LyricsFlags flags, Object^ userData, IntPtr% taskId)
{
    IAIMPServiceLyrics* service = GetAimpService();
    AimpActionResult result = AimpActionResult::Fail;
    taskId = IntPtr(0);

    try
    {
        if (service != nullptr)
        {
            _callBack = gcnew OnAimpServiceLyricsReceiveCallback(this, &AIMP::AimpServiceLyrics::OnAimpServiceLyricsReceive);
            IntPtr procPtr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_callBack);
            void** task = nullptr;

            result = CheckResult(service->Get(
                static_cast<AimpFileInfo^>(fileInfo)->InternalAimpObject,
                static_cast<DWORD>(flags),
                static_cast<TAIMPServiceLyricsReceiveProc(_stdcall *)>(procPtr.ToPointer()),
                reinterpret_cast<void*>(&userData),
                task
            ));

            if (result == AimpActionResult::OK)
            {
                taskId = IntPtr(task);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return result;
}

AimpActionResult AimpServiceLyrics::Cancel(IntPtr taskId, LyricsFlags flags)
{
    IAIMPServiceLyrics* service = GetAimpService();
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        if (service != nullptr)
        {
            result = CheckResult(service->Cancel(static_cast<void**>(taskId.ToPointer()), static_cast<DWORD>(flags)));
        }

        return result;
    }
    finally
    {
        ReleaseObject(service);
    }
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

IAIMPServiceLyrics* AimpServiceLyrics::GetAimpService()
{
    IAIMPServiceLyrics* service = nullptr;
    GetService(IID_IAIMPServiceLyrics, &service);
    return service;
}
