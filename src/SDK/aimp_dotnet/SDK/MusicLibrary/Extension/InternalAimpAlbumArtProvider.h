//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

class InternalAimpAlbumArtProvider : public IUnknownInterfaceImpl<IAIMPMLAlbumArtProvider> {
private:
    gcroot<MusicLibrary::Extension::IAimpAlbumArtProvider^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLAlbumArtProvider> Base;

    explicit InternalAimpAlbumArtProvider(gcroot<MusicLibrary::Extension::IAimpAlbumArtProvider^> instance);

    virtual HRESULT WINAPI Get(IAIMPObjectList* Fields, VARIANT* Values, IAIMPPropertyList* Options, IAIMPImageContainer** Image);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};