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

#include "stdafx.h"
#include "AimpPlayer.h"
#include "Playback/AimpPlaybackQueueItem.h"
#include "Lyrics/AimpServiceLyrics.h"
#include "SDK/Action/AimpServiceActionManager.h"
#include "AlbumArt/AimpServiceAlbumArtCache.h"
#include "FileManager/AimpServiceFileInfoFormatter.h"
#include "MUI/AimpServiceMUI.h"
#include "Menu/AimpServiceMenuManager.h"

using namespace AIMP;
using namespace SDK;

AimpPlayer::AimpPlayer(ManagedAimpCore^ core, int pluginId, int applicationDomainId, bool isCrossDomain)
{
    _managedAimpCore = core;
    IAIMPServicePlayer* ps;
    static_cast<ManagedAimpCore^>(_managedAimpCore)->GetService(IID_IAIMPServicePlayer, reinterpret_cast<void**>(&ps));
    _player = ps;

    _aimpCore = gcnew AimpCore(_managedAimpCore);
}

AimpPlayer::~AimpPlayer()
{
    _player->Release();
    delete _aimpCore;
    delete _menuManager;
    delete _actionManager;
    delete _muiManager;
    delete _artManager;
    delete _serviceConfig;
    delete _playListManager;
    delete _playbackQueueManager;
    delete _serviceSynchronizer;
    delete _serviceThreadPool;
    delete _serviceMusicLibrary;
    delete _serviceMusicLibraryUi;
    delete _serviceFileFormats;
    delete _serviceFileInfo;
    delete _serviceFileInfoFormatter;
    delete _serviceAlbumArtCache;
}

IAimpCore^ AimpPlayer::Core::get()
{
    return _aimpCore;
}

MenuManager::IAimpServiceMenuManager^ AimpPlayer::MenuManager::get()
{
    if (_menuManager == nullptr)
    {
        _menuManager = gcnew AimpServiceMenuManager(_managedAimpCore);
    }
    return _menuManager;
}

IAimpServiceActionManager^ AimpPlayer::ActionManager::get()
{
    if (_actionManager == nullptr)
    {
        _actionManager = gcnew AimpServiceActionManager(_managedAimpCore);
    }
    return _actionManager;
}

IAimpMUIManager^ AimpPlayer::MUIManager::get()
{
    if (_muiManager == nullptr)
    {
        _muiManager = gcnew AimpServiceMUI(_managedAimpCore);
    }
    return _muiManager;
}

IAimpServiceAlbumArt^ AimpPlayer::ServiceAlbumArt::get()
{
    if (_artManager == nullptr)
    {
        _artManager = gcnew AimpServiceAlbumArt(_managedAimpCore);
    }
    return _artManager;
}

IAimpServiceConfig^ AimpPlayer::ServiceConfig::get()
{
    if (_serviceConfig == nullptr)
    {
        //IAIMPServiceConfig* config = static_cast<IAIMPServiceConfig*>(_managedAimpCore->QueryInterface(IID_IAIMPServiceConfig));
        _serviceConfig = gcnew AimpServiceConfig(_managedAimpCore);
    }
    return _serviceConfig;
}

IAimpPlaylistManager2^ AimpPlayer::PlaylistManager::get()
{
    if (_playListManager == nullptr)
    {
        _playListManager = gcnew AimpServicePlaylistManager(static_cast<ManagedAimpCore^>(_managedAimpCore));
    }
    return _playListManager;
}

IAimpPlaybackQueueService^ AimpPlayer::PlaybackQueueManager::get()
{
    if (_playbackQueueManager == nullptr)
    {
        _playbackQueueManager = gcnew AimpServicePlaybackQueue(static_cast<ManagedAimpCore^>(_managedAimpCore));
        static_cast<ManagedAimpCore^>(_managedAimpCore)->CheckUrl += gcnew AimpCheckUrl(this, &AimpPlayer::OnCheckUrl);
    }
    return _playbackQueueManager;
}

IAIMPServicePlayer* AimpPlayer::ServicePlayer::get()
{
    return _player;
}

bool AimpPlayer::IsMute::get()
{
    bool value;
    if (Utils::CheckResult(_player->GetMute(&value)) == ActionResultType::OK)
    {
        return value;
    }
    return false;
}

void AimpPlayer::IsMute::set(bool value)
{
    _player->SetMute(value);
}

float AimpPlayer::Volume::get()
{
    float value;
    if (Utils::CheckResult(_player->GetVolume(&value)) == ActionResultType::OK)
    {
        return value;
    }
    return 0;
}

void AimpPlayer::Volume::set(float value)
{
    _player->SetVolume(value);
}

double AimpPlayer::Duration::get()
{
    double value;
    if (Utils::CheckResult(_player->GetDuration(&value)) == ActionResultType::OK)
    {
        return value;
    }
    return 0;
}

double AimpPlayer::Position::get()
{
    double value;
    if (Utils::CheckResult(_player->GetPosition(&value)) == ActionResultType::OK)
    {
        return value;
    }
    return 0;
}

void AimpPlayer::Position::set(double value)
{
    _player->SetPosition(value);
}

AimpPlayerState AimpPlayer::State::get()
{
    int state = _player->GetState();
    return static_cast<AimpPlayerState>(state);
}

IAimpFileInfo^ AimpPlayer::CurrentFileInfo::get()
{
    IAIMPFileInfo* fi = nullptr;
    if (Utils::CheckResult(_player->GetInfo(&fi)) == ActionResultType::OK && fi != nullptr)
    {
        return gcnew AimpFileInfo(fi);
    }

    return nullptr;
}

IAimpPlaylistItem^ AimpPlayer::CurrentPlaylistItem::get()
{
    IAIMPPlaylistItem* item = nullptr;
    if (Utils::CheckResult(_player->GetPlaylistItem(&item)) == ActionResultType::OK && item != nullptr)
    {
        return gcnew AimpPlaylistItem(item);
    }

    return nullptr;
}

IWin32Manager^ AimpPlayer::Win32Manager::get()
{
    if (_win32Manager == nullptr)
    {
        _win32Manager = gcnew AIMP::Win32::Win32Manager();
    }

    return _win32Manager;
}

IAimpServiceOptionsDialog^ AimpPlayer::ServiceOptionsDialog::get()
{
    if (_serviceOptionsDialogManager == nullptr)
    {
        _serviceOptionsDialogManager = gcnew AimpServiceOptionsDialog(static_cast<ManagedAimpCore^>(_managedAimpCore));
    }
    return _serviceOptionsDialogManager;
}

IAimpServiceMessageDispatcher^ AimpPlayer::ServiceMessageDispatcher::get()
{
    if (_serviceMessageDispatcher == nullptr)
    {
        _serviceMessageDispatcher = gcnew AimpServiceMessageDispatcher(static_cast<ManagedAimpCore^>(_managedAimpCore));
    }

    return _serviceMessageDispatcher;
}

void AimpPlayer::Pause()
{
    _player->Pause();
}

void AimpPlayer::Stop()
{
    _player->Stop();
}

void AimpPlayer::Resume()
{
    _player->Resume();
}

void AimpPlayer::StopAfterTrack()
{
    _player->StopAfterTrack();
}

void AimpPlayer::GoToNext()
{
    _player->GoToNext();
}

void AimpPlayer::GoToPrev()
{
    _player->GoToPrev();
}

void AimpPlayer::Play(IAimpPlaybackQueueItem^ queueItem)
{
    _player->Play(static_cast<AimpPlaybackQueueItem^>(queueItem)->InternalAimpObject);
}

void AimpPlayer::Play(IAimpPlaylistItem^ playListItem)
{
    _player->Play2(static_cast<AimpPlaylistItem^>(playListItem)->InternalAimpObject);
}

void AimpPlayer::Play(IAimpPlaylist^ playList)
{
    _player->Play3(static_cast<AimpPlayList^>(playList)->InternalAimpObject);
}

IAimpServiceSynchronizer^ AimpPlayer::ServiceSynchronizer::get()
{
    if (_serviceSynchronizer == nullptr)
    {
        _serviceSynchronizer = gcnew AimpServiceSynchronizer(_managedAimpCore);
    }

    return _serviceSynchronizer;
}

IAimpServiceThreadPool^ AimpPlayer::ServiceThreadPool::get()
{
    if (_serviceThreadPool == nullptr)
    {
        _serviceThreadPool = gcnew AimpServiceThreadPool(_managedAimpCore);
    }

    return _serviceThreadPool;
}

IAimpServiceMusicLibrary^ AimpPlayer::ServiceMusicLibrary::get()
{
    if (_serviceMusicLibrary == nullptr)
    {
        _serviceMusicLibrary = gcnew AimpServiceMusicLibrary(_managedAimpCore);
    }
    return _serviceMusicLibrary;
}

IAimpServiceMusicLibraryUI^ AimpPlayer::ServiceMusicLibraryUi::get()
{
    if (_serviceMusicLibraryUi == nullptr)
    {
        _serviceMusicLibraryUi = gcnew AimpServiceMusicLibraryUI(_managedAimpCore);
    }
    return _serviceMusicLibraryUi;
}

IAimpServiceFileFormats^ AimpPlayer::ServiceFileFormats::get()
{
    if (_serviceFileFormats == nullptr)
    {
        _serviceFileFormats = gcnew AimpServiceFileFormats(_managedAimpCore);
    }
    return _serviceFileFormats;
}

IAimpServiceFileInfo^ AimpPlayer::ServiceFileInfo::get()
{
    if (_serviceFileInfo == nullptr)
    {
        _serviceFileInfo = gcnew AimpServiceFileInfo(_managedAimpCore);
    }
    return _serviceFileInfo;
}

IAimpServiceFileSystems^ AimpPlayer::ServiceFileSystems::get()
{
    if (_serviceFileSystems == nullptr)
    {
        _serviceFileSystems = gcnew AimpServiceFileSystems(_managedAimpCore);
    }
    return _serviceFileSystems;
}

IAimpServiceFileStreaming^ AimpPlayer::ServiceFileStreaming::get()
{
    if (_serviceFileStreaming == nullptr)
    {
        _serviceFileStreaming = gcnew AimpServiceFileStreaming(_managedAimpCore);
    }
    return _serviceFileStreaming;
}

IAimpServiceFileInfoFormatter^ AimpPlayer::ServiceFileInfoFormatter::get()
{
    if (_serviceFileInfoFormatter == nullptr)
    {
        _serviceFileInfoFormatter = gcnew AimpServiceFileInfoFormatter(_managedAimpCore);
        //TODO: Complete it
    }
    return _serviceFileInfoFormatter;
}

IAimpServiceFileTagEditor^ AimpPlayer::ServiceFileTagEditor::get()
{
    if (_serviceFileTagEditor == nullptr)
    {
        _serviceFileTagEditor = gcnew AimpServiceFileTagEditor(_managedAimpCore);
    }

    return _serviceFileTagEditor;
}

bool AimpPlayer::OnCheckUrl(String^ % url)
{
    return static_cast<AimpServicePlaybackQueue^>(this->_playbackQueueManager)->RaiseCheckUrl(url);
}

IAimpServiceLyrics^ AimpPlayer::ServiceLyrics::get()
{
    if (_serviceLyrics == nullptr)
    {
        _serviceLyrics = gcnew AimpServiceLyrics(_managedAimpCore);
    }

    return _serviceLyrics;
}

IAimpServiceAlbumArtCache^ AimpPlayer::ServiceAlbumArtCache::get()
{
    if(_serviceAlbumArtCache == nullptr)
    {
        _serviceAlbumArtCache = gcnew AimpServiceAlbumArtCache(_managedAimpCore);
    }

    return _serviceAlbumArtCache;
}
