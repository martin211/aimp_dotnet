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

#pragma once
#include "SDK\BaseManager.h"
#include "AimpPlayListQueue.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace Collections;
        using namespace Generic;

        using namespace SDK;
        using namespace Playlist;

        public ref class PlayListManager :
            public AimpBaseManager<IAIMPServicePlaylistManager2>,
            public IAimpPlaylistManager2
        {
        private:
            PlayListHandler^ _onPlaylistActivated;
            PlayListHandler^ _onPlaylistAdded;
            PlayListHandler^ _onPlaylistRemoved;

        public:
            explicit PlayListManager(ManagedAimpCore^ core);

            ~PlayListManager();

            !PlayListManager();

            virtual property IAimpPlaylistQueue^ PlaylistQueue
            {
                IAimpPlaylistQueue^ get();
            }

            virtual event PlayListHandler^ PlaylistActivated
            {
                virtual void add(PlayListHandler^ onEvent);
                virtual void remove(PlayListHandler^ onEvent);
                virtual void raise(String^ playListName, String^ playListId);
            }

            virtual event PlayListHandler^ PlaylistAdded
            {
                virtual void add(PlayListHandler^ onEvent);
                virtual void remove(PlayListHandler^ onEvent);
                virtual void raise(String^ playListName, String^ playListId);
            }

            virtual event PlayListHandler^ PlaylistRemoved
            {
                virtual void add(PlayListHandler^ onEvent);
                virtual void remove(PlayListHandler^ onEvent);
                void raise(String^ playListName, String^ playListId);
            }

            virtual AimpActionResult CreatePlaylist(String^ name, bool isActive, IAimpPlaylist^% playList);

            virtual AimpActionResult CreatePlaylistFromFile(String^ fileName, bool isActive, IAimpPlaylist^% playList);

            virtual AimpActionResult GetActivePlaylist(IAimpPlaylist^% playList);

            virtual AimpActionResult GetLoadedPlaylist(int index, IAimpPlaylist^% playList);

            virtual AimpActionResult GetPlayablePlaylist(IAimpPlaylist^% playList);

            virtual AimpActionResult GetLoadedPlaylistById(String^ id, IAimpPlaylist^% playList);

            virtual AimpActionResult GetLoadedPlaylistByName(String^ name, IAimpPlaylist^% playList);

            virtual int GetLoadedPlaylistCount();

            virtual AimpActionResult SetActivePlaylist(IAimpPlaylist^ playList);

            virtual AimpActionResult GetPreimageFactory(int index, IAimpExtensionPlaylistPreimageFactory^% factory);

            virtual AimpActionResult
            GetPreimageFactoryByID(String^ id, IAimpExtensionPlaylistPreimageFactory^% factory);

            virtual int GetPreimageFactoryCount();

            //******** IAimpExtensionPlaylistManagerListenerExecutor ********

            //virtual void OnPlaylistActivated(IAIMPPlaylist* playlist);

            //virtual void OnPlaylistAdded(IAIMPPlaylist* playlist);

            //virtual void OnPlaylistRemoved(IAIMPPlaylist* playlist);

        private:
            virtual AimpActionResult GetService(IAIMPServicePlaylistManager2** service);
        };
    }
}
