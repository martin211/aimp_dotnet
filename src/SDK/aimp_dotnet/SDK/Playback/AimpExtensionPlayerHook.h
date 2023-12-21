//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

using namespace Player::Extensions;

class AimpExtensionPlayerHook :
    public IUnknownInterfaceImpl<IAIMPExtensionPlayerHook> {
private:
    gcroot<IAimpExtensionPlayerHook^> _managed;
public:
    explicit AimpExtensionPlayerHook(const gcroot<IAimpExtensionPlayerHook^> managed)
        : _managed(managed) {
    }

    typedef IUnknownInterfaceImpl<IAIMPExtensionPlayerHook> Base;

    virtual HRESULT WINAPI OnCheckURL(IAIMPString* url, BOOL* handled);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
