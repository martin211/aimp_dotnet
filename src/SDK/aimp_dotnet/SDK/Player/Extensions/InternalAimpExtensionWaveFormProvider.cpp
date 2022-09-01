//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "stdafx.h"
#include "InternalAimpExtensionWaveFormProvider.h"

#include "SDK/Threading/AimpTaskOwner.h"

AimpWaveformPeakInfo::AimpWaveformPeakInfo(TAIMPWaveformPeakInfo* native) : _native(native) {
}

int AimpWaveformPeakInfo::MaxNegative::get() {
    return _native->MaxNegative;
}

void AimpWaveformPeakInfo::MaxNegative::set(int value) {
    _native->MaxNegative = value;
}

int AimpWaveformPeakInfo::MaxPositive::get() {
    return _native->MaxPositive;
}

void AimpWaveformPeakInfo::MaxPositive::set(int value) {
    _native->MaxPositive = value;
}

InternalAimpExtensionWaveFormProvider::InternalAimpExtensionWaveFormProvider(gcroot<IAimpExtensionWaveFormProvider^> managed) : _managed(managed) {
}

HRESULT InternalAimpExtensionWaveFormProvider::Calculate(IAIMPString* fileURI, IAIMPTaskOwner* taskOwner, PAIMPWaveformPeakInfo peaks, int peakCount) {
    auto peakList = gcnew List<Player::Objects::IAimpWaveformPeakInfo^>(peakCount);

    for (int i = 0; i <= peakCount; i++) {
        TAIMPWaveformPeakInfo* p = &peaks[i];
        peakList->Add(gcnew AimpWaveformPeakInfo(p));
    }

    const auto res = _managed->Calculate(AimpConverter::ToManagedString(fileURI), gcnew AimpTaskOwner(taskOwner), nullptr);

    return static_cast<HRESULT>(res->ResultType);
}

HRESULT InternalAimpExtensionWaveFormProvider::QueryInterface(const IID& riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionWaveformProvider) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}

ULONG InternalAimpExtensionWaveFormProvider::AddRef() {
    return Base::AddRef();
}

ULONG InternalAimpExtensionWaveFormProvider::Release() {
    return Base::Release();
}
