// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
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
    using namespace SDK;

    namespace SDK
    {
        using namespace System;
        using namespace Generic;

        using namespace SDK;
        using namespace Playlist;

        delegate void ChangeHandler(MessageDispatcher::AimpCoreMessageType, int);

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

            virtual ActionResultType GetPath(MessageDispatcher::AimpCorePathType pathType, String^% path);

            virtual HRESULT SendMessage(MessageDispatcher::AimpCoreMessageType message, int value, Object^ obj);

            virtual event PlayListHandler^ PlaylistActivated;

            virtual event PlayListHandler^ PlaylistAdded;

            virtual event PlayListHandler^ PlaylistRemoved;

            virtual event Playback::AimpCheckUrl^ CheckUrl;

        internal:
            IAIMPActionEvent* CreateActionEvent();

            HRESULT GetService(REFIID iid, void** service);

            static IUnknown* QueryInterface(REFIID iid);

            HRESULT RegisterExtension(GUID iid, IAimpExtension^ extension);

            HRESULT UnregisterExtension(IAimpExtension^ extension);

            HRESULT UnregisterExtension(IUnknown* extension);

            static IAIMPCore* GetAimpCore();

            HRESULT ShowNotification(bool autoHide, String^ notification);

            ActionResultType CreateStream(IAIMPStream** stream);

            ActionResultType CreateAction(IAIMPAction** action);

            bool OnCheckUrl(String^ % url);

            HRESULT CreateMenuItem(IAIMPMenuItem** item);

            OptionsDialogFrameExtension* GetOptionsFrame();

        public:
            virtual void OnPlaylistActivated(IAIMPPlaylist* playlist);

            virtual void OnPlaylistAdded(IAIMPPlaylist* playlist);

            virtual void OnPlaylistRemoved(IAIMPPlaylist* playlist);

        private:
            static IAIMPCore* _core = nullptr;
            IAIMPExtensionPlayerHook* _playerHook = nullptr;
            //EventHelper* _nativeEventHelper;
            //Callback* _coreMessageCallback;
            //Callback* _playListActivatedCallback;
            IAIMPServiceMessageDispatcher* _messageDispatcher = nullptr;
            IAIMPMessageHook* _hook = nullptr;
            List<AimpEventsDelegate^>^ _coreMessage;
            List<AIMP::SDK::Playlist::PlayListHandler^>^ _playListActivatedHandlers;
            OptionsDialogFrameExtension* _optionsFrame = nullptr;
            AimpExtensionAlbumArtCatalog* _albumArtCatalogExtension = nullptr;
            AimpExtensionAlbumArtProvider* _albumArtProviderExtension = nullptr;
            AimpExtensionEmbeddedVisualization* _embeddedVisualization = nullptr;
            AimpExtensionCustomVisualization* _customVisualization = nullptr;
            AimpExtensionPlaylistManagerListener* _playlistManagerListener = nullptr;
            AimpExtensionDataStorage* _musicLibraryDataStorage = nullptr;
            InternalAimpExtensionFileInfoProvider* _fileInfoExtensionProvider = nullptr;
            InternalAimpExtensionFileSystem* _extensionFileSystem = nullptr;
            InternalAimpExtensionPlaylistPreimageFactory* _extensionPlaylistPreimageFactory = nullptr;

            AIMP::SDK::Playlist::PlayListHandler^ _playlistAdded;
            AIMP::SDK::Playlist::PlayListHandler^ _playlistRemoved;
            AIMP::SDK::Playback::AimpCheckUrl^ _checkUrl;
        };
    }
}
