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

#include "stdafx.h"
#include "AimpPlayer.h"

using namespace AIMP;
using namespace AIMP::SDK;

AimpPlayer::AimpPlayer(ManagedAimpCore ^core, int pluginId, int applicationDomainId, bool isCrossDomain)
{
    _managedAimpCore = core;
    IAIMPServicePlayer* ps;
    ((ManagedAimpCore^)_managedAimpCore)->GetService(IID_IAIMPServicePlayer, reinterpret_cast<void**>(&ps));
    _player = ps;

    _aimpCore = gcnew AimpCore(_managedAimpCore);
    ((AimpCore^)_aimpCore)->InternalCoreMessage += gcnew AimpEventsDelegate(this, &AIMP::AimpPlayer::OnInternalCoreMessage);
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
}

IAimpCore^ AimpPlayer::Core::get()
{
    return _aimpCore;
}

IAimpServiceMenuManager^ AimpPlayer::MenuManager::get()
{
    if (_menuManager == nullptr)
    {
        _menuManager = gcnew AimpMenuManager(_managedAimpCore);
    }
    return _menuManager;
}

IAimpServiceActionManager^ AimpPlayer::ActionManager::get()
{
    if (_actionManager == nullptr)
    {
        _actionManager = gcnew AIMP::AimpActionManager((ManagedAimpCore^)_managedAimpCore);
    }
    return _actionManager;
}

IAimpMUIManager^ AimpPlayer::MUIManager::get()
{
    if (_muiManager == nullptr)
    {
        _muiManager = gcnew AIMP::AimpMIUManager((ManagedAimpCore^)_managedAimpCore);
    }
    return _muiManager;
}

IAimpAlbumArtManager^ AimpPlayer::AlbumArtManager::get()
{
    if (_artManager == nullptr)
    {
        _artManager = gcnew AIMP::AimpAlbumArtManager((ManagedAimpCore^)_managedAimpCore);
    }
    return _artManager;
}

IAimpServiceConfig^ AimpPlayer::ServiceConfig::get()
{
    if (_serviceConfig == nullptr)
    {
        IAIMPServiceConfig* config = (IAIMPServiceConfig*)_managedAimpCore->QueryInterface(IID_IAIMPServiceConfig);
        _serviceConfig = gcnew AIMP::AimpServiceConfig(config);
    }
    return _serviceConfig;
}

IAimpPlaylistManager2^ AimpPlayer::PlaylistManager::get()
{
    if (_playListManager == nullptr)
    {
        _playListManager = gcnew AIMP::SDK::PlayListManager((ManagedAimpCore^)_managedAimpCore);
    }
    return _playListManager;
}

IAimpPlaybackQueueService^ AimpPlayer::PlaybackQueueManager::get()
{
    if (_playbackQueueManager == nullptr)
    {
        _playbackQueueManager = gcnew AIMP::SDK::AimpServicePlaybackQueue((ManagedAimpCore^)_managedAimpCore);
        ((ManagedAimpCore^)_managedAimpCore)->CheckUrl += gcnew AIMP::SDK::Playback::AimpCheckUrl(this, &AIMP::AimpPlayer::OnCheckUrl);
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
    if (Utils::CheckResult(_player->GetMute(&value)) == AimpActionResult::Ok)
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
    if (Utils::CheckResult(_player->GetVolume(&value)) == AimpActionResult::Ok)
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
    if (Utils::CheckResult(_player->GetDuration(&value)) == AimpActionResult::Ok)
    {
        return value;
    }
    return 0;
}

double AimpPlayer::Position::get()
{
    double value;
    if (Utils::CheckResult(_player->GetPosition(&value)) == AimpActionResult::Ok)
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
    return (AimpPlayerState)state;
}

IAimpFileInfo^ AimpPlayer::CurrentFileInfo::get()
{
    IAIMPFileInfo* fi = NULL;
    if (Utils::CheckResult(_player->GetInfo(&fi)) == AimpActionResult::Ok && fi != NULL)
    {
        return gcnew AimpFileInfo(fi);
    }
    return nullptr;
}

IAimpPlaylistItem^ AimpPlayer::CurrentPlaylistItem::get()
{
    IAIMPPlaylistItem* item = NULL;
    if (Utils::CheckResult(_player->GetPlaylistItem(&item)) == AimpActionResult::Ok && item != NULL)
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
        _serviceOptionsDialogManager = gcnew AIMP::SDK::AimpServiceOptionsDialog((ManagedAimpCore^)_managedAimpCore);
    }
    return _serviceOptionsDialogManager;
}

void AimpPlayer::StateChanged::add(EventHandler<Player::StateChangedEventArgs^>^ onAction)
{
    if (this->_onStateChanged == nullptr)
    {
        _onStateChanged = (EventHandler<Player::StateChangedEventArgs^>^)Delegate::Combine(_onStateChanged, onAction);
    }
}

void AimpPlayer::StateChanged::remove(EventHandler<Player::StateChangedEventArgs^>^ onAction)
{
    bool tmp = this->_onStateChanged != nullptr;
    if (tmp)
    {
        _onStateChanged = (EventHandler<Player::StateChangedEventArgs^>^)Delegate::Remove(_onStateChanged, onAction);
    }
}

void AimpPlayer::StateChanged::raise(Object ^sender, Player::StateChangedEventArgs^ state)
{
    if (this->_onStateChanged != nullptr)
    {
        _onStateChanged(sender, state);
    }
}

void AimpPlayer::LanguageChanged::add(EventHandler^ onAction)
{
    bool tmp = _onLanguageChanged == nullptr;
    if (tmp)
    {
        _onLanguageChanged = (EventHandler^)Delegate::Combine(_onLanguageChanged, onAction);
    }
}

void AimpPlayer::LanguageChanged::remove(EventHandler^ onAction)
{
    bool tmp = _onLanguageChanged != nullptr;
    if (tmp)
    {
        _onLanguageChanged = (EventHandler^)Delegate::Remove(_onLanguageChanged, onAction);
    }
}

void AimpPlayer::LanguageChanged::raise(Object ^sender, EventArgs ^e)
{
    if (_onLanguageChanged != nullptr)
    {
        _onLanguageChanged(sender, e);
    }
}

void AimpPlayer::TrackChanged::add(EventHandler^ onAction)
{
    bool tmp = _onTrackChanged == nullptr;
    if (tmp)
    {
        _onTrackChanged = (EventHandler^)Delegate::Combine(_onTrackChanged, onAction);
    }
}

void AimpPlayer::TrackChanged::remove(EventHandler^ onAction)
{
    bool tmp = _onTrackChanged != nullptr;
    if (tmp)
    {
        _onTrackChanged = (EventHandler^)Delegate::Remove(_onTrackChanged, onAction);
    }
}

void AimpPlayer::TrackChanged::raise(Object ^sender, EventArgs ^e)
{
    if (_onTrackChanged != nullptr)
    {
        _onTrackChanged(sender, e);
    }
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

void AimpPlayer::Play(IAimpPlaybackQueueItem ^queueItem)
{
    _player->Play(((AimpPlaybackQueueItem^)queueItem)->InternalAimpObject);
}

void AimpPlayer::Play(IAimpPlaylistItem ^playListItem)
{
    _player->Play2(((AimpPlaylistItem^)playListItem)->InternalAimpObject);
}

void AimpPlayer::Play(IAimpPlaylist^ playList)
{
    _player->Play3(((AimpPlayList^)playList)->InternalAimpObject);
}

IAimpServiceSynchronizer^ AimpPlayer::ServiceSynchronizer::get()
{
    if (_serviceSynchronizer == nullptr)
    {
        _serviceSynchronizer = gcnew AimpServiceSynchronizer((ManagedAimpCore^)_managedAimpCore);
    }
    return _serviceSynchronizer;
}

IAimpServiceThreadPool^ AimpPlayer::ServiceThreadPool::get()
{
    if (_serviceThreadPool == nullptr)
    {
        _serviceThreadPool = gcnew AimpServiceThreadPool((ManagedAimpCore^)_managedAimpCore);
    }
    return _serviceThreadPool;
}

IAimpServiceMusicLibrary^ AimpPlayer::ServiceMusicLibrary::get()
{
    if (_serviceMusicLibrary == nullptr)
    {
        _serviceMusicLibrary = gcnew AIMP::SDK::AimpServiceMusicLibrary((ManagedAimpCore^)_managedAimpCore);
    }
    return _serviceMusicLibrary;
}

IAimpServiceMusicLibraryUI^ AimpPlayer::ServiceMusicLibraryUi::get()
{
    if (_serviceMusicLibraryUi == nullptr)
    {
        _serviceMusicLibraryUi = gcnew AimpServiceMusicLibraryUI((ManagedAimpCore^)_managedAimpCore);
    }
    return _serviceMusicLibraryUi;
}

IAimpServiceFileFormats^ AimpPlayer::ServiceFileFormats::get()
{
    if (_serviceFileFormats == nullptr)
    {
        _serviceFileFormats = gcnew AimpServiceFileFormats((ManagedAimpCore^)_managedAimpCore);
    }
    return _serviceFileFormats;
}

IAimpServiceFileInfo^ AimpPlayer::ServiceFileInfo::get()
{
    if (_serviceFileInfo == nullptr)
    {
        _serviceFileInfo = gcnew AimpServiceFileInfo((ManagedAimpCore^)_managedAimpCore);
    }
    return _serviceFileInfo;
}

IAimpServiceFileSystems^ AimpPlayer::ServiceFileSystems::get()
{
    if (_serviceFileSystems == nullptr)
    {
        _serviceFileSystems = gcnew AimpServiceFileSystems((ManagedAimpCore^)_managedAimpCore);
    }
    return _serviceFileSystems;
}

IAimpServiceFileStreaming^ AimpPlayer::ServiceFileStreaming::get()
{
    if (_serviceFileStreaming == nullptr)
    {
        _serviceFileStreaming = gcnew AimpServiceFileStreaming((ManagedAimpCore^)_managedAimpCore);
    }
    return _serviceFileStreaming;
}

IAimpServiceFileInfoFormatter^ AimpPlayer::ServiceFileInfoFormatter::get()
{
    if (_serviceFileInfoFormatter == nullptr)
    {
        //TODO: Complete it
    }
    return _serviceFileInfoFormatter;
}

bool AimpPlayer::OnCheckUrl(String^ %url)
{
    return ((AIMP::SDK::AimpServicePlaybackQueue^)this->_playbackQueueManager)->RaiseCheckUrl(url);
}

void AimpPlayer::OnInternalCoreMessage(AimpMessages::AimpCoreMessageType param1, int param2)
{
    if (param1 == AimpMessages::AimpCoreMessageType::AIMP_MSG_EVENT_PLAYER_STATE && _state != this->State)
    {
        _state = this->State;
        StateChanged(this, gcnew AIMP::SDK::Player::StateChangedEventArgs(_state));
    }
    else if (param1 == AimpMessages::AimpCoreMessageType::AIMP_MSG_EVENT_LANGUAGE)
    {
        LanguageChanged(this, EventArgs::Empty);
    }
    else if (param1 == AimpMessages::AimpCoreMessageType::AIMP_MSG_EVENT_STREAM_START || param1 == AimpMessages::AimpCoreMessageType::AIMP_MSG_EVENT_STREAM_START_SUBTRACK)
    {
        TrackChanged(this, EventArgs::Empty);
    }
}
