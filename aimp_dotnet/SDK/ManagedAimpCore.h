#pragma once
#include "..\AimpSdk.h"
#include <Unknwnbase.h>
#include "..\Extensions\OptionsDialogFrameExtension.h"
#include "..\Extensions\AimpExtensionAlbumArtCatalog.h"
#include "..\Extensions\AimpExtensionAlbumArtProvider.h"
#include "..\Extensions\AimpExtensionPlaylistManagerListener.h"
#include "..\SDK\Visuals\AimpExtensionEmbeddedVisualization.h"
#include "..\SDK\Visuals\AimpExtensionCustomVisualization.h"
#include "..\SDK\MusicLibrary\AimpExtensionDataStorage.h"
#include "..\SDK\MusicLibrary\InternalAimpGroupingTreeDataProvider.h"
#include "..\SDK\FileManager\InternalAimpExtensionFileInfoProvider.h"

namespace AIMP
{
    using namespace System;
    using namespace AIMP::SDK;

    namespace SDK
    {
        using namespace System;
        using namespace System::Collections::Generic;

        using namespace AIMP::SDK;
        using namespace AIMP::SDK::PlayList;

        delegate void ChangeHandler(AimpMessages::AimpCoreMessageType, int);

        /// <summary>
        /// Wrapper on IAIMPCore interface.
        /// </summary>
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

            virtual event AIMP::SDK::PlayList::PlayListHandler ^PlaylistActivated;

            virtual event AIMP::SDK::PlayList::PlayListHandler ^PlaylistAdded;

            virtual event AIMP::SDK::PlayList::PlayListHandler ^PlaylistRemoved;

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

            IAIMPStream* CreateStream();

            bool OnCheckUrl(String^ %url);

            HRESULT CreateMenuItem(IAIMPMenuItem **item);

            OptionsDialogFrameExtension* GetOptionsFrame();

        public:
            virtual void OnPlaylistActivated(IAIMPPlaylist* playlist);

            virtual void OnPlaylistAdded(IAIMPPlaylist* playlist);

            virtual void OnPlaylistRemoved(IAIMPPlaylist* playlist);
           
        private:
            static IAIMPCore* _core;
            IAIMPExtensionPlayerHook *_playerHook;
            //EventHelper* _nativeEventHelper;
            //Callback* _coreMessageCallback;
            //Callback* _playListActivatedCallback;
            IAIMPServiceMessageDispatcher* _messageDispatcher;
            IAIMPMessageHook* _hook;
            List<AimpEventsDelegate^> ^_coreMessage;
            List<AIMP::SDK::PlayList::PlayListHandler^> ^_playListActivatedHandlers;
            OptionsDialogFrameExtension* _optionsFrame;
            AimpExtensionAlbumArtCatalog* _albumArtCatalogExtension;
            AimpExtensionAlbumArtProvider* _albumArtProviderExtension;
            AimpExtensionEmbeddedVisualization* _embeddedVisualization;
            AimpExtensionCustomVisualization* _customVisualization;
            AimpExtensionPlaylistManagerListener *_playlistManagerListener;
            AimpExtensionDataStorage *_musicLibraryDataStorage;
            InternalAimpExtensionFileInfoProvider *_fileInfoExtensionProvider;

            AIMP::SDK::PlayList::PlayListHandler ^_playlistAdded;
            AIMP::SDK::PlayList::PlayListHandler ^_playlistRemoved;
            AIMP::SDK::Playback::AimpCheckUrl ^_checkUrl;
        };
    }
}