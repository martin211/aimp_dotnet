//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpAlbumArtProvider2.h"
#include "SDK/AimpObjectList.h"
#include "SDK/AlbumArt/AimpAlbumArtRequest.h"

InternalAimpAlbumArtProvider2::InternalAimpAlbumArtProvider2(gcroot<MusicLibrary::Extension::IAimpAlbumArtProvider2^> instance) {
    _instance = instance;
}

HRESULT InternalAimpAlbumArtProvider2::Get(IAIMPObjectList* Fields, VARIANT* Values, IAIMPAlbumArtRequest* Request, IAIMPImageContainer** Image) {
    const auto filedList = gcnew AimpObjectList<String^>(Fields);

    array<Object^>^ values = gcnew array<Object^>(Fields->GetCount());
    VARIANT* val = static_cast<VARIANT*>(Values);
    VARIANT* varArr = Values;

    for (int i = 0; i < values->Length; i++)
    {
        values[i] = AimpConverter::FromVariant(Values[i].pvarVal);
    }

    return static_cast<HRESULT>(_instance->Get(filedList, values, gcnew AimpAlbumArtRequest(Request))->ResultType);
}

ULONG InternalAimpAlbumArtProvider2::AddRef() {
    return Base::AddRef();
}

ULONG InternalAimpAlbumArtProvider2::Release() {
    return Base::Release();
}

HRESULT InternalAimpAlbumArtProvider2::QueryInterface(const IID& riid, LPVOID* ppvObject) {
    return IUnknownInterfaceImpl<IAIMPMLAlbumArtProvider2>::QueryInterface(riid, ppvObject);
}
