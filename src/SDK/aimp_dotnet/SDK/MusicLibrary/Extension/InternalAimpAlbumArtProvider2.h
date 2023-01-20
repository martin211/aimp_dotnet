//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

class InternalAimpAlbumArtProvider2 : public IUnknownInterfaceImpl<IAIMPMLAlbumArtProvider2> {
private:
    gcroot<MusicLibrary::Extension::IAimpAlbumArtProvider2^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLAlbumArtProvider2> Base;

    explicit InternalAimpAlbumArtProvider2(gcroot<MusicLibrary::Extension::IAimpAlbumArtProvider2^> instance);

    virtual HRESULT WINAPI Get(IAIMPObjectList* Fields, VARIANT* Values, IAIMPAlbumArtRequest* Request, IAIMPImageContainer** Image);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
