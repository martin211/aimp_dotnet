//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "AimpDataStorageCommandDeleteFiles.h"

class AimpDataStorageCommandDeleteFiles2 :
    public AimpDataStorageCommandDeleteFiles,
    public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandDeleteFiles2> {
private:
    gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandDeleteFiles2^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandDeleteFiles2> Base;

    AimpDataStorageCommandDeleteFiles2(gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandDeleteFiles2^> instance);

    virtual HRESULT WINAPI Delete2(IAIMPMLDataFilter* Filter, BOOL Physically);

    virtual BOOL WINAPI CanDelete(BOOL Physically);

    virtual HRESULT WINAPI Delete(IAIMPMLFileList* Files, BOOL Physically);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
