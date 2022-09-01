// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

#include "SDK\Action\AimpServiceActionManager.h"
#include "SDK\AlbumArt\AimpServiceAlbumArt.h"
#include "SDK\Configuration\AimpConfigurationManager.h"
#include "SDK\FileManager\AimpFileInfo.h"
#include "SDK\Win32\Win32Manager.h"
#include "SDK\PlayList\AimpPlayListItem.h"
#include "SDK\PlayList\AimpPlayList.h"
#include "SDK\PlayList\AimpServicePlaylistManager.h"
#include "SDK\Playback\AimpServicePlaybackQueue.h"
#include "SDK\Threading\AimpServiceSynchronizer.h"
#include "AimpCore.h"
#include "SDK\Options\AimpServiceOptionsDialog.h"
#include "SDK\Threading\AimpServiceSynchronizer.h"
#include "SDK\Threading\AimpServiceThreadPool.h"
#include "SDK\MusicLibrary\AimpServiceMusicLibrary.h"
#include "SDK\MusicLibrary\AimpServiceMusicLibraryUI.h"
#include "SDK\FileManager\AimpServiceFileFormats.h"
#include "SDK\FileManager\AimpServiceFileInfo.h"
#include "SDK\FileManager\AimpServiceFileSystems.h"
#include "SDK\FileManager\AimpServiceFileStreaming.h"
#include "SDK\MessageDispatcher\AimpServiceMessageDispatcher.h";
#include "SDK\TagEditor\AimpServiceFileTagEditor.h"
#include "SDK\Action\AimpServiceActionManager.h";

using namespace AIMP::SDK;

namespace AIMP {
    using namespace System;
    using namespace InteropServices;
    using namespace SDK;
    using namespace Configuration;
    using namespace Playlist;
    using namespace Win32;
    using namespace Player;
    using namespace Threading;
    using namespace MessageDispatcher;
    using namespace TagEditor;
    using namespace Services;

    private ref class AimpPlayer :
        public MarshalByRefObject,
        public IAimpPlayer {
    private:
        IAIMPMessageHook* aimp_message_hook_;

        ManagedAimpCore^ _managedAimpCore;
        IAimpCore^ _aimpCore;
        AimpEventsDelegate^ _coreMessage;
        IAimpServiceMenuManager^ _menuManager;
        IAimpServiceActionManager^ _actionManager;
        MUIManager::IAimpServiceMUI^ _muiManager;
        IAimpServiceAlbumArt^ _artManager;
        IAimpServiceConfig^ _serviceConfig;
        IWin32Manager^ _win32Manager;
        IAimpServicePlaylistManager^ _playListManager;
        IAimpServicePlaybackQueue^ _playbackQueueManager;
        IAimpServiceOptionsDialog^ _serviceOptionsDialogManager;
        AimpPlayerState _state;
        IAimpServiceSynchronizer^ _serviceSynchronizer;
        IAimpServiceThreadPool^ _serviceThreadPool;
        IAimpServiceMusicLibrary^ _serviceMusicLibrary;
        IAimpServiceMusicLibraryUI^ _serviceMusicLibraryUi;
        IAimpServiceFileFormats^ _serviceFileFormats;
        IAimpServiceFileInfo^ _serviceFileInfo;
        IAimpServiceFileSystems^ _serviceFileSystems;
        IAimpServiceFileStreaming^ _serviceFileStreaming;
        IAimpServiceFileInfoFormatter^ _serviceFileInfoFormatter;
        IAimpServiceMessageDispatcher^ _serviceMessageDispatcher;
        IAimpServiceFileTagEditor^ _serviceFileTagEditor;
        IAimpServiceLyrics^ _serviceLyrics;
        IAimpServiceAlbumArtCache^ _serviceAlbumArtCache;
        IAimpServiceThreads^ _serviceThreads;
        Core::IAimpServiceVersionInfo^ _serviceVersionInfo;
        Core::IAimpServiceShutdown^ _serviceShutdown;
        IAimpServicePlayer^ _servicePlayer;
        IAimpServicePlayerEqualizer^ _servicePlayerEqualizer;
        IAimpServicePlayerEqualizerPresets^ _servicePlayerEqualizerPresets;
        IAimpServiceWaveform^ _serviceWaveForm;
        IAimpServiceFileInfoFormatterUtils^ _serviceFileInfoFormatterUtils;
        IAimpServiceFileURI^ _serviceFileURI;
        IAimpServiceFileURI2^ _serviceFileURI2;
    public:
        /// <summary>
        /// Initializes a new instance of the <see cref="AIMP3Controller{TConvAlloc}" /> class.
        /// </summary>
        /// <param name="core">The aimp core.</param>
        /// <param name="pluginId">The plugin identifier.</param>
        /// <param name="applicationDomainId">The application domain identifier.</param>
        /// <param name="isCrossDomain">The is cross domain.</param>
        AimpPlayer(ManagedAimpCore^ core, int pluginId, int applicationDomainId, bool isCrossDomain);

        ~AimpPlayer();

        property IAimpServiceFileInfoFormatterUtils^ ServiceFileInfoFormatterUtils
        {
            virtual IAimpServiceFileInfoFormatterUtils^ get();
        }
        property IAimpServiceFileURI^ ServiceFileUri
        {
            virtual IAimpServiceFileURI^ get();
        }
        property IAimpServiceFileURI2^ ServiceFileUri2
        {
            virtual IAimpServiceFileURI2^ get();
        }

        property IAimpServiceWaveform^ ServiceWaveform {
            virtual IAimpServiceWaveform^ get();
        }

        property IAimpServicePlayerEqualizer^ ServicePlayerEqualizer {
            virtual IAimpServicePlayerEqualizer^ get();
        }

        property IAimpServicePlayerEqualizerPresets^ ServicePlayerEqualizerPresets {
            virtual IAimpServicePlayerEqualizerPresets^ get();
        }

        /// <summary>
        /// Gets Player core.
        /// </summary>
        virtual property IAimpCore^ Core {
            IAimpCore^ get();
        }

        /// <summary>
        /// Gets player menu manager.
        /// </summary>
        virtual property IAimpServiceMenuManager^ ServiceMenuManager {
            IAimpServiceMenuManager^ get();
        }

        /// <summary>
        /// Gets player action manager.
        /// </summary>
        virtual property IAimpServiceActionManager^ ServiceActionManager {
            IAimpServiceActionManager^ get();
        }

        /// <summary>
        /// Gets the MUI manager.
        /// </summary>
        virtual property MUIManager::IAimpServiceMUI^ ServiceMui {
            MUIManager::IAimpServiceMUI^ get();
        }

        virtual property IAimpServiceAlbumArt^ ServiceAlbumArt
        {
            IAimpServiceAlbumArt^ get();
        }

        virtual property IAimpServiceConfig^ ServiceConfig {
            IAimpServiceConfig^ get();
        }

        virtual property IAimpServicePlaylistManager^ ServicePlaylistManager {
            IAimpServicePlaylistManager^ get();
        }

        virtual property IAimpServicePlaybackQueue^ ServicePlaybackQueue {
            IAimpServicePlaybackQueue^ get();
        }

        virtual property IAimpServicePlayer^ ServicePlayer {
            IAimpServicePlayer^ get();
        }

        virtual property IWin32Manager^ Win32Manager {
            IWin32Manager^ get();
        }

        virtual property IAimpServiceOptionsDialog^ ServiceOptionsDialog {
            IAimpServiceOptionsDialog^ get();
        }

        virtual property IAimpServiceMessageDispatcher^ ServiceMessageDispatcher {
            IAimpServiceMessageDispatcher^ get();
        }

        property SDK::Core::IAimpServiceShutdown^ ServiceShutdown { virtual SDK::Core::IAimpServiceShutdown^ get(); }

        property SDK::Core::IAimpServiceVersionInfo^ ServiceVersionInfo { virtual SDK::Core::IAimpServiceVersionInfo^ get(); }

        virtual property IAimpServiceSynchronizer^ ServiceSynchronizer {
            IAimpServiceSynchronizer^ get();
        }

        virtual property IAimpServiceThreadPool^ ServiceThreadPool {
            IAimpServiceThreadPool^ get();
        }

        virtual property IAimpServiceMusicLibrary^ ServiceMusicLibrary {
            IAimpServiceMusicLibrary^ get();
        }

        virtual property IAimpServiceMusicLibraryUI^ ServiceMusicLibraryUi {
            IAimpServiceMusicLibraryUI^ get();
        }

        virtual property IAimpServiceFileFormats^ ServiceFileFormats {
            IAimpServiceFileFormats^ get();
        }

        virtual property IAimpServiceFileInfo^ ServiceFileInfo {
            IAimpServiceFileInfo^ get();
        }

        virtual property IAimpServiceFileSystems^ ServiceFileSystems {
            IAimpServiceFileSystems^ get();
        }

        virtual property IAimpServiceFileStreaming^ ServiceFileStreaming {
            IAimpServiceFileStreaming^ get();
        }

        virtual property IAimpServiceFileInfoFormatter^ ServiceFileInfoFormatter {
            IAimpServiceFileInfoFormatter^ get();
        }

        virtual property IAimpServiceFileTagEditor^ ServiceFileTagEditor {
            IAimpServiceFileTagEditor^ get();
        }

        virtual property IAimpServiceLyrics^ ServiceLyrics {
            IAimpServiceLyrics^ get();
        }

        virtual property IAimpServiceAlbumArtCache^ ServiceAlbumArtCache {
            IAimpServiceAlbumArtCache^ get();
        }

        virtual property IAimpServiceThreads^ ServiceThreads {
            IAimpServiceThreads^ get();
        }
    };
}
