// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServicePlaylistManager.h"
#include "AimpExtensionPlaylistPreimageFactory.h"

using namespace AIMP::SDK;

AimpServicePlaylistManager::AimpServicePlaylistManager(ManagedAimpCore^ core) : BaseAimpService<IAIMPServicePlaylistManager2>(core)
{
}

IAimpPlaylistQueue^ AimpServicePlaylistManager::PlaylistQueue::get()
{
    IAIMPServicePlaylistManager2* service = GetAimpService();

    try
    {
        if (service != nullptr)
        {
            IAIMPPlaylistQueue* playListQueue = nullptr;
            if (CheckResult(service->QueryInterface(IID_IAIMPPlaylistQueue, reinterpret_cast<void**>(&playListQueue))) == AimpActionResult::OK)
            {
                IAIMPPlaylistQueue2* playListQueue2;
                service->QueryInterface(IID_IAIMPPlaylistQueue2, reinterpret_cast<void**>(&playListQueue2));
                return gcnew AimpPlaylistQueue(playListQueue, playListQueue2);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return nullptr;
}

void AimpServicePlaylistManager::PlaylistActivated::add(PlayListHandler^ onEvent)
{
    _onPlaylistActivated = onEvent;
}

void AimpServicePlaylistManager::PlaylistActivated::remove(PlayListHandler^ onEvent)
{
    _onPlaylistActivated = nullptr;
}

void AimpServicePlaylistManager::PlaylistActivated::raise(String^ playListName, String^ playListId)
{
    if (_onPlaylistActivated != nullptr)
    {
        _onPlaylistActivated(playListName, playListId);
    }
}

void AimpServicePlaylistManager::PlaylistAdded::add(PlayListHandler^ onEvent)
{
    if (_onPlaylistAdded == nullptr)
    {
        _onPlaylistAdded = onEvent;
    }
}

void AimpServicePlaylistManager::PlaylistAdded::remove(PlayListHandler^ onEvent)
{
    if (_onPlaylistAdded != nullptr)
    {
        _onPlaylistAdded = nullptr;
    }
}

void AimpServicePlaylistManager::PlaylistAdded::raise(String^ playListName, String^ playListId)
{
    if (_onPlaylistAdded != nullptr)
    {
        _onPlaylistAdded(playListName, playListId);
    }
}

void AimpServicePlaylistManager::PlaylistRemoved::add(PlayListHandler^ onEvent)
{
    _onPlaylistRemoved = onEvent;
}

void AimpServicePlaylistManager::PlaylistRemoved::remove(PlayListHandler^ onEvent)
{
    _onPlaylistRemoved = nullptr;
}

void AimpServicePlaylistManager::PlaylistRemoved::raise(String^ playListName, String^ playListId)
{
    if (_onPlaylistRemoved != nullptr)
    {
        _onPlaylistRemoved(playListName, playListId);
    }
}

AimpActionResult AimpServicePlaylistManager::CreatePlaylist(String^ name, bool isActive, IAimpPlaylist^% playList)
{
    playList = nullptr;
    AimpActionResult res = AimpActionResult::Fail;

    IAIMPPlaylist* pl = nullptr;
    IAIMPString* str = nullptr;
    IAIMPServicePlaylistManager2* service = GetAimpService();

    try
    {
        if (service != nullptr)
        {
            str = AimpConverter::ToAimpString(name);
            res = CheckResult(service->CreatePlaylist(str, BOOL(isActive), &pl));

            if (res == AimpActionResult::OK && pl != nullptr)
            {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return res;
}

AimpActionResult AimpServicePlaylistManager::CreatePlaylistFromFile(String^ fileName, bool isActive, IAimpPlaylist^% playList)
{
    playList = nullptr;
    IAIMPPlaylist* pl = nullptr;
    IAIMPString* str = nullptr;
    IAIMPServicePlaylistManager2* service = GetAimpService();
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        if (service != nullptr)
        {
            str = AimpConverter::ToAimpString(fileName);
            res = CheckResult(service->CreatePlaylistFromFile(str, BOOL(isActive), &pl));

            if (res == AimpActionResult::OK && pl != nullptr)
            {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return res;
}

AimpActionResult AimpServicePlaylistManager::GetActivePlaylist(IAimpPlaylist^% playList)
{
    playList = nullptr;
    IAIMPPlaylist* pl = nullptr;
    IAIMPServicePlaylistManager2* service = GetAimpService();
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        if (service != nullptr)
        {
            res = CheckResult(service->GetActivePlaylist(&pl));
            if (res == AimpActionResult::OK)
            {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return res;
}

AimpActionResult AimpServicePlaylistManager::GetLoadedPlaylist(int index, IAimpPlaylist^% playList)
{
    playList = nullptr;
    IAIMPPlaylist* pl = nullptr;
    IAIMPServicePlaylistManager2* service = GetAimpService();
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        if (service != nullptr)
        {
            res = CheckResult(service->GetLoadedPlaylist(index, &pl));
            if (res == AimpActionResult::OK)
            {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return res;
}

AimpActionResult AimpServicePlaylistManager::GetPlayablePlaylist(IAimpPlaylist^% playList)
{
    playList = nullptr;
    IAIMPPlaylist* pl = nullptr;
    IAIMPServicePlaylistManager2* service = GetAimpService();
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        if (service != nullptr)
        {
            res = CheckResult(service->GetPlayablePlaylist(&pl));
            if (res == AimpActionResult::OK)
            {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return res;
}

AimpActionResult AimpServicePlaylistManager::GetLoadedPlaylistById(System::String^ id, IAimpPlaylist^% playList)
{
    playList = nullptr;
    IAIMPPlaylist* pl = nullptr;
    IAIMPString* key = nullptr;
    IAIMPServicePlaylistManager2* service = GetAimpService();
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        if (service != nullptr)
        {
            key = AimpConverter::ToAimpString(id);
            res = CheckResult(service->GetLoadedPlaylistByID(key, &pl));
            if (res == AimpActionResult::OK)
            {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally
    {
        ReleaseObject(key);
        ReleaseObject(service);
    }

    return res;
}

AimpActionResult AimpServicePlaylistManager::GetLoadedPlaylistByName(String^ name, IAimpPlaylist^% playList)
{
    playList = nullptr;
    IAIMPPlaylist* pl = nullptr;
    IAIMPString* key = nullptr;
    IAIMPServicePlaylistManager2* service = nullptr;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        if (service != nullptr)
        {
            key = AimpConverter::ToAimpString(name);
            res = CheckResult(service->GetLoadedPlaylistByName(key, &pl));

            if (res == AimpActionResult::OK)
            {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally
    {
        ReleaseObject(key);
        ReleaseObject(service);
    }

    return res;
}

int AimpServicePlaylistManager::GetLoadedPlaylistCount()
{
    IAIMPServicePlaylistManager2* service = GetAimpService();
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        if (service != nullptr)
        {
            return service->GetLoadedPlaylistCount();
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return 0;
}

AimpActionResult AimpServicePlaylistManager::SetActivePlaylist(IAimpPlaylist^ playList)
{
    IAIMPServicePlaylistManager2* service = GetAimpService();
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        if (service != nullptr)
        {
            res = CheckResult(service->SetActivePlaylist(static_cast<AimpPlayList^>(playList)->InternalAimpObject));
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return res;
}

//void AimpServicePlaylistManager::OnPlaylistActivated(IAIMPPlaylist* playlist)
//{
//    IAIMPPropertyList* properties;
//    playlist->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
//    String ^name = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_NAME);
//    String ^id = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_ID);
//    this->PlaylistActivated(name, id);
//    properties->Release();
//    properties = nullptr;
//}
//
//void AimpServicePlaylistManager::OnPlaylistAdded(IAIMPPlaylist* playlist)
//{
//    IAIMPPropertyList* properties;
//    playlist->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
//    String ^name = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_NAME);
//    String ^id = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_ID);
//    this->PlaylistAdded(name, id);
//    properties->Release();
//    properties = nullptr;
//}
//
//void AimpServicePlaylistManager::OnPlaylistRemoved(IAIMPPlaylist* playlist)
//{
//    IAIMPPropertyList* properties;
//    playlist->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
//    String ^name = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_NAME);
//    String ^id = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_ID);
//    this->PlaylistRemoved(name, id);
//    properties->Release();
//    properties = nullptr;
//}

AimpActionResult AimpServicePlaylistManager::GetPreimageFactory(int index, IAimpExtensionPlaylistPreimageFactory^% factory)
{
    factory = nullptr;
    IAIMPServicePlaylistManager2* service = GetAimpService();
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        if (service != nullptr)
        {
            IAIMPExtensionPlaylistPreimageFactory* aimpFactory = nullptr;

            res = CheckResult(service->GetPreimageFactory(index, &aimpFactory));
            if (res == AimpActionResult::OK && aimpFactory != nullptr)
            {
                factory = gcnew AimpExtensionPlaylistPreimageFactory(aimpFactory);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return res;
}

AimpActionResult AimpServicePlaylistManager::GetPreimageFactoryByID(String^ id, IAimpExtensionPlaylistPreimageFactory^% factory)
{
    IAIMPServicePlaylistManager2* service = GetAimpService();
    AimpActionResult res = AimpActionResult::Fail;
    IAIMPString* idStr = AimpConverter::ToAimpString(id);
    IAIMPExtensionPlaylistPreimageFactory* aimpFactory = nullptr;

    try
    {
        if (service != nullptr)
        {
            res = CheckResult(service->GetPreimageFactoryByID(idStr, &aimpFactory));

            if (res == AimpActionResult::OK && aimpFactory != nullptr)
            {
                factory = gcnew AimpExtensionPlaylistPreimageFactory(aimpFactory);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(idStr);
        ReleaseObject(aimpFactory);
    }

    return res;
}

int AimpServicePlaylistManager::GetPreimageFactoryCount()
{
    IAIMPServicePlaylistManager2* service = GetAimpService();
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        if (service != nullptr)
        {
            return service->GetPreimageFactoryCount();
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return 0;
}

IAIMPServicePlaylistManager2* AimpServicePlaylistManager::GetAimpService()
{
    IAIMPServicePlaylistManager2* service = nullptr;
    GetService(IID_IAIMPServicePlaylistManager2, &service);
    return service;
}
