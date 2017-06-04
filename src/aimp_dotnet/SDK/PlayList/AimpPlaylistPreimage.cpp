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

#include "Stdafx.h"
#include "AimpPlaylistPreimage.h"

AimpPlaylistPreimage::AimpPlaylistPreimage(gcroot<AIMP::SDK::Playlist::IAimpPlaylistPreimage^> managedObject)
{
    _managedObject = managedObject;
}

void AimpPlaylistPreimage::Initialize(IAIMPPlaylistPreimageListener* Listener)
{
    _managedObject->Initialize(gcnew AIMP::SDK::AimpPlaylistPreimageListener(Listener));
}

HRESULT AimpPlaylistPreimage::ConfigLoad(IAIMPStream * Stream)
{
    return (HRESULT)_managedObject->ConfigLoad(gcnew AIMP::SDK::AimpStream(Stream));
}

HRESULT AimpPlaylistPreimage::ConfigSave(IAIMPStream * Stream)
{
    return (HRESULT)_managedObject->ConfigSave(gcnew AIMP::SDK::AimpStream(Stream));
}

HRESULT AimpPlaylistPreimage::ExecuteDialog(HWND OwnerWndHanle)
{
    System::IntPtr ownerHandle(OwnerWndHanle);
    return (HRESULT)_managedObject->ExecuteDialog(ownerHandle);
}

HRESULT WINAPI AimpPlaylistPreimage::GetValueAsInt32(int PropertyID, int *Value)
{
    switch (PropertyID)
    {
    case AIMP_PLAYLISTPREIMAGE_PROPID_AUTOSYNC:
        *Value = _managedObject->AutoSync ? 1 : 0;
        break;
    case AIMP_PLAYLISTPREIMAGE_PROPID_HASDIALOG:
        *Value = _managedObject->HasDialog ? 1 : 0;
        break;
    case AIMP_PLAYLISTPREIMAGE_PROPID_AUTOSYNC_ON_STARTUP:
        *Value = _managedObject->AutoSyncOnStartup ? 1 : 0;
        break;
    }

    return S_OK;
}

HRESULT WINAPI AimpPlaylistPreimage::GetValueAsObject(int PropertyID, REFIID IID, void **Value)
{
    switch (PropertyID)
    {
    case AIMP_PLAYLISTPREIMAGE_PROPID_FACTORYID:
        *Value = AIMP::SDK::AimpConverter::ToAimpString(_managedObject->FactoryId);
        break;
    case AIMP_PLAYLISTPREIMAGE_PROPID_SORTTEMPLATE:
        *Value = AIMP::SDK::AimpConverter::ToAimpString(_managedObject->SortTemplate);
        break;
    }

    return S_OK;
}

void AimpPlaylistPreimage::FinalizeObject()
{
    _managedObject->FinalizeObject();
}

ULONG AimpPlaylistPreimage::AddRef(void)
{
    return Base::AddRef();
}

ULONG AimpPlaylistPreimage::Release(void)
{
    return Base::Release();
}

HRESULT AimpPlaylistPreimage::QueryInterface(REFIID riid, LPVOID * ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPPlaylistPreimageListener)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = NULL;
    return E_NOINTERFACE;
}
