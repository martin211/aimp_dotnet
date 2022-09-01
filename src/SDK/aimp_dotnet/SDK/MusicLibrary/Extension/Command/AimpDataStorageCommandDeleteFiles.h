//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

class AimpDataStorageCommandDeleteFiles : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandDeleteFiles> {
private:
    gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandDeleteFiles^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandDeleteFiles> Base;

    AimpDataStorageCommandDeleteFiles(gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandDeleteFiles^> instance);

    virtual BOOL WINAPI CanDelete(BOOL Physically);

    virtual HRESULT WINAPI Delete(IAIMPMLFileList* Files, BOOL Physically);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
