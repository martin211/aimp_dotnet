//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpPlaylistPreimage.h"
#include "../AimpPlaylistPreimageListener.h"
#include "SDK/Threading/AimpTaskOwner.h"

using namespace AIMP::SDK;

InternalAimpPlaylistPreimage::InternalAimpPlaylistPreimage(gcroot<IAimpPlaylistPreimage^> managedInstance) {
    _managedInstance = managedInstance;
}

void WINAPI InternalAimpPlaylistPreimage::Finalize() {
    _managedInstance->FinalizeObject();
}

void WINAPI InternalAimpPlaylistPreimage::Initialize(IAIMPPlaylistPreimageListener* Listener) {
    _managedInstance->Initialize(gcnew AimpPlaylistPreimageListener(Listener));
}

HRESULT WINAPI InternalAimpPlaylistPreimage::ConfigLoad(IAIMPStream* Stream) {
    return HRESULT(_managedInstance->ConfigLoad(gcnew AimpStream(Stream))->ResultType);
}

HRESULT WINAPI InternalAimpPlaylistPreimage::ConfigSave(IAIMPStream* Stream) {
    return HRESULT(_managedInstance->ConfigSave(gcnew AimpStream(Stream))->ResultType);
}

HRESULT WINAPI InternalAimpPlaylistPreimage::ExecuteDialog(HWND OwnerWndHanle) {
    IntPtr ownerHandle(OwnerWndHanle);
    return HRESULT(_managedInstance->ExecuteDialog(ownerHandle)->ResultType);
}

HRESULT WINAPI InternalAimpPlaylistPreimage::GetFiles(IAIMPTaskOwner* Owner, DWORD** Flags, IAIMPObjectList** List) {
    ActionResultType res = ActionResultType::Fail;
    Object^ obj = _managedInstance;
    IAimpPlaylistPreimageDataProvider^ dp = dynamic_cast<IAimpPlaylistPreimageDataProvider^>(obj);
    if (dp != nullptr) {
        IAIMPObjectList* L = AimpConverter::GetAimpObjectList();
        const auto result = dp->GetFiles(gcnew AimpTaskOwner(Owner));
        res = result->ResultType;
        if (result->ResultType == ActionResultType::OK) {
            *Flags = (DWORD*)result->Item1;
            Collections::IList^ collection = result->Item2;
            Type^ t = collection->GetType()->GetGenericArguments()[0];
            if (t == IAimpFileInfo::typeid) {
                for (int i = 0; i < collection->Count; i++) {
                    IAIMPFileInfo* fi = AimpConverter::ToAimpObject(static_cast<IAimpFileInfo^>(collection[i]));
                    L->Add(fi);
                    fi->Release();
                    fi = nullptr;
                }
            }
            else if (t == String::typeid) {
                for (int i = 0; i < collection->Count; i++) {
                    String^ str = static_cast<String^>(collection[i]);
                    auto s = AimpConverter::ToAimpString(str);
                    L->Add(s);
                    s->Release();
                }
            }
        }

        *List = L;
    }

    return static_cast<HRESULT>(res);
}


HRESULT WINAPI InternalAimpPlaylistPreimage::GetValueAsInt32(int PropertyID, int* Value) {
    HRESULT res = AimpPropertyList::GetValueAsInt32(PropertyID, Value);

    switch (PropertyID) {
    case AIMP_PLAYLISTPREIMAGE_PROPID_AUTOSYNC:
        *Value = _managedInstance->AutoSync ? 1 : 0;
        res = S_OK;
        break;
    case AIMP_PLAYLISTPREIMAGE_PROPID_HASDIALOG:
        *Value = _managedInstance->HasDialog ? 1 : 0;
        res = S_OK;
        break;
    case AIMP_PLAYLISTPREIMAGE_PROPID_AUTOSYNC_ON_STARTUP:
        *Value = _managedInstance->AutoSyncOnStartup ? 1 : 0;
        res = S_OK;
        break;
    }

    return res;
}

HRESULT WINAPI InternalAimpPlaylistPreimage::GetValueAsObject(int PropertyID, REFIID IID, void** Value) {
    HRESULT res = AimpPropertyList::GetValueAsObject(PropertyID, IID, Value);

    switch (PropertyID) {
    case AIMP_PLAYLISTPREIMAGE_PROPID_FACTORYID:
        *Value = AimpConverter::ToAimpString(_managedInstance->FactoryId);
        res = S_OK;
        break;
    case AIMP_PLAYLISTPREIMAGE_PROPID_SORTTEMPLATE:
        *Value = AimpConverter::ToAimpString(_managedInstance->SortTemplate);
        res = S_OK;
        break;
    }

    return res;
}

ULONG WINAPI InternalAimpPlaylistPreimage::Release(void) {
    return Base::Release();
}

ULONG WINAPI InternalAimpPlaylistPreimage::AddRef(void) {
    return Base::AddRef();
}

HRESULT WINAPI InternalAimpPlaylistPreimage::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPPlaylistPreimage) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPPlaylistPreimageDataProvider) {
        *ppvObject = static_cast<IAIMPPlaylistPreimageDataProvider*>(this);
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}
