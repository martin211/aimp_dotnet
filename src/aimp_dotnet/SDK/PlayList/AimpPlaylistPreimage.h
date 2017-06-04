// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once
#include "AimpPlaylistPreimageListener.h"

class AimpPlaylistPreimage : public IUnknownInterfaceImpl<IAIMPPlaylistPreimage>
{
private:
    gcroot<AIMP::SDK::Playlist::IAimpPlaylistPreimage^> _managedObject;
    typedef IUnknownInterfaceImpl<IAIMPPlaylistPreimage> Base;

public:

    AimpPlaylistPreimage(gcroot<AIMP::SDK::Playlist::IAimpPlaylistPreimage^> managedObject);

    virtual void WINAPI FinalizeObject();

    virtual void WINAPI Initialize(IAIMPPlaylistPreimageListener* Listener);

    virtual HRESULT WINAPI ConfigLoad(IAIMPStream* Stream);
    
    virtual HRESULT WINAPI ConfigSave(IAIMPStream* Stream);

    virtual HRESULT WINAPI ExecuteDialog(HWND OwnerWndHanle);

    virtual HRESULT WINAPI GetValueAsInt32(int PropertyID, int *Value);

    virtual HRESULT WINAPI GetValueAsObject(int PropertyID, REFIID IID, void **Value);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
