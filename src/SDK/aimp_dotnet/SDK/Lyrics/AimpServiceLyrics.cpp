// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceLyrics.h"
#include "SDK/FileManager/AimpFileInfo.h"
#include "AimpLyrics.h"

using namespace AIMP::SDK;

void AimpServiceLyrics::OnAimpServiceLyricsReceive(IAIMPLyrics* lyrics, void* userData) {
    AimpLyrics^ l = nullptr;
    if (lyrics != nullptr) {
        l = gcnew AimpLyrics(lyrics);
    }

    // TODO add user data
    LyricsReceive(l, nullptr);
}

AimpServiceLyrics::AimpServiceLyrics(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceLyrics>(core) {
}

AimpServiceLyrics::~AimpServiceLyrics() {
    delete _callBack;
}

AimpActionResult<IntPtr>^ AimpServiceLyrics::Get(IAimpFileInfo^ fileInfo, LyricsFlags flags, String^ userData) {
    IAIMPServiceLyrics* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IntPtr taskId = IntPtr(0);
    IAIMPString* data = nullptr;

    try {
        if (service != nullptr) {
            if (String::IsNullOrWhiteSpace(userData)) {
                data = AimpConverter::ToAimpString(userData);
            }

            _callBack = gcnew OnAimpServiceLyricsReceiveCallback(this, &AimpServiceLyrics::OnAimpServiceLyricsReceive);
            IntPtr procPtr = InteropServices::Marshal::GetFunctionPointerForDelegate(_callBack);
            void** task = nullptr;

            result = CheckResult(service->Get(
                static_cast<AimpFileInfo^>(fileInfo)->InternalAimpObject,
                static_cast<DWORD>(flags),
                static_cast<TAIMPServiceLyricsReceiveProc(_stdcall*)>(procPtr.ToPointer()),
                data,
                task
            ));

            if (result == ActionResultType::OK) {
                taskId = IntPtr(task);
            }
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<IntPtr>(result, taskId);
}

ActionResult AimpServiceLyrics::Cancel(IntPtr taskId, LyricsFlags flags) {
    IAIMPServiceLyrics* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            result = CheckResult(service->Cancel(taskId.ToPointer(), static_cast<DWORD>(flags)));
        }

        return ACTION_RESULT(result);
    }
    finally {
        ReleaseObject(service);
    }
}

void AimpServiceLyrics::LyricsReceive::raise(IAimpLyrics^ lyrics, String^ userData) {
    if (_eventCallBack != nullptr) {
        _eventCallBack(lyrics, userData);
    }
}

void AimpServiceLyrics::LyricsReceive::remove(AimpServiceLyricsReceive^ handler) {
    delete _eventCallBack;
    _eventCallBack = nullptr;
}

void AimpServiceLyrics::LyricsReceive::add(AimpServiceLyricsReceive^ handler) {
    if (_eventCallBack == nullptr) {
        _eventCallBack = static_cast<AimpServiceLyricsReceive^>(Delegate::Combine(this->_eventCallBack, handler));
    }
}

IAIMPServiceLyrics* AimpServiceLyrics::GetAimpService() {
    IAIMPServiceLyrics* service = nullptr;
    GetService(IID_IAIMPServiceLyrics, &service);
    return service;
}
