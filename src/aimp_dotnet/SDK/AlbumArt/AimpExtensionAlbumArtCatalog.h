// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

class AimpExtensionAlbumArtCatalog :
    public IUnknownInterfaceImpl<IAIMPExtensionAlbumArtCatalog>,
    public IAIMPExtensionAlbumArtCatalog2 {
private:
    gcroot<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtCatalog^> _managedinstance;
    IAIMPCore* _aimpCore;
public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionAlbumArtCatalog> Base;

    AimpExtensionAlbumArtCatalog(IAIMPCore* aimpCore,
                                 gcroot<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtCatalog^> instance);

    virtual HRESULT WINAPI GetIcon(HICON** Image);

    virtual HRESULT WINAPI GetName(IAIMPString** Name);

    virtual HRESULT WINAPI Show(IAIMPString* FileURI, IAIMPString* Artist, IAIMPString* Album,
                                IAIMPImageContainer** Image);

    virtual HRESULT WINAPI Show2(IAIMPFileInfo* FileInfo, IAIMPImageContainer** Image);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
