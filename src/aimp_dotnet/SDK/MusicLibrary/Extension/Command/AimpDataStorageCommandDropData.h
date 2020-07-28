// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

class AimpDataStorageCommandDropData : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandDropData> {
private:
    gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandDropData^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandDropData> Base;

    AimpDataStorageCommandDropData(gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandDropData^> instance);

    virtual HRESULT WINAPI DropData();

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
