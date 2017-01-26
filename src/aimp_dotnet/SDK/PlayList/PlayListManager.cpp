#include "Stdafx.h"
#include "PlayListManager.h"

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

IAimpPlayListQueue^ PlayListManager::PlayListQueue::get()
{
    if (_playListQueue == nullptr)
    {
        AimpActionResult res = AimpActionResult::Fail;
        IAIMPServicePlaylistManager *service;
        res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
        if (res == AimpActionResult::Ok)
        {
            IAIMPPlaylistQueue *playListQueue;
            if (CheckResult(service->QueryInterface(IID_IAIMPPlaylistQueue, (void**)&playListQueue)) == AimpActionResult::Ok)
            {
                IAIMPPlaylistQueue2 *playListQueue2;
                service->QueryInterface(IID_IAIMPPlaylistQueue2, (void**)&playListQueue2);

                _playListQueue = gcnew AimpPlaylistQueue(playListQueue, playListQueue2);
            }
        }
    }

    return _playListQueue;
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

AIMP::SDK::AimpActionResult AIMP::SDK::PlayListManager::CreatePlaylist(System::String^ name, bool isActive, IAimpPlayList ^%playList)
{
    playList = nullptr;
    AimpActionResult res = AimpActionResult::Fail;

    IAIMPPlaylist *pl = NULL;
    IAIMPString *str = NULL;
    IAIMPServicePlaylistManager *service;
    res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));

    if (res == AimpActionResult::Ok && service != NULL)
    {
        str = AimpExtension::GetAimpString(name);
        res = CheckResult(service->CreatePlaylist(str, (BOOL)isActive, &pl));

        if (res == AimpActionResult::Ok)
        {
            playList = gcnew AimpPlayList(pl);
        }
    }

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

    return res;
}

AIMP::SDK::AimpActionResult AIMP::SDK::PlayListManager::CreatePlaylistFromFile(System::String^ fileName, bool isActive, IAimpPlayList ^%playList)
{
    playList = nullptr;

    IAIMPPlaylist *pl = NULL;
    IAIMPString *str = NULL;
    IAIMPServicePlaylistManager *service;

    AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
    if (service != NULL && res == AimpActionResult::Ok)
    {
        str = AimpExtension::GetAimpString(fileName);
        res = CheckResult(service->CreatePlaylistFromFile(str, (BOOL)isActive, &pl));

        if (res == AimpActionResult::Ok)
        {
            playList = gcnew AimpPlayList(pl);
        }
    }

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

    return res;
}

AIMP::SDK::AimpActionResult AIMP::SDK::PlayListManager::GetActivePlaylist(IAimpPlayList ^%playList)
{
    playList = nullptr;
    IAIMPPlaylist *pl = NULL;
    IAIMPServicePlaylistManager *service;

    AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
    if (service != NULL && res == AimpActionResult::Ok)
    {
        res = CheckResult(service->GetActivePlaylist(&pl));
        if (res == AimpActionResult::Ok)
        {
            playList = gcnew AimpPlayList(pl);
        }
    }

    if (service != NULL)
    {
        service->Release();
        service = NULL;
    }

    return res;
}

AIMP::SDK::AimpActionResult AIMP::SDK::PlayListManager::GetLoadedPlaylist(int index, IAimpPlayList ^%playList)
{
    playList = nullptr;
    IAIMPPlaylist *pl = NULL;
    IAIMPServicePlaylistManager *service;

    AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));

    if (service != NULL && res == AimpActionResult::Ok)
    {
        res = CheckResult(service->GetLoadedPlaylist(index, &pl));
        if (res == AimpActionResult::Ok)
        {
            playList = gcnew AimpPlayList(pl);
        }
    }

    if (service != NULL)
    {
        service->Release();
        service = NULL;
    }

    return res;
}

AIMP::SDK::AimpActionResult AIMP::SDK::PlayListManager::GetPlayablePlaylist(IAimpPlayList ^%playList)
{
    playList = nullptr;

    IAIMPPlaylist *pl = NULL;
    IAIMPServicePlaylistManager *service;

    AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
    if (res == AimpActionResult::Ok)
    {
        res = CheckResult(service->GetPlayablePlaylist(&pl));
        if (res == AimpActionResult::Ok)
        {
            playList = gcnew AimpPlayList(pl);
        }
    }

    return res;
}

AIMP::SDK::AimpActionResult AIMP::SDK::PlayListManager::GetLoadedPlaylistById(System::String^ id, IAimpPlayList ^%playList)
{
    playList = nullptr;
    IAIMPPlaylist *pl = NULL;
    IAIMPString *key = NULL;
    IAIMPServicePlaylistManager *service;

    AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
    if (res == AimpActionResult::Ok)
    {
        key = AimpExtension::GetAimpString(id);
        res = CheckResult(service->GetLoadedPlaylistByID(key, &pl));
        if (res == AimpActionResult::Ok)
        {
            playList = gcnew AimpPlayList(pl);
        }
    }

    if (pl != NULL)
    {
        pl->Release();
        pl = NULL;
    }

    if (key != NULL)
    {
        key->Release();
        key = NULL;
    }

    return res;
}

AIMP::SDK::AimpActionResult AIMP::SDK::PlayListManager::GetLoadedPlaylistByName(System::String^ name, IAimpPlayList ^%playList)
{
    playList = nullptr;
    IAIMPPlaylist *pl = NULL;
    IAIMPString *key = NULL;
    IAIMPServicePlaylistManager *service;

    AimpActionResult res = AimpActionResult::Fail;

    res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));

    if (res == AimpActionResult::Ok)
    {
        key = AimpExtension::GetAimpString(name);
        res = CheckResult(service->GetLoadedPlaylistByName(key, &pl));

        if (res == AimpActionResult::Ok)
        {
            playList = gcnew AimpPlayList(pl);
        }
    }

    if (pl != NULL)
    {
        pl->Release();
        pl = NULL;
    }

    if (key != NULL)
    {
        key->Release();
        key = NULL;
    }

    return res;
}

int AIMP::SDK::PlayListManager::GetLoadedPlaylistCount()
{
    IAIMPServicePlaylistManager *service;
    AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
    return service->GetLoadedPlaylistCount();
}

void AIMP::SDK::PlayListManager::SetActivePlaylist(IAimpPlayList^ playList)
{
    IAIMPServicePlaylistManager *service;
    AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
    CheckResult(service->SetActivePlaylist(((AimpPlayList^)playList)->InternalAimpObject));
}

void AIMP::SDK::PlayListManager::OnPlaylistActivated(IAIMPPlaylist* playlist)
{
    IAIMPPropertyList *properties;
    playlist->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
    String ^name = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_NAME);
    String ^id = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_ID);
    this->PlaylistActivated(name, id);
    properties->Release();
    properties = NULL;
}

void AIMP::SDK::PlayListManager::OnPlaylistAdded(IAIMPPlaylist* playlist)
{
    IAIMPPropertyList *properties;
    playlist->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
    String ^name = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_NAME);
    String ^id = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_ID);
    this->PlaylistAdded(name, id);
    properties->Release();
    properties = NULL;
}

void AIMP::SDK::PlayListManager::OnPlaylistRemoved(IAIMPPlaylist* playlist)
{
    IAIMPPropertyList *properties;
    playlist->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
    String ^name = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_NAME);
    String ^id = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_ID);
    this->PlaylistRemoved(name, id);
    properties->Release();
    properties = NULL;
}
