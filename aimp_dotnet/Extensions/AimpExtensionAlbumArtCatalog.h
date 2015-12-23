#pragma once

class AimpExtensionAlbumArtCatalog : 
    public IUnknownInterfaceImpl<IAIMPExtensionAlbumArtCatalog>, 
    public IAIMPExtensionAlbumArtCatalog2
{
private:
    gcroot<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtCatalog^> _managedinstance;
    IAIMPCore *_aimpCore;
public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionAlbumArtCatalog> Base;

    AimpExtensionAlbumArtCatalog(IAIMPCore *aimpCore, gcroot<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtCatalog^> instance)        
    {
        _managedinstance = instance;
        _aimpCore = aimpCore;
    }

    virtual HRESULT WINAPI GetIcon(HICON *Image);

    virtual HRESULT WINAPI GetName(IAIMPString **Name);

    virtual HRESULT WINAPI Show(IAIMPString *FileURI, IAIMPString *Artist, IAIMPString *Album, IAIMPImageContainer **Image);

    virtual HRESULT WINAPI Show2(IAIMPFileInfo *FileInfo, IAIMPImageContainer **Image);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (!ppvObject)
        {
            return E_POINTER;
        }

        if (riid == IID_IAIMPExtensionAlbumArtCatalog) {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }
        if (riid == IID_IAIMPExtensionAlbumArtCatalog2) {
            *ppvObject = static_cast<IAIMPExtensionAlbumArtCatalog2*>(this);
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
