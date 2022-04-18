// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpExtensionFileInfoProvider.h"
#include "SDK/FileManager/AimpFileInfo.h"

HRESULT WINAPI InternalAimpExtensionFileInfoProvider::GetFileInfo(IAIMPString* fileURI, IAIMPFileInfo* info) {
    IAimpFileInfo^ aimpFileInfo = gcnew AimpFileInfo(info);
    //IAimpString^ str = gcnew AimpString(fileURI);
    auto result = _managedInstance->GetFileInfo(AimpConverter::ToManagedString(fileURI), aimpFileInfo);
    info = static_cast<AimpFileInfo^>(aimpFileInfo)->InternalAimpObject;
    return HRESULT(result->ResultType);
}

HRESULT WINAPI InternalAimpExtensionFileInfoProvider::GetFileInfo(IAIMPStream* stream, IAIMPFileInfo* info) {
    IAimpFileInfo^ aimpFileInfo = gcnew AimpFileInfo(info);
    const auto result = _managedInstance->GetFileInfo(gcnew AimpStream(stream), aimpFileInfo);
    info = static_cast<AimpFileInfo^>(aimpFileInfo)->InternalAimpObject;
    return HRESULT(result->ResultType);
}

ULONG InternalAimpExtensionFileInfoProvider::AddRef() {
    return Base::AddRef();
}

ULONG InternalAimpExtensionFileInfoProvider::Release() {
    return Base::Release();
}

HRESULT InternalAimpExtensionFileInfoProvider::QueryInterface(const IID& riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionFileInfoProvider) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPExtensionFileInfoProviderEx) {
        *ppvObject = static_cast<IAIMPExtensionFileInfoProviderEx*>(this);
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}
