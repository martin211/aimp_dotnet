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
#include "InternalAimpMusicLibraryPlaylistPreimage.h"
#include "../MusicLibrary/AimpDataFieldFilter.h"

namespace AIMP
{
    namespace SDK
    {
        //InternalAimpMusicLibraryPlaylistPreimage::InternalAimpMusicLibraryPlaylistPreimage(gcroot<AIMP::SDK::MusicLibrary::IAimpMusicLibraryPlaylistPreimage^> managedInstance)
        //{
        //    _managedInstance = managedInstance;
        //}

        HRESULT WINAPI InternalAimpMusicLibraryPlaylistPreimage::GetFilter(IAIMPMLDataFilter** Filter)
        {
            IAimpDataFieldFilter^ dataFilter = nullptr;
            AimpActionResult res = AimpActionResult::Fail;
            //res = _managedInstance->GetFilter(&dataFilter);

            //if (res == AimpActionResult::Ok)
            //{
            //    *Filter = gcnew AimpDataFieldFilter();
            //}

            return (HRESULT)res;
        }

        HRESULT WINAPI InternalAimpMusicLibraryPlaylistPreimage::GetStorage(IUnknown** Storage)
        {
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
        //    *ppvObject = NULL;
        //    return res;
        //}
    }
}