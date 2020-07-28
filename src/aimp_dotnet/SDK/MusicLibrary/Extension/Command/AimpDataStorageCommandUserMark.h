// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

class AimpDataStorageCommandUserMark : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandUserMark>
{
private:
    gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandUserMark^> _instance;

public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandUserMark> Base;

    AimpDataStorageCommandUserMark(gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandUserMark^> instance);

    virtual HRESULT WINAPI SetMark(VARIANT* ID, const DOUBLE Value);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
