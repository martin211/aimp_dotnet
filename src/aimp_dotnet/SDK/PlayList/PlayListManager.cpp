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
