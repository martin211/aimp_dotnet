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

#pragma once
#include <Unknwnbase.h>
#include "AimpSdk.h"
#include "SDK\Options\OptionsDialogFrameExtension.h"
#include "SDK\AlbumArt\AimpExtensionAlbumArtCatalog.h"
#include "SDK\AlbumArt\AimpExtensionAlbumArtProvider.h"
#include "SDK\PlayList\AimpExtensionPlaylistManagerListener.h"
#include "SDK\Visuals\AimpExtensionEmbeddedVisualization.h"
#include "SDK\Visuals\AimpExtensionCustomVisualization.h"
#include "SDK\MusicLibrary\AimpExtensionDataStorage.h"
#include "SDK\MusicLibrary\InternalAimpGroupingTreeDataProvider.h"
#include "SDK\FileManager\InternalAimpExtensionFileInfoProvider.h"
#include "SDK\FileManager\InternalAimpExtensionFileSystem.h"
#include "SDK\Visuals\AimpServiceVisualizations.h"
#include "SDK\PlayList\Internal\InternalAimpExtensionPlaylistPreimageFactory.h"

namespace AIMP
{
    using namespace System;
    using namespace AIMP::SDK;

    namespace SDK
    {
        using namespace System;
        using namespace System::Collections::Generic;

        using namespace AIMP::SDK;
        using namespace AIMP::SDK::Playlist;

        delegate void ChangeHandler(AimpMessages::AimpCoreMessageType, int);

        /// <summary>
        /// Wrapper on IAIMPCore interface.
        /// </summary>
        [Serializable]
        public ref class ManagedAimpCore
        {

        public:
            /// <summary>
            /// Initializes a new instance of the <see cref="ManagedAimpCore"/> class.
            /// </summary>
            /// <param name="core">The core.</param>
            ManagedAimpCore(IAIMPCore* core);

            /// <summary>
            /// Finalizes an instance of the <see cref="ManagedAimpCore"/> class.
            /// </summary>
            ~ManagedAimpCore();

            virtual AimpActionResult GetPath(AimpMessages::AimpCorePathType pathType, String ^%path);

            virtual HRESULT SendMessage(AimpMessages::AimpCoreMessageType message, int value, Object ^obj);

            virtual event AimpEventsDelegate^ CoreMessage;

            virtual event AimpEventsDelegate^ InternalCoreMessage;

            virtual event AIMP::SDK::Playlist::PlayListHandler ^PlaylistActivated;

            virtual event AIMP::SDK::Playlist::PlayListHandler ^PlaylistAdded;

            virtual event AIMP::SDK::Playlist::PlayListHandler ^PlaylistRemoved;

            virtual event AIMP::SDK::Playback::AimpCheckUrl ^CheckUrl;

            void OnCoreMessage(AimpMessages::AimpCoreMessageType param1, int param2);

            void OnInternalCoreMessage(AIMP::SDK::AimpMessages::AimpCoreMessageType param1, int param2);

        internal:
            IAIMPActionEvent* CreateActionEvent();

            HRESULT GetService(REFIID iid, void** service);

            static IUnknown *QueryInterface(REFIID iid);

            HRESULT RegisterExtension(GUID iid, IAimpExtension^ extension);

            HRESULT UnregisterExtension(IAimpExtension^ extension);

            HRESULT UnregisterExtension(IUnknown* extension);

            static IAIMPCore* GetAimpCore();

            HRESULT ShowNotification(bool autoHide, String ^notification);

            AimpActionResult CreateStream(IAIMPStream **stream);

            AimpActionResult CreateAction(IAIMPAction **action);

            bool OnCheckUrl(String^ %url);

            HRESULT CreateMenuItem(IAIMPMenuItem **item);

            OptionsDialogFrameExtension* GetOptionsFrame();

        public:
            virtual void OnPlaylistActivated(IAIMPPlaylist* playlist);

            virtual void OnPlaylistAdded(IAIMPPlaylist* playlist);

            virtual void OnPlaylistRemoved(IAIMPPlaylist* playlist);
           
        private:
            static IAIMPCore* _core = nullptr;
            IAIMPExtensionPlayerHook *_playerHook = nullptr;
            //EventHelper* _nativeEventHelper;
            //Callback* _coreMessageCallback;
            //Callback* _playListActivatedCallback;
            IAIMPServiceMessageDispatcher* _messageDispatcher = nullptr;
            IAIMPMessageHook* _hook = nullptr;
            List<AimpEventsDelegate^> ^_coreMessage;
            List<AIMP::SDK::Playlist::PlayListHandler^> ^_playListActivatedHandlers;
            OptionsDialogFrameExtension* _optionsFrame = nullptr;
            AimpExtensionAlbumArtCatalog* _albumArtCatalogExtension = nullptr;
            AimpExtensionAlbumArtProvider* _albumArtProviderExtension = nullptr;
            AimpExtensionEmbeddedVisualization* _embeddedVisualization = nullptr;
            AimpExtensionCustomVisualization* _customVisualization = nullptr;
            AimpExtensionPlaylistManagerListener *_playlistManagerListener = nullptr;
            AimpExtensionDataStorage* _musicLibraryDataStorage = nullptr;
            InternalAimpExtensionFileInfoProvider *_fileInfoExtensionProvider = nullptr;
            InternalAimpExtensionFileSystem *_extensionFileSystem = nullptr;
            InternalAimpExtensionPlaylistPreimageFactory* _extensionPlaylistPreimageFactory = nullptr;

            AIMP::SDK::Playlist::PlayListHandler ^_playlistAdded;
            AIMP::SDK::Playlist::PlayListHandler ^_playlistRemoved;
            AIMP::SDK::Playback::AimpCheckUrl ^_checkUrl;
        };
    }
}
