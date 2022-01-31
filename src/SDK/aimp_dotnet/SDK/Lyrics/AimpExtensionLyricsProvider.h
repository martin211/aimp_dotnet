// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "AIMPSDK/AIMP400/apiLyrics.h"

using namespace AIMP::SDK::Lyrics::Extensions;

class AimpExtensionLyricsProvider :
    public IUnknownInterfaceImpl<IAIMPExtensionLyricsProvider> {
private:
    gcroot<IAimpExtensionLyricsProvider^> _managedExtension;
public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionLyricsProvider> Base;

    explicit AimpExtensionLyricsProvider(gcroot<IAimpExtensionLyricsProvider^> extension);

    virtual HRESULT WINAPI Get(IAIMPTaskOwner* owner, IAIMPFileInfo* file_info, DWORD flags, IAIMPLyrics* lyrics);

    virtual DWORD WINAPI GetCategory();

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
