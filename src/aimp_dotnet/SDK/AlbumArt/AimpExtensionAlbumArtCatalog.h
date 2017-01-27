/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 */
 
#pragma once

class AimpExtensionAlbumArtCatalog : 
    public IUnknownInterfaceImpl<IAIMPExtensionAlbumArtCatalog>, 
    public IAIMPExtensionAlbumArtCatalog2
{
private:
    gcroot<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtCatalog^> _managedinstance;
    IAIMPCore *_aimpCore;
public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionAlbumArtCatalog> Base;

    AimpExtensionAlbumArtCatalog(IAIMPCore *aimpCore, gcroot<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtCatalog^> instance);

    virtual HRESULT WINAPI GetIcon(HICON **Image);

    virtual HRESULT WINAPI GetName(IAIMPString **Name);

    virtual HRESULT WINAPI Show(IAIMPString *FileURI, IAIMPString *Artist, IAIMPString *Album, IAIMPImageContainer **Image);

    virtual HRESULT WINAPI Show2(IAIMPFileInfo *FileInfo, IAIMPImageContainer **Image);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
