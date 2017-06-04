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

PlayListManager::PlayListManager(ManagedAimpCore ^core) : AimpBaseManager<IAIMPServicePlaylistManager>(core)
{
    _core->RegisterExtension(IID_IAIMPServicePlaylistManager, this);
}

PlayListManager::~PlayListManager()
{
    this->!PlayListManager();
}

PlayListManager::!PlayListManager()
{
    _core->UnregisterExtension(this);
}

IAimpPlaylistQueue^ PlayListManager::PlaylistQueue::get()
{
    IAIMPServicePlaylistManager *service = NULL;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
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
        if (service != NULL)
        {
            service->Release();
            service = NULL;
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

    IAIMPPlaylist *pl = NULL;
    IAIMPString *str = NULL;
    IAIMPServicePlaylistManager *service = NULL;

    try
    {
        res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
        if (res == AimpActionResult::Ok && service != NULL)
        {
            str = AimpConverter::ToAimpString(name);
            res = CheckResult(service->CreatePlaylist(str, (BOOL)isActive, &pl));

            if (res == AimpActionResult::Ok && pl != NULL)
            {
                playList = gcnew AimpPlayList(pl);
            }

            str->Release();
            str = NULL;
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }
    }

    return res;
}

AimpActionResult PlayListManager::CreatePlaylistFromFile(System::String^ fileName, bool isActive, IAimpPlaylist ^%playList)
{
    playList = nullptr;
    IAIMPPlaylist *pl = NULL;
    IAIMPString *str = NULL;
    IAIMPServicePlaylistManager *service = NULL;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
        if (res == AimpActionResult::Ok && service != NULL)
        {
            str = AimpConverter::ToAimpString(fileName);
            res = CheckResult(service->CreatePlaylistFromFile(str, (BOOL)isActive, &pl));

            if (res == AimpActionResult::Ok && pl != NULL)
            {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }

        if (str != NULL)
        {
            str->Release();
            str = NULL;
        }
    }

    return res;
}

AimpActionResult PlayListManager::GetActivePlaylist(IAimpPlaylist ^%playList)
{
    playList = nullptr;
    IAIMPPlaylist *pl = NULL;
    IAIMPServicePlaylistManager *service = NULL;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
        if (res == AimpActionResult::Ok && service != NULL)
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
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }
    }

    return res;
}

AimpActionResult PlayListManager::GetLoadedPlaylist(int index, IAimpPlaylist ^%playList)
{
    playList = nullptr;
    IAIMPPlaylist *pl = NULL;
    IAIMPServicePlaylistManager *service = NULL;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));

        if (res == AimpActionResult::Ok && service != NULL)
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
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }
    }

    return res;
}

AimpActionResult PlayListManager::GetPlayablePlaylist(IAimpPlaylist ^%playList)
{
    playList = nullptr;
    IAIMPPlaylist *pl = NULL;
    IAIMPServicePlaylistManager *service = NULL;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
        if (res == AimpActionResult::Ok && service != NULL)
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
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }
    }

    return res;
}

AimpActionResult PlayListManager::GetLoadedPlaylistById(System::String^ id, IAimpPlaylist ^%playList)
{
    playList = nullptr;
    IAIMPPlaylist *pl = NULL;
    IAIMPString *key = NULL;
    IAIMPServicePlaylistManager *service = NULL;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
        if (res == AimpActionResult::Ok && service != NULL)
        {
            key = AimpConverter::ToAimpString(id);
            res = CheckResult(service->GetLoadedPlaylistByID(key, &pl));
            if (res == AimpActionResult::Ok)
            {
                playList = gcnew AimpPlayList(pl);
            }

            key->Release();
            key = NULL;
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }
    }

    return res;
}

AimpActionResult PlayListManager::GetLoadedPlaylistByName(System::String^ name, IAimpPlaylist ^%playList)
{
    playList = nullptr;
    IAIMPPlaylist *pl = NULL;
    IAIMPString *key = NULL;
    IAIMPServicePlaylistManager *service = NULL;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
        if (res == AimpActionResult::Ok && service != NULL)
        {
            key = AimpConverter::ToAimpString(name);
            res = CheckResult(service->GetLoadedPlaylistByName(key, &pl));

            if (res == AimpActionResult::Ok)
            {
                playList = gcnew AimpPlayList(pl);
            }

            key->Release();
            key = NULL;
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }
    }

    return res;
}

int PlayListManager::GetLoadedPlaylistCount()
{
    IAIMPServicePlaylistManager *service = NULL;

    try
    {
        AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
        if (res == AimpActionResult::Ok && service != NULL)
        {
            return service->GetLoadedPlaylistCount();
        }

        return 0;
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }
    }
}

AimpActionResult PlayListManager::SetActivePlaylist(IAimpPlaylist^ playList)
{
    IAIMPServicePlaylistManager *service = NULL;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
        if (res == AimpActionResult::Ok && service != NULL)
        {
            res = CheckResult(service->SetActivePlaylist(((AimpPlayList^)playList)->InternalAimpObject));
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }
    }

    return res;
}

void PlayListManager::OnPlaylistActivated(IAIMPPlaylist* playlist)
{
    IAIMPPropertyList *properties;
    playlist->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
    String ^name = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_NAME);
    String ^id = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_ID);
    this->PlaylistActivated(name, id);
    properties->Release();
    properties = NULL;
}

void PlayListManager::OnPlaylistAdded(IAIMPPlaylist* playlist)
{
    IAIMPPropertyList *properties;
    playlist->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
    String ^name = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_NAME);
    String ^id = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_ID);
    this->PlaylistAdded(name, id);
    properties->Release();
    properties = NULL;
}

void PlayListManager::OnPlaylistRemoved(IAIMPPlaylist* playlist)
{
    IAIMPPropertyList *properties;
    playlist->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
    String ^name = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_NAME);
    String ^id = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_ID);
    this->PlaylistRemoved(name, id);
    properties->Release();
    properties = NULL;
}

AimpActionResult PlayListManager::GetPreimageFactory(int index, IAimpExtensionPlaylistPreimageFactory ^%factory)
{
    factory = nullptr;
    IAIMPServicePlaylistManager2 *service = NULL;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager2, (void**)&service));
        if (res == AimpActionResult::Ok && service != NULL)
        {
            IAIMPExtensionPlaylistPreimageFactory *aimpFactory = NULL;

            res = CheckResult(service->GetPreimageFactory(index, &aimpFactory));
            if (res == AimpActionResult::Ok && aimpFactory != NULL)
            {
                factory = gcnew AimpExtensionPlaylistPreimageFactory(aimpFactory);
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }
    }

    return res;
}

AimpActionResult PlayListManager::GetPreimageFactoryByID(String ^id, IAimpExtensionPlaylistPreimageFactory ^%factory)
{
    IAIMPServicePlaylistManager2 *service = NULL;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        IAIMPString *idStr = AimpConverter::ToAimpString(id);
        res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager2, (void**)&service));
        if (res == AimpActionResult::Ok && service != NULL)
        {
            IAIMPExtensionPlaylistPreimageFactory *aimpFactory = NULL;
            res = CheckResult(service->GetPreimageFactoryByID(idStr, &aimpFactory));

            if (res == AimpActionResult::Ok && aimpFactory != NULL)
            {
                factory = gcnew AimpExtensionPlaylistPreimageFactory(aimpFactory);
            }
        }
    }
    finally
    {
    
    }

    return res;
}


int PlayListManager::GetPreimageFactoryCount()
{
    IAIMPServicePlaylistManager2 *service = NULL;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager2, (void**)&service));
        if (res == AimpActionResult::Ok && service != NULL)
        {
            return service->GetPreimageFactoryCount();
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }
    }

    return 0;
}
