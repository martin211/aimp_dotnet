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
#include "InternalAimpPlaylistPreimage.h"
#include "../AimpPlaylistPreimageListener.h"
#include "../../AimpStream.h"
#include "SDK/Threading/AimpTaskOwner.h"

using namespace AIMP::SDK;

InternalAimpPlaylistPreimage::InternalAimpPlaylistPreimage(gcroot<AIMP::SDK::Playlist::IAimpPlaylistPreimage^> managedInstance)
{
    _managedInstance = managedInstance;
}

void WINAPI InternalAimpPlaylistPreimage::Finalize()
{
    _managedInstance->FinalizeObject();
}

void WINAPI InternalAimpPlaylistPreimage::Initialize(IAIMPPlaylistPreimageListener* Listener)
{
    _managedInstance->Initialize(gcnew AimpPlaylistPreimageListener(Listener));
}

HRESULT WINAPI InternalAimpPlaylistPreimage::ConfigLoad(IAIMPStream* Stream)
{
    return (HRESULT)_managedInstance->ConfigLoad(gcnew AimpStream(Stream));
}

HRESULT WINAPI InternalAimpPlaylistPreimage::ConfigSave(IAIMPStream* Stream)
{
    return (HRESULT)_managedInstance->ConfigSave(gcnew AimpStream(Stream));
}

HRESULT WINAPI AIMP::SDK::InternalAimpPlaylistPreimage::ExecuteDialog(HWND OwnerWndHanle)
{
    System::IntPtr ownerHandle(OwnerWndHanle);
    return (HRESULT)_managedInstance->ExecuteDialog(ownerHandle);
}

HRESULT WINAPI AIMP::SDK::InternalAimpPlaylistPreimage::GetFiles(IAIMPTaskOwner* Owner, DWORD** Flags, IAIMPObjectList** List)
{
    AimpActionResult res = AimpActionResult::Fail;
    Object^ obj = _managedInstance;
    IAimpPlaylistPreimageDataProvider^ dp = dynamic_cast<IAimpPlaylistPreimageDataProvider^>(obj);
    if (dp != nullptr)
    {
        int flags = 0;
        System::Collections::Generic::List<Object^>^ files;
        res = dp->GetFiles(gcnew AimpTaskOwner(Owner), *&flags, *&files);

        if (res == AimpActionResult::Ok)
        {
            *Flags = (DWORD*)flags;
            //*List = list->In
        }
    }

    return (HRESULT)res;
}

void WINAPI AIMP::SDK::InternalAimpPlaylistPreimage::BeginUpdate()
{ }

void WINAPI AIMP::SDK::InternalAimpPlaylistPreimage::EndUpdate()
{ }

HRESULT WINAPI AIMP::SDK::InternalAimpPlaylistPreimage::Reset()
{
    return E_NOTIMPL;
}

HRESULT WINAPI AIMP::SDK::InternalAimpPlaylistPreimage::GetValueAsFloat(int PropertyID, double *Value)
{
    return E_NOTIMPL;
}

HRESULT WINAPI AIMP::SDK::InternalAimpPlaylistPreimage::GetValueAsInt64(int PropertyID, INT64 *Value)
{
    return E_NOTIMPL;
}

HRESULT WINAPI AIMP::SDK::InternalAimpPlaylistPreimage::SetValueAsFloat(int PropertyID, const double Value)
{
    return E_NOTIMPL;
}

HRESULT WINAPI AIMP::SDK::InternalAimpPlaylistPreimage::SetValueAsInt32(int PropertyID, int Value)
{
    return E_NOTIMPL;
}

HRESULT WINAPI AIMP::SDK::InternalAimpPlaylistPreimage::SetValueAsInt64(int PropertyID, const INT64 Value)
{
    return E_NOTIMPL;
}

HRESULT WINAPI AIMP::SDK::InternalAimpPlaylistPreimage::SetValueAsObject(int PropertyID, IUnknown *Value)
{
    System::Diagnostics::Debugger::Break();
    return E_NOTIMPL;
}

HRESULT WINAPI InternalAimpPlaylistPreimage::GetValueAsInt32(int PropertyID, int *Value)
{
    switch (PropertyID)
    {
    case AIMP_PLAYLISTPREIMAGE_PROPID_AUTOSYNC:
        *Value = _managedInstance->AutoSync ? 1 : 0;
        break;
    case AIMP_PLAYLISTPREIMAGE_PROPID_HASDIALOG:
        *Value = _managedInstance->HasDialog ? 1 : 0;
        break;
    case AIMP_PLAYLISTPREIMAGE_PROPID_AUTOSYNC_ON_STARTUP:
        *Value = _managedInstance->AutoSyncOnStartup ? 1 : 0;
        break;
    }

    return S_OK;
}

HRESULT WINAPI InternalAimpPlaylistPreimage::GetValueAsObject(int PropertyID, REFIID IID, void **Value)
{
    switch (PropertyID)
    {
    case AIMP_PLAYLISTPREIMAGE_PROPID_FACTORYID:
        *Value = AimpConverter::ToAimpString(_managedInstance->FactoryId);
        break;
    case AIMP_PLAYLISTPREIMAGE_PROPID_SORTTEMPLATE:
        *Value = AimpConverter::ToAimpString(_managedInstance->SortTemplate);
        break;
    }

    return S_OK;
}

ULONG WINAPI InternalAimpPlaylistPreimage::Release(void)
{
    return Base::Release();
}

ULONG WINAPI InternalAimpPlaylistPreimage::AddRef(void)
{
    return Base::AddRef();
}

HRESULT WINAPI InternalAimpPlaylistPreimage::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPPlaylistPreimage)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPPlaylistPreimageDataProvider)
    {
        *ppvObject = static_cast<IAIMPPlaylistPreimageDataProvider*>(this);
        AddRef();
        return S_OK;
    }

    *ppvObject = NULL;
    return res;
}
