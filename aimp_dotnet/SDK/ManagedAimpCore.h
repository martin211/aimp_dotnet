#pragma once
#include "..\AimpSdk.h"
#include <Unknwnbase.h>
#include "EventHelper.h"
#include "..\Extensions\OptionsDialogFrameExtension.h"
#include "..\Extensions\AimpExtensionAlbumArtCatalog.h"
#include "..\Extensions\AimpExtensionAlbumArtProvider.h"
#include "..\SDK\Visuals\AimpExtensionEmbeddedVisualization.h"
#include "..\SDK\Visuals\AimpExtensionCustomVisualization.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::Collections::Generic;

        using namespace AIMP::SDK;
        using namespace AIMP::SDK::Extensions;
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

            virtual event AIMP::SDK::Extensions::PlayListHandler ^PlaylistActivated;

            virtual event AIMP::SDK::Extensions::PlayListHandler ^PlaylistAdded;

            virtual event AIMP::SDK::Extensions::PlayListHandler ^PlaylistRemoved;

            virtual event AIMP::SDK::Playback::AimpCheckUrl ^CheckUrl;

            void OnCoreMessage(AimpMessages::AimpCoreMessageType param1, int param2);

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

            void OnPlaylistActivated(IAIMPPlaylist *playlist);

            void OnPlayListAdded(IAIMPPlaylist *playlist);

            void OnPlayListRemoved(IAIMPPlaylist *playlist);

            bool OnCheckUrl(String^ %url);

            HRESULT CreateMenuItem(IAIMPMenuItem **item);

            OptionsDialogFrameExtension* GetOptionsFrame();
           
        private:
            static IAIMPCore* _core;
            IAIMPExtensionPlayerHook *_playerHook;
            EventHelper* _nativeEventHelper;
            Callback* _coreMessageCallback;
            Callback* _playListActivatedCallback;
            IAIMPServiceMessageDispatcher* _messageDispatcher;
            IAIMPMessageHook* _hook;
            List<AimpEventsDelegate^> ^_coreMessage;
            List<AIMP::SDK::Extensions::PlayListHandler^> ^_playListActivatedHandlers;
            OptionsDialogFrameExtension* _optionsFrame;
            AimpExtensionAlbumArtCatalog* _albumArtCatalogExtension;
            AimpExtensionAlbumArtProvider* _albumArtProviderExtension;
            AimpExtensionEmbeddedVisualization* _embeddedVisualization;
            AimpExtensionCustomVisualization* _customVisualization;

            AIMP::SDK::Extensions::PlayListHandler ^_playlistAdded;
            AIMP::SDK::Extensions::PlayListHandler ^_playlistRemoved;
            AIMP::SDK::Playback::AimpCheckUrl ^_checkUrl;
        };
    }
}