//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "IUnknownInterfaceImpl.h"

using namespace AlbumArt;
using namespace AlbumArt::Extensions;

private class AimpExtensionAlbumArtProvider3 :
    public IUnknownInterfaceImpl<IAIMPExtensionAlbumArtProvider3>,
    public IAIMPExtensionAlbumArtProvider3 {
private:
    gcroot<IAimpExtensionAlbumArtProvider3^> _managed;

public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionAlbumArtProvider3> Base;

    AimpExtensionAlbumArtProvider3(gcroot<IAimpExtensionAlbumArtProvider3^> managed);

    virtual HRESULT WINAPI Get(IAIMPFileInfo* FileURI, IAIMPAlbumArtRequest* Request, IAIMPImageContainer** Image);

    virtual DWORD WINAPI GetCategory();

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject) {
        if (!ppvObject) {
            return E_POINTER;
        }

        if (riid == IID_IAIMPExtensionAlbumArtProvider3) {
        //if (riid == IID_IAIMPServiceAlbumArt) {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }

    virtual ULONG WINAPI AddRef(void) {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void) {
        return Base::Release();
    }
};