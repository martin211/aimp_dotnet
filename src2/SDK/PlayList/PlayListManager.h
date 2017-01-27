/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 */
#include "..\BaseManager.h"
#include "AimpPlayListQueue.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System::Collections;
        using namespace System::Collections::Generic;

        using namespace AIMP::SDK;
        using namespace AIMP::SDK::PlayList;

        public ref class PlayListManager :
            public AimpBaseManager<IAIMPServicePlaylistManager>, 
            public IAimpPlayListManager, 
            public IAimpExtensionPlaylistManagerListenerExecutor
        {
        private:
            PlayListHandler ^_onPlaylistActivated;
            PlayListHandler ^_onPlaylistAdded;
            PlayListHandler ^_onPlaylistRemoved;
            AimpPlaylistQueue ^_playListQueue;

        public:
            explicit PlayListManager(ManagedAimpCore ^core);

            ~PlayListManager();

            !PlayListManager();

            virtual property IAimpPlayListQueue ^PlayListQueue
            {
                IAimpPlayListQueue ^get();
            }

            virtual event PlayListHandler ^PlaylistActivated
            {
                virtual void add(PlayListHandler ^onEvent);
                virtual void remove(PlayListHandler ^onEvent);
                virtual void raise(String ^playListName, String ^playListId);
            }

            virtual event PlayListHandler ^PlaylistAdded
            {
                virtual void add(PlayListHandler ^onEvent);
                virtual void remove(PlayListHandler ^onEvent);
                virtual void raise(String ^playListName, String ^playListId);
            }

            virtual event PlayListHandler ^PlaylistRemoved
            {
                virtual void add(PlayListHandler ^onEvent);
                virtual void remove(PlayListHandler ^onEvent);
                void raise(String ^playListName, String ^playListId);
            }

            virtual AimpActionResult CreatePlaylist(System::String^ name, bool isActive, IAimpPlayList ^%playList);

            virtual AimpActionResult CreatePlaylistFromFile(System::String^ fileName, bool isActive, IAimpPlayList ^%playList);

            virtual AimpActionResult GetActivePlaylist(IAimpPlayList ^%playList);

            virtual AimpActionResult GetLoadedPlaylist(int index, IAimpPlayList ^%playList);

            virtual AimpActionResult GetPlayablePlaylist(IAimpPlayList ^%playList);

            virtual AimpActionResult GetLoadedPlaylistById(System::String^ id, IAimpPlayList ^%playList);

            virtual AimpActionResult GetLoadedPlaylistByName(System::String^ name, IAimpPlayList ^%playList);

            virtual int GetLoadedPlaylistCount();

            virtual void SetActivePlaylist(IAimpPlayList^ playList);

            //******** IAimpExtensionPlaylistManagerListenerExecutor ********

            virtual void OnPlaylistActivated(IAIMPPlaylist* playlist);

            virtual void OnPlaylistAdded(IAIMPPlaylist* playlist);

            virtual void OnPlaylistRemoved(IAIMPPlaylist* playlist);
        };
    }
}
