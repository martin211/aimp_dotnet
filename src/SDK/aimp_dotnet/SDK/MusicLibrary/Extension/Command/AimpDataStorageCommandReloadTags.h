//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

class AimpDataStorageCommandReloadTags : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandReloadTags> {
private:
    gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandReloadTags^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandReloadTags> Base;

    AimpDataStorageCommandReloadTags(
        gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandReloadTags^> instance);

    virtual HRESULT WINAPI ReloadTags(IAIMPMLFileList* Files);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
