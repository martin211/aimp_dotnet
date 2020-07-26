// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

class AimpDataStorageCommandReportDialog : public IUnknownInterfaceImpl<IAIMPMLDataStorageCommandReportDialog>
{
private:
    gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandReportDialog^> _instance;

public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandReportDialog> Base;

    AimpDataStorageCommandReportDialog(gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandReportDialog^> instance);

    virtual HRESULT WINAPI Execute(HWND OwnerHandle);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
