//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

class AimpDataStorageCommandAddFilesDialog : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandAddFilesDialog> {
private:
    gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandAddFilesDialog^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandAddFilesDialog> Base;

    AimpDataStorageCommandAddFilesDialog(
        gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandAddFilesDialog^> instance);

    virtual HRESULT WINAPI Execute(HWND OwnerHandle);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
