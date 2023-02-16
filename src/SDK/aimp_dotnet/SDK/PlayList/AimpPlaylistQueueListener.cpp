//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpPlaylistQueueListener.h"

using namespace AIMP::SDK;

AimpPlaylistQueueListener::AimpPlaylistQueueListener(gcroot<IPlayListQueueEventExecutor^> executor) {
    _executor = executor;
}

void WINAPI AimpPlaylistQueueListener::ContentChanged() {
    _executor->OnContentChanged();
}

void WINAPI AimpPlaylistQueueListener::StateChanged() {
    _executor->OnStateChanged();
}

HRESULT WINAPI AimpPlaylistQueueListener::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPPlaylistQueueListener) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}

ULONG WINAPI AimpPlaylistQueueListener::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI AimpPlaylistQueueListener::Release(void) {
    return Base::Release();
}
