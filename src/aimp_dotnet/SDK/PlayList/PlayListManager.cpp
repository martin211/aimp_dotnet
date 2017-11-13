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
#include "PlayListManager.h"
#include "AimpExtensionPlaylistPreimageFactory.h"

using namespace AIMP::SDK;

PlayListManager::PlayListManager(ManagedAimpCore ^core) : AimpBaseManager<IAIMPServicePlaylistManager2>(core)
{
}

PlayListManager::~PlayListManager()
{
    this->!PlayListManager();
}

PlayListManager::!PlayListManager()
{
}

IAimpPlaylistQueue^ PlayListManager::PlaylistQueue::get()
{
    IAIMPServicePlaylistManager2 *service = nullptr;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = GetService(&service);
        if (res == AimpActionResult::Ok)
        {
            IAIMPPlaylistQueue *playListQueue;
            if (CheckResult(service->QueryInterface(IID_IAIMPPlaylistQueue, (void**)&playListQueue)) == AimpActionResult::Ok)
            {
                IAIMPPlaylistQueue2 *playListQueue2;
                service->QueryInterface(IID_IAIMPPlaylistQueue2, (void**)&playListQueue2);
                return gcnew AimpPlaylistQueue(playListQueue, playListQueue2);
            }
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }
}

void PlayListManager::PlaylistActivated::add(PlayListHandler ^onEvent)
{
    _onPlaylistActivated = onEvent;
}

void PlayListManager::PlaylistActivated::remove(PlayListHandler ^onEvent)
{
    _onPlaylistActivated = nullptr;
}

void PlayListManager::PlaylistActivated::raise(String ^playListName, String ^playListId)
{
    if (_onPlaylistActivated != nullptr)
    {
        _onPlaylistActivated(playListName, playListId);
    }
}

void PlayListManager::PlaylistAdded::add(PlayListHandler ^onEvent)
{
    if (_onPlaylistAdded == nullptr)
    {
        _onPlaylistAdded = onEvent;
    }
}

void PlayListManager::PlaylistAdded::remove(PlayListHandler ^onEvent)
{
    if (_onPlaylistAdded != nullptr)
    {
        _onPlaylistAdded = nullptr;
    }
}

void PlayListManager::PlaylistAdded::raise(String ^playListName, String ^playListId)
{
    if (_onPlaylistAdded != nullptr)
    {
        _onPlaylistAdded(playListName, playListId);
    }
}

void PlayListManager::PlaylistRemoved::add(PlayListHandler ^onEvent)
{
    _onPlaylistRemoved = onEvent;
}

void PlayListManager::PlaylistRemoved::remove(PlayListHandler ^onEvent)
{
    _onPlaylistRemoved = nullptr;
}

void PlayListManager::PlaylistRemoved::raise(String ^playListName, String ^playListId)
{
    if (_onPlaylistRemoved != nullptr)
    {
        _onPlaylistRemoved(playListName, playListId);
    }
}

AimpActionResult PlayListManager::CreatePlaylist(System::String^ name, bool isActive, IAimpPlaylist ^%playList)
{
    playList = nullptr;
    AimpActionResult res = AimpActionResult::Fail;

    IAIMPPlaylist *pl = nullptr;
    IAIMPString *str = nullptr;
    IAIMPServicePlaylistManager2 *service = nullptr;

    try
    {
        res = GetService(&service);
        if (res == AimpActionResult::Ok && service != nullptr)
        {
            str = AimpConverter::ToAimpString(name);
            res = CheckResult(service->CreatePlaylist(str, (BOOL)isActive, &pl));

            if (res == AimpActionResult::Ok && pl != nullptr)
            {
                playList = gcnew AimpPlayList(pl);
            }

            str->Release();
            str = nullptr;
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return res;
}

AimpActionResult PlayListManager::CreatePlaylistFromFile(System::String^ fileName, bool isActive, IAimpPlaylist ^%playList)
{
    playList = nullptr;
    IAIMPPlaylist *pl = nullptr;
    IAIMPString *str = nullptr;
    IAIMPServicePlaylistManager2 *service = nullptr;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = GetService(&service);
        if (res == AimpActionResult::Ok && service != nullptr)
        {
            str = AimpConverter::ToAimpString(fileName);
            res = CheckResult(service->CreatePlaylistFromFile(str, (BOOL)isActive, &pl));

            if (res == AimpActionResult::Ok && pl != nullptr)
            {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }

        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return res;
}

AimpActionResult PlayListManager::GetActivePlaylist(IAimpPlaylist ^%playList)
{
    playList = nullptr;
    IAIMPPlaylist *pl = nullptr;
    IAIMPServicePlaylistManager2 *service = nullptr;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = GetService(&service);
        if (res == AimpActionResult::Ok && service != nullptr)
        {
            res = CheckResult(service->GetActivePlaylist(&pl));
            if (res == AimpActionResult::Ok)
            {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return res;
}

AimpActionResult PlayListManager::GetLoadedPlaylist(int index, IAimpPlaylist ^%playList)
{
    playList = nullptr;
    IAIMPPlaylist *pl = nullptr;
    IAIMPServicePlaylistManager2 *service = nullptr;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = GetService(&service);
        if (res == AimpActionResult::Ok && service != nullptr)
        {
            res = CheckResult(service->GetLoadedPlaylist(index, &pl));
            if (res == AimpActionResult::Ok)
            {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return res;
}

AimpActionResult PlayListManager::GetPlayablePlaylist(IAimpPlaylist ^%playList)
{
    playList = nullptr;
    IAIMPPlaylist *pl = nullptr;
    IAIMPServicePlaylistManager2 *service = nullptr;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = GetService(&service);
        if (res == AimpActionResult::Ok && service != nullptr)
        {
            res = CheckResult(service->GetPlayablePlaylist(&pl));
            if (res == AimpActionResult::Ok)
            {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return res;
}

AimpActionResult PlayListManager::GetLoadedPlaylistById(System::String^ id, IAimpPlaylist ^%playList)
{
    playList = nullptr;
    IAIMPPlaylist *pl = nullptr;
    IAIMPString *key = nullptr;
    IAIMPServicePlaylistManager2 *service = nullptr;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = GetService(&service);
        if (res == AimpActionResult::Ok && service != nullptr)
        {
            key = AimpConverter::ToAimpString(id);
            res = CheckResult(service->GetLoadedPlaylistByID(key, &pl));
            if (res == AimpActionResult::Ok)
            {
                playList = gcnew AimpPlayList(pl);
            }

            key->Release();
            key = nullptr;
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return res;
}

AimpActionResult PlayListManager::GetLoadedPlaylistByName(System::String^ name, IAimpPlaylist ^%playList)
{
    playList = nullptr;
    IAIMPPlaylist *pl = nullptr;
    IAIMPString *key = nullptr;
    IAIMPServicePlaylistManager2 *service = nullptr;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = GetService(&service);
        if (res == AimpActionResult::Ok && service != nullptr)
        {
            key = AimpConverter::ToAimpString(name);
            res = CheckResult(service->GetLoadedPlaylistByName(key, &pl));

            if (res == AimpActionResult::Ok)
            {
                playList = gcnew AimpPlayList(pl);
            }

            key->Release();
            key = nullptr;
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return res;
}

int PlayListManager::GetLoadedPlaylistCount()
{
    IAIMPServicePlaylistManager2 *service = nullptr;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = GetService(&service);
        if (res == AimpActionResult::Ok && service != nullptr)
        {
            return service->GetLoadedPlaylistCount();
        }

        return 0;
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }
}

AimpActionResult PlayListManager::SetActivePlaylist(IAimpPlaylist^ playList)
{
    IAIMPServicePlaylistManager2 *service = nullptr;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = GetService(&service);
        if (res == AimpActionResult::Ok && service != nullptr)
        {
            res = CheckResult(service->SetActivePlaylist(((AimpPlayList^)playList)->InternalAimpObject));
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return res;
}

//void PlayListManager::OnPlaylistActivated(IAIMPPlaylist* playlist)
//{
//    IAIMPPropertyList *properties;
//    playlist->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
//    String ^name = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_NAME);
//    String ^id = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_ID);
//    this->PlaylistActivated(name, id);
//    properties->Release();
//    properties = nullptr;
//}
//
//void PlayListManager::OnPlaylistAdded(IAIMPPlaylist* playlist)
//{
//    IAIMPPropertyList *properties;
//    playlist->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
//    String ^name = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_NAME);
//    String ^id = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_ID);
//    this->PlaylistAdded(name, id);
//    properties->Release();
//    properties = nullptr;
//}
//
//void PlayListManager::OnPlaylistRemoved(IAIMPPlaylist* playlist)
//{
//    IAIMPPropertyList *properties;
//    playlist->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
//    String ^name = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_NAME);
//    String ^id = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_ID);
//    this->PlaylistRemoved(name, id);
//    properties->Release();
//    properties = nullptr;
//}

AimpActionResult PlayListManager::GetPreimageFactory(int index, IAimpExtensionPlaylistPreimageFactory ^%factory)
{
    factory = nullptr;
    IAIMPServicePlaylistManager2 *service = nullptr;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = GetService(&service);
        if (res == AimpActionResult::Ok && service != nullptr)
        {
            IAIMPExtensionPlaylistPreimageFactory *aimpFactory = nullptr;

            res = CheckResult(service->GetPreimageFactory(index, &aimpFactory));
            if (res == AimpActionResult::Ok && aimpFactory != nullptr)
            {
                factory = gcnew AimpExtensionPlaylistPreimageFactory(aimpFactory);
            }
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return res;
}

AimpActionResult PlayListManager::GetPreimageFactoryByID(String ^id, IAimpExtensionPlaylistPreimageFactory ^%factory)
{
    IAIMPServicePlaylistManager2 *service = nullptr;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        IAIMPString *idStr = AimpConverter::ToAimpString(id);
        res = GetService(&service);
        if (res == AimpActionResult::Ok && service != nullptr)
        {
            IAIMPExtensionPlaylistPreimageFactory *aimpFactory = nullptr;
            res = CheckResult(service->GetPreimageFactoryByID(idStr, &aimpFactory));

            if (res == AimpActionResult::Ok && aimpFactory != nullptr)
            {
                factory = gcnew AimpExtensionPlaylistPreimageFactory(aimpFactory);
            }
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return res;
}

int PlayListManager::GetPreimageFactoryCount()
{
    IAIMPServicePlaylistManager2 *service = nullptr;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = GetService(&service);
        if (res == AimpActionResult::Ok && service != nullptr)
        {
            return service->GetPreimageFactoryCount();
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return 0;
}

AimpActionResult PlayListManager::GetService(IAIMPServicePlaylistManager2** service)
{
    IAIMPServicePlaylistManager2 *srv = nullptr;
    AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager2, (void**)&srv));
    *service = srv;
    return res;
}
