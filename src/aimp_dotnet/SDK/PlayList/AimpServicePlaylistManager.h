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

        public ref class AimpServicePlaylistManager :
            public BaseAimpService<IAIMPServicePlaylistManager2>,
            public IAimpPlaylistManager2
        {
        private:
            PlayListHandler^ _onPlaylistActivated;
            PlayListHandler^ _onPlaylistAdded;
            PlayListHandler^ _onPlaylistRemoved;

        public:
            explicit AimpServicePlaylistManager(ManagedAimpCore^ core);

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

            virtual ActionResultType CreatePlaylist(String^ name, bool isActive, IAimpPlaylist^% playList);

            virtual ActionResultType CreatePlaylistFromFile(String^ fileName, bool isActive, IAimpPlaylist^% playList);

            virtual ActionResultType GetActivePlaylist(IAimpPlaylist^% playList);

            virtual ActionResultType GetLoadedPlaylist(int index, IAimpPlaylist^% playList);

            virtual ActionResultType GetPlayablePlaylist(IAimpPlaylist^% playList);

            virtual ActionResultType GetLoadedPlaylistById(String^ id, IAimpPlaylist^% playList);

            virtual ActionResultType GetLoadedPlaylistByName(String^ name, IAimpPlaylist^% playList);

            virtual int GetLoadedPlaylistCount();

            virtual ActionResultType SetActivePlaylist(IAimpPlaylist^ playList);

            virtual ActionResultType GetPreimageFactory(int index, IAimpExtensionPlaylistPreimageFactory^% factory);

            virtual ActionResultType
            GetPreimageFactoryByID(String^ id, IAimpExtensionPlaylistPreimageFactory^% factory);

            virtual int GetPreimageFactoryCount();

            //******** IAimpExtensionPlaylistManagerListenerExecutor ********

            //virtual void OnPlaylistActivated(IAIMPPlaylist* playlist);

            //virtual void OnPlaylistAdded(IAIMPPlaylist* playlist);

            //virtual void OnPlaylistRemoved(IAIMPPlaylist* playlist);

        protected:
            IAIMPServicePlaylistManager2* GetAimpService() override;
        };
    }
}
