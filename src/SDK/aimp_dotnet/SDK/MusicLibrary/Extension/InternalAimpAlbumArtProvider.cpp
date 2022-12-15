#include "stdafx.h"
#include "InternalAimpAlbumArtProvider.h"

#include "SDK/AimpObjectList.h"
#include "SDK/Objects/AimpImageContainer.h"

InternalAimpAlbumArtProvider::InternalAimpAlbumArtProvider(gcroot<MusicLibrary::Extension::IAimpAlbumArtProvider^> instance) {
    _instance = instance;
}

HRESULT InternalAimpAlbumArtProvider::Get(IAIMPObjectList* Fields, VARIANT* Values, IAIMPPropertyList* Options, IAIMPImageContainer** Image) {
    const auto filedList = gcnew AimpObjectList<String^>(Fields);
    array<Object^>^ values = gcnew array<Object^>(Fields->GetCount());

    for (int i = 0; i < values->Length; i++)
    {
        values[i] = AimpConverter::FromVariant(&Values[i]);
    }

    const auto result = _instance->Get(filedList, values, nullptr);

    if (result->ResultType == ActionResultType::OK) {
        IAIMPImageContainer* aimpContainer = ((AimpImageContainer^)result->Result)->InternalAimpObject;
        *Image = aimpContainer;
    }

    return E_NOTIMPL;
}

ULONG InternalAimpAlbumArtProvider::AddRef() {
    return Base::AddRef();
}

ULONG InternalAimpAlbumArtProvider::Release() {
    return Base::Release();
}

HRESULT InternalAimpAlbumArtProvider::QueryInterface(const IID& riid, LPVOID* ppvObject) {
    if (riid == IID_IAIMPMLAlbumArtProvider) {
        *ppvObject = this;
        this->AddRef();
        return S_OK;
    }

    return Base::QueryInterface(riid, ppvObject);
}
