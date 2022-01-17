// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "stdafx.h"
#include "AimpPlayer.h"
#include "Lyrics/AimpServiceLyrics.h"
#include "SDK/Action/AimpServiceActionManager.h"
#include "AlbumArt/AimpServiceAlbumArtCache.h"
#include "Core/AimpServiceShutdown.h"
#include "Core/AimpServiceVersionInfo.h"
#include "FileManager/AimpServiceFileInfoFormatter.h"
#include "MUI/AimpServiceMUI.h"
#include "Menu/AimpServiceMenuManager.h"
#include "Player/AimpServicePlayer.h"
#include "Player/AimpServicePlayerEqualizer.h"
#include "Player/AimpServicePlayerEqualizerPresets.h"
#include "Threading/AimpServiceThreads.h"

using namespace AIMP;
using namespace SDK;

AimpPlayer::AimpPlayer(ManagedAimpCore^ core, int pluginId, int applicationDomainId, bool isCrossDomain) {
    _managedAimpCore = core;
    _aimpCore = gcnew AimpCore(_managedAimpCore);
}

AimpPlayer::~AimpPlayer() {
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
    delete _serviceShutdown;
    delete _servicePlayer;
    delete _serviceVersionInfo;
    delete _serviceThreads;
    delete _serviceLyrics;
    delete _serviceFileTagEditor;
}

IAimpServicePlayerEqualizer^ AimpPlayer::ServicePlayerEqualizer::get() {
    if (_servicePlayerEqualizer == nullptr) {
        _servicePlayerEqualizer = gcnew AimpServicePlayerEqualizer(_managedAimpCore);
    }

    return _servicePlayerEqualizer;
}

IAimpServicePlayerEqualizerPresets^ AimpPlayer::ServicePlayerEqualizerPresets::get() {
    if (_servicePlayerEqualizerPresets == nullptr) {
        _servicePlayerEqualizerPresets = gcnew AimpServicePlayerEqualizerPresets(_managedAimpCore);
    }

    return _servicePlayerEqualizerPresets;
}

IAimpCore^ AimpPlayer::Core::get() {
    return _aimpCore;
}

MenuManager::IAimpServiceMenuManager^ AimpPlayer::ServiceMenuManager::get() {
    if (_menuManager == nullptr) {
        _menuManager = gcnew AimpServiceMenuManager(_managedAimpCore);
    }
    return _menuManager;
}

IAimpServiceActionManager^ AimpPlayer::ServiceActionManager::get() {
    if (_actionManager == nullptr) {
        _actionManager = gcnew AimpServiceActionManager(_managedAimpCore);
    }
    return _actionManager;
}

IAimpServiceMUI^ AimpPlayer::ServiceMui::get() {
    if (_muiManager == nullptr) {
        _muiManager = gcnew AimpServiceMUI(_managedAimpCore);
    }
    return _muiManager;
}

IAimpServiceAlbumArt^ AimpPlayer::ServiceAlbumArt::get() {
    if (_artManager == nullptr) {
        _artManager = gcnew AimpServiceAlbumArt(_managedAimpCore);
    }
    return _artManager;
}

IAimpServiceConfig^ AimpPlayer::ServiceConfig::get() {
    if (_serviceConfig == nullptr) {
        //IAIMPServiceConfig* config = static_cast<IAIMPServiceConfig*>(_managedAimpCore->QueryInterface(IID_IAIMPServiceConfig));
        _serviceConfig = gcnew AimpServiceConfig(_managedAimpCore);
    }
    return _serviceConfig;
}

IAimpServicePlaylistManager^ AimpPlayer::ServicePlaylistManager::get() {
    if (_playListManager == nullptr) {
        _playListManager = gcnew AimpServicePlaylistManager(static_cast<ManagedAimpCore^>(_managedAimpCore));
    }
    return _playListManager;
}

IAimpServicePlaybackQueue^ AimpPlayer::ServicePlaybackQueue::get() {
    if (_playbackQueueManager == nullptr) {
        _playbackQueueManager = gcnew AimpServicePlaybackQueue(static_cast<ManagedAimpCore^>(_managedAimpCore));
    }
    return _playbackQueueManager;
}

IAimpServicePlayer^ AimpPlayer::ServicePlayer::get() {
    if (_servicePlayer == nullptr) {
        _servicePlayer = gcnew AimpServicePlayer(_managedAimpCore);
    }
    return _servicePlayer;
}

IWin32Manager^ AimpPlayer::Win32Manager::get() {
    if (_win32Manager == nullptr) {
        _win32Manager = gcnew AIMP::Win32::Win32Manager();
    }

    return _win32Manager;
}

IAimpServiceOptionsDialog^ AimpPlayer::ServiceOptionsDialog::get() {
    if (_serviceOptionsDialogManager == nullptr) {
        _serviceOptionsDialogManager = gcnew AimpServiceOptionsDialog(static_cast<ManagedAimpCore^>(_managedAimpCore));
    }
    return _serviceOptionsDialogManager;
}

IAimpServiceMessageDispatcher^ AimpPlayer::ServiceMessageDispatcher::get() {
    if (_serviceMessageDispatcher == nullptr) {
        _serviceMessageDispatcher = gcnew AimpServiceMessageDispatcher(static_cast<ManagedAimpCore^>(_managedAimpCore));
    }

    return _serviceMessageDispatcher;
}

SDK::Core::IAimpServiceShutdown^ AimpPlayer::ServiceShutdown::get() {
    if (_serviceShutdown == nullptr) {
        _serviceShutdown = gcnew SDK::Core::AimpServiceShutdown(_managedAimpCore);
    }

    return _serviceShutdown;
}

SDK::Core::IAimpServiceVersionInfo^ AimpPlayer::ServiceVersionInfo::get() {
    if (_serviceVersionInfo == nullptr) {
        _serviceVersionInfo = gcnew AimpServiceVersionInfo(_managedAimpCore);
    }

    return _serviceVersionInfo;
}

IAimpServiceSynchronizer^ AimpPlayer::ServiceSynchronizer::get() {
    if (_serviceSynchronizer == nullptr) {
        _serviceSynchronizer = gcnew AimpServiceSynchronizer(_managedAimpCore);
    }

    return _serviceSynchronizer;
}

IAimpServiceThreadPool^ AimpPlayer::ServiceThreadPool::get() {
    if (_serviceThreadPool == nullptr) {
        _serviceThreadPool = gcnew AimpServiceThreadPool(_managedAimpCore);
    }

    return _serviceThreadPool;
}

IAimpServiceMusicLibrary^ AimpPlayer::ServiceMusicLibrary::get() {
    if (_serviceMusicLibrary == nullptr) {
        _serviceMusicLibrary = gcnew AimpServiceMusicLibrary(_managedAimpCore);
    }
    return _serviceMusicLibrary;
}

IAimpServiceMusicLibraryUI^ AimpPlayer::ServiceMusicLibraryUi::get() {
    if (_serviceMusicLibraryUi == nullptr) {
        _serviceMusicLibraryUi = gcnew AimpServiceMusicLibraryUI(_managedAimpCore);
    }
    return _serviceMusicLibraryUi;
}

IAimpServiceFileFormats^ AimpPlayer::ServiceFileFormats::get() {
    if (_serviceFileFormats == nullptr) {
        _serviceFileFormats = gcnew AimpServiceFileFormats(_managedAimpCore);
    }
    return _serviceFileFormats;
}

IAimpServiceFileInfo^ AimpPlayer::ServiceFileInfo::get() {
    if (_serviceFileInfo == nullptr) {
        _serviceFileInfo = gcnew AimpServiceFileInfo(_managedAimpCore);
    }
    return _serviceFileInfo;
}

IAimpServiceFileSystems^ AimpPlayer::ServiceFileSystems::get() {
    if (_serviceFileSystems == nullptr) {
        _serviceFileSystems = gcnew AimpServiceFileSystems(_managedAimpCore);
    }
    return _serviceFileSystems;
}

IAimpServiceFileStreaming^ AimpPlayer::ServiceFileStreaming::get() {
    if (_serviceFileStreaming == nullptr) {
        _serviceFileStreaming = gcnew AimpServiceFileStreaming(_managedAimpCore);
    }
    return _serviceFileStreaming;
}

IAimpServiceFileInfoFormatter^ AimpPlayer::ServiceFileInfoFormatter::get() {
    if (_serviceFileInfoFormatter == nullptr) {
        _serviceFileInfoFormatter = gcnew AimpServiceFileInfoFormatter(_managedAimpCore);
        //TODO: Complete it
    }
    return _serviceFileInfoFormatter;
}

IAimpServiceFileTagEditor^ AimpPlayer::ServiceFileTagEditor::get() {
    if (_serviceFileTagEditor == nullptr) {
        _serviceFileTagEditor = gcnew AimpServiceFileTagEditor(_managedAimpCore);
    }

    return _serviceFileTagEditor;
}

IAimpServiceLyrics^ AimpPlayer::ServiceLyrics::get() {
    if (_serviceLyrics == nullptr) {
        _serviceLyrics = gcnew AimpServiceLyrics(_managedAimpCore);
    }

    return _serviceLyrics;
}

IAimpServiceAlbumArtCache^ AimpPlayer::ServiceAlbumArtCache::get() {
    if (_serviceAlbumArtCache == nullptr) {
        _serviceAlbumArtCache = gcnew AimpServiceAlbumArtCache(_managedAimpCore);
    }

    return _serviceAlbumArtCache;
}

IAimpServiceThreads^ AimpPlayer::ServiceThreads::get() {
    if (_serviceThreads == nullptr) {
        _serviceThreads = gcnew AimpServiceThreads(_managedAimpCore);
    }

    return _serviceThreads;
}
