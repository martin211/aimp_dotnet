//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpExtensionFileExpander.h"

#include "SDK/AimpObjectList.h"
#include "SDK/AimpProgressCallback.h"

InternalAimpExtensionFileExpander::InternalAimpExtensionFileExpander(gcroot<FileManager::Extensions::IAimpExtensionFileExpander^> managedInstance) {
    _managedInstance = managedInstance;
}

HRESULT InternalAimpExtensionFileExpander::Expand(IAIMPString* fileName, IAIMPObjectList** list, IAIMPProgressCallback* progressCallback) {
    const auto fn = AimpConverter::ToManagedString(fileName);
    AimpProgressCallback^ callBack = gcnew AimpProgressCallback(progressCallback);
    const auto result = _managedInstance->Expand(fn, callBack);
    if (result->ResultType == ActionResultType::OK) {
        *list = safe_cast<AimpObjectList<IAimpVirtualFile^>^>(result->Result)->AimpObject;
    }

    return static_cast<HRESULT>(result->ResultType);
}

HRESULT InternalAimpExtensionFileExpander::QueryInterface(const IID& riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionFileExpander) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}

ULONG InternalAimpExtensionFileExpander::AddRef() {
    return Base::AddRef();
}

ULONG InternalAimpExtensionFileExpander::Release() {
    return Base::Release();
}
