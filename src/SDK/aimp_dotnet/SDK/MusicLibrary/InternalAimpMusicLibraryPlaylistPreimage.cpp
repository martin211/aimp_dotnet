//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpMusicLibraryPlaylistPreimage.h"

//InternalAimpMusicLibraryPlaylistPreimage::InternalAimpMusicLibraryPlaylistPreimage(gcroot<AIMP::SDK::MusicLibrary::IAimpMusicLibraryPlaylistPreimage^> managedInstance)
//{
//    _managedInstance = managedInstance;
//}

HRESULT WINAPI InternalAimpMusicLibraryPlaylistPreimage::GetFilter(IAIMPMLDataFilter** Filter) {
    // TODO Complete it
    DataFilter::IAimpDataFieldFilter^ dataFilter = nullptr;
    ActionResultType res = ActionResultType::Fail;
    //res = _managedInstance->GetFilter(&dataFilter);

    //if (res == ActionResultType::OK)
    //{
    //    *Filter = gcnew AimpDataFieldFilter();
    //}

    return HRESULT(res);
}

HRESULT WINAPI InternalAimpMusicLibraryPlaylistPreimage::GetStorage(IUnknown** Storage) {
    return S_OK;
}

//
//ULONG WINAPI InternalAimpMusicLibraryPlaylistPreimage::Release(void)
//{
//    return Base::Release();
//}
//
//ULONG WINAPI InternalAimpMusicLibraryPlaylistPreimage::AddRef(void)
//{
//    return Base::AddRef();
//}
//
//HRESULT WINAPI InternalAimpMusicLibraryPlaylistPreimage::QueryInterface(REFIID riid, LPVOID* ppvObject)
//{
//    HRESULT res = Base::QueryInterface(riid, ppvObject);
//
//    if (riid == IID_IAIMPPlaylistPreimage)
//    {
//        *ppvObject = this;
//        AddRef();
//        return S_OK;
//    }
//
//    if (riid == IID_IAIMPPlaylistPreimageDataProvider)
//    {
//        *ppvObject = static_cast<IAIMPPlaylistPreimageDataProvider*>(this);
//        AddRef();
//        return S_OK;
//    }
//
//    *ppvObject = nullptr;
//    return res;
//}
