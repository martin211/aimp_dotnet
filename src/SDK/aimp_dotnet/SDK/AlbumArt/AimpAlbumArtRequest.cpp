// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpAlbumArtRequest.h"

#include "SDK/Objects/AimpImageContainer.h"

using namespace AIMP::SDK;

AimpAlbumArtRequest::AimpAlbumArtRequest(IAIMPAlbumArtRequest* properties) : AimpObject<IAIMPAlbumArtRequest>(properties) {
}

bool AimpAlbumArtRequest::FindInFiles::get() {
    int val = 0;
    _aimpObject->GetValueAsInt32(AIMP_ALBUMART_REQUEST_PROPID_FIND_IN_FILES, &val);
    return val != 0;
}

void AimpAlbumArtRequest::FindInFiles::set(bool value) {
    _aimpObject->SetValueAsInt32(AIMP_ALBUMART_REQUEST_PROPID_FIND_IN_FILES, value ? 1 : 0);
}

bool AimpAlbumArtRequest::FindInInternet::get() {
    int val = 0;
    _aimpObject->GetValueAsInt32(AIMP_ALBUMART_REQUEST_PROPID_FIND_IN_INTERNET, &val);
    return val != 0;
}

void AimpAlbumArtRequest::FindInInternet::set(bool value) {
    _aimpObject->SetValueAsInt32(AIMP_ALBUMART_REQUEST_PROPID_FIND_IN_INTERNET, value ? 1 : 0);
}

array<String^>^ AimpAlbumArtRequest::FindInFileMasks::get() {
    IAIMPString* str;
    _aimpObject->GetValueAsObject(AIMP_ALBUMART_REQUEST_PROPID_FIND_IN_FILES_MASKS, IID_IAIMPString,
                                  reinterpret_cast<void**>(&str));
    String^ result = gcnew String(str->GetData());
    RELEASE(str)
    return result->Split(gcnew array<WCHAR>{';'}, StringSplitOptions::RemoveEmptyEntries);
}

void AimpAlbumArtRequest::FindInFileMasks::set(array<String^>^ value) {
    auto str = String::Empty;
    for (int i = 0; i < value->Length; i++) {
        str += value[i] + ";";
    }
    _aimpObject->SetValueAsObject(AIMP_ALBUMART_REQUEST_PROPID_FIND_IN_FILES_MASKS, AimpConverter::ToAimpString(str));
}

array<String^>^ AimpAlbumArtRequest::FindInFileExtensions::get() {
    IAIMPString* str;
    _aimpObject->GetValueAsObject(AIMP_ALBUMART_REQUEST_PROPID_FIND_IN_FILES_EXTS, IID_IAIMPString,
                                  reinterpret_cast<void**>(&str));
    auto result = gcnew String(str->GetData());
    RELEASE(str)
    return result->Split(gcnew array<WCHAR>{';'}, StringSplitOptions::RemoveEmptyEntries);
}

void AimpAlbumArtRequest::FindInFileExtensions::set(array<String^>^ value) {
    auto str = String::Empty;
    for (int i = 0; i < value->Length; i++) {
        str += value[i] + ";";
    }
    auto s = AimpConverter::ToAimpString(str);
    _aimpObject->SetValueAsObject(AIMP_ALBUMART_REQUEST_PROPID_FIND_IN_FILES_EXTS, s);
    RELEASE(s)
}

int AimpAlbumArtRequest::FindInInternetMaxFileSize::get() {
    int val = 0;
    _aimpObject->GetValueAsInt32(AIMP_ALBUMART_REQUEST_PROPID_FIND_IN_INTERNET_MAX_FILE_SIZE, &val);
    return val;
}

void AimpAlbumArtRequest::FindInInternetMaxFileSize::set(int value) {
    _aimpObject->SetValueAsInt32(AIMP_ALBUMART_REQUEST_PROPID_FIND_IN_INTERNET_MAX_FILE_SIZE, value);
}

bool AimpAlbumArtRequest::FindInTags::get() {
    int val = 0;
    _aimpObject->GetValueAsInt32(AIMP_ALBUMART_REQUEST_PROPID_FIND_IN_TAGS, &val);
    return val != 0;
}

void AimpAlbumArtRequest::FindInTags::set(bool value) {
    _aimpObject->SetValueAsInt32(AIMP_ALBUMART_REQUEST_PROPID_FIND_IN_TAGS, value ? 1 : 0);
}

AimpActionResult<IAimpImageContainer^>^ AimpAlbumArtRequest::CacheGet(String^ key) {
    if (_aimpObject == nullptr) {
        return gcnew AimpActionResult<IAimpImageContainer^>(ActionResultType::NotImplemented);
    }

    IAIMPString* str = AimpConverter::ToAimpString(key);
    IAIMPImageContainer* container = nullptr;
    auto res = ActionResultType::Fail;

    try {
        res = Utils::CheckResult(_aimpObject->CacheGet(str, &container));
        if (res == ActionResultType::OK) {
            return gcnew AimpActionResult<IAimpImageContainer^>(res, gcnew AimpImageContainer(container));
        }
    }
    finally {
        RELEASE(str)
    }

    return gcnew AimpActionResult<IAimpImageContainer^>(res);
}

AimpActionResult^ AimpAlbumArtRequest::CachePut(String^ key, IAimpImageContainer^ image) {
    auto res = ActionResultType::Fail;
    IAIMPString* str = AimpConverter::ToAimpString(key);

    try {
        res = Utils::CheckResult(_aimpObject->CachePut(str, safe_cast<AimpImageContainer^>(image)->InternalAimpObject));
    }
    finally {
        RELEASE(str)
    }

    return gcnew AimpActionResult(res);
}

AimpActionResult<IAimpImageContainer^>^ AimpAlbumArtRequest::Download(String^ url) {
    auto res = ActionResultType::Fail;
    IAIMPString* str = AimpConverter::ToAimpString(url);
    IAIMPImageContainer* container = nullptr;

    try {
        res = Utils::CheckResult(_aimpObject->Download(str, &container));
        if (res == ActionResultType::OK) {
            return gcnew AimpActionResult<IAimpImageContainer^>(res, gcnew AimpImageContainer(container));
        }
    }
    finally {
        RELEASE(str)
    }

    return gcnew AimpActionResult<IAimpImageContainer^>(res);
}

bool AimpAlbumArtRequest::IsCanceled() {
    return _aimpObject->IsCanceled();
}
