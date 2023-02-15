//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

class AimpDataStorageCommandAddFiles : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandAddFiles> {
private:
    gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandAddFiles^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandAddFiles> Base;

    explicit AimpDataStorageCommandAddFiles(
        gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandAddFiles^> instance);

    virtual HRESULT WINAPI Add(IAIMPObjectList* Files);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
