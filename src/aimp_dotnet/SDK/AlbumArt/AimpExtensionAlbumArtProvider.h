// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

class AimpExtensionAlbumArtProvider :
    public IUnknownInterfaceImpl<IAIMPExtensionAlbumArtProvider>,
    public IAIMPExtensionAlbumArtProvider2
{
private:
    gcroot<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtProvider^> _managedinstance;
    IAIMPCore* _aimpCore;
public:
    AimpExtensionAlbumArtProvider(IAIMPCore* aimpCore,
                                  gcroot<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtProvider^> instance)
    {
        _managedinstance = instance;
        _aimpCore = aimpCore;
    }

    typedef IUnknownInterfaceImpl<IAIMPExtensionAlbumArtProvider> Base;

    virtual HRESULT WINAPI Get(IAIMPString* FileURI, IAIMPString* Artist, IAIMPString* Album,
                               IAIMPPropertyList* Options, IAIMPImageContainer** Image);

    virtual DWORD WINAPI GetCategory();

    virtual HRESULT WINAPI Get2(IAIMPFileInfo* FileInfo, IAIMPPropertyList* Options, IAIMPImageContainer** Image);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (!ppvObject)
        {
            return E_POINTER;
        }

        if (riid == IID_IAIMPExtensionAlbumArtProvider)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }
        if (riid == IID_IAIMPExtensionAlbumArtProvider2)
        {
            *ppvObject = static_cast<IAIMPExtensionAlbumArtProvider2*>(this);
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }
};
