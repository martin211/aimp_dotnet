// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpMLPlaylistPreimage.h"
#include "../AimpPlaylistPreimageListener.h"
#include "SDK/AimpStream.h"
#include "SDK/Threading/AimpTaskOwner.h"
#include "SDK/MusicLibrary/InternalAimpDataFilter.h"

using namespace AIMP::SDK;

InternalAimpMLPlaylistPreimage::InternalAimpMLPlaylistPreimage(gcroot<IAimpPlaylistPreimage^> managedInstance)
{
    _managedInstance = managedInstance;
}

HRESULT WINAPI InternalAimpMLPlaylistPreimage::GetFilter(IAIMPMLDataFilter** Filter)
{
    ActionResultType res = ActionResultType::Fail;
    Object^ obj = _managedInstance;
    auto preimage = dynamic_cast<MusicLibrary::IAimpMusicLibraryPlaylistPreimage^>(obj);
    if (preimage != nullptr)
    {
        IAimpDataFieldFilter^ f = nullptr;
        res = preimage->GetFilter(*&f);

        if (res == ActionResultType::OK && f != nullptr)
        {
            *Filter = new InternalAimpDataFilter(nullptr);
        }
    }

    return HRESULT(res);
}

HRESULT WINAPI InternalAimpMLPlaylistPreimage::GetStorage(IUnknown** Storage)
{
    ActionResultType res = ActionResultType::Fail;
    Object^ obj = _managedInstance;
    MusicLibrary::IAimpMusicLibraryPlaylistPreimage^ preimage = dynamic_cast<MusicLibrary::
        IAimpMusicLibraryPlaylistPreimage^>(obj);

    if (preimage != nullptr)
    {
        // TODO Complete it
    }

    return HRESULT(res);
}

HRESULT WINAPI InternalAimpMLPlaylistPreimage::GetValueAsFloat(int PropertyID, double* Value)
{
    return E_NOTIMPL;
}

HRESULT WINAPI InternalAimpMLPlaylistPreimage::GetValueAsInt64(int PropertyID, INT64* Value)
{
    return E_NOTIMPL;
}

HRESULT WINAPI InternalAimpMLPlaylistPreimage::SetValueAsFloat(int PropertyID, const double Value)
{
    return E_NOTIMPL;
}

HRESULT WINAPI InternalAimpMLPlaylistPreimage::SetValueAsInt32(int PropertyID, int Value)
{
    return E_NOTIMPL;
}

HRESULT WINAPI InternalAimpMLPlaylistPreimage::SetValueAsInt64(int PropertyID, const INT64 Value)
{
    return E_NOTIMPL;
}

HRESULT WINAPI InternalAimpMLPlaylistPreimage::SetValueAsObject(int PropertyID, IUnknown* Value)
{
    return E_NOTIMPL;
}

HRESULT WINAPI InternalAimpMLPlaylistPreimage::GetValueAsInt32(int PropertyID, int* Value)
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
    default:
        *Value = 0;
    }

    return S_OK;
}

HRESULT WINAPI InternalAimpMLPlaylistPreimage::GetValueAsObject(int PropertyID, REFIID IID, void** Value)
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

void WINAPI InternalAimpMLPlaylistPreimage::BeginUpdate()
{
}

void WINAPI InternalAimpMLPlaylistPreimage::EndUpdate()
{
}

HRESULT WINAPI InternalAimpMLPlaylistPreimage::Reset()
{
    return E_NOTIMPL;
}


ULONG WINAPI InternalAimpMLPlaylistPreimage::Release(void)
{
    return Base::Release();
}

ULONG WINAPI InternalAimpMLPlaylistPreimage::AddRef(void)
{
    return Base::AddRef();
}

HRESULT WINAPI InternalAimpMLPlaylistPreimage::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPMLPlaylistPreimage)
    {
        *ppvObject = static_cast<IAIMPMLPlaylistPreimage*>(this);
        Base::AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPPlaylistPreimageDataProvider)
    {
        *ppvObject = static_cast<IAIMPPlaylistPreimageDataProvider*>(this);
        Base::AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPPlaylistPreimage)
    {
        *ppvObject = this;
        Base::AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}

void WINAPI InternalAimpMLPlaylistPreimage::Finalize()
{
    _managedInstance->FinalizeObject();
}

void WINAPI InternalAimpMLPlaylistPreimage::Initialize(IAIMPPlaylistPreimageListener* Listener)
{
    _managedInstance->Initialize(gcnew AimpPlaylistPreimageListener(Listener));
}

HRESULT WINAPI InternalAimpMLPlaylistPreimage::ConfigLoad(IAIMPStream* Stream)
{
    return (HRESULT)_managedInstance->ConfigLoad(gcnew AimpStream(Stream));
}

HRESULT WINAPI InternalAimpMLPlaylistPreimage::ConfigSave(IAIMPStream* Stream)
{
    return (HRESULT)_managedInstance->ConfigSave(gcnew AimpStream(Stream));
}

HRESULT WINAPI InternalAimpMLPlaylistPreimage::ExecuteDialog(HWND OwnerWndHanle)
{
    System::IntPtr ownerHandle(OwnerWndHanle);
    return (HRESULT)_managedInstance->ExecuteDialog(ownerHandle);
}

HRESULT WINAPI InternalAimpMLPlaylistPreimage::GetFiles(IAIMPTaskOwner* Owner, DWORD** Flags, IAIMPObjectList** List)
{
    ActionResultType res = ActionResultType::Fail;
    Object^ obj = _managedInstance;
    IAimpPlaylistPreimageDataProvider^ dp = dynamic_cast<IAimpPlaylistPreimageDataProvider^>(obj);
    if (dp != nullptr)
    {
        int flags = 0;
        IAIMPObjectList* L = AIMP::SDK::AimpConverter::GetAimpObjectList();
        System::Collections::IList^ collection;
        res = dp->GetFiles(gcnew AimpTaskOwner(Owner), *&flags, *&collection);

        if (res == ActionResultType::OK)
        {
            *Flags = (DWORD*)flags;
            System::Type^ t = collection->GetType()->GetGenericArguments()[0];
            if (t == AIMP::SDK::FileManager::IAimpFileInfo::typeid)
            {
                for (int i = 0; i < collection->Count; i++)
                {
                    IAIMPFileInfo* fi = AIMP::SDK::AimpConverter::ToAimpObject((IAimpFileInfo^)collection[i]);
                    L->Add(fi);
                    fi->Release();
                    fi = nullptr;
                }
            }
            else if (t == System::String::typeid)
            {
                for (int i = 0; i < collection->Count; i++)
                {
                    System::String^ str = (System::String^)collection[i];
                    IAIMPString* s = AIMP::SDK::AimpConverter::ToAimpString(str);
                    L->Add(s);
                    s->Release();
                }
            }
        }

        *List = L;
    }

    return (HRESULT)res;
}
