#include "..\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System::Collections;
        using namespace System::Collections::Generic;

        using namespace AIMP::SDK;
        using namespace AIMP::SDK::PlayList;

        public ref class PlayListManager : public AimpBaseManager<IAIMPServicePlaylistManager>, 
            public IAimpPlayListManager, 
            public IAimpExtensionPlaylistManagerListenerExecutor
        {
        private:
            PlayListHandler ^_onPlaylistActivated;
            PlayListHandler ^_onPlaylistAdded;
            PlayListHandler ^_onPlaylistRemoved;

        public:
            explicit PlayListManager(ManagedAimpCore ^core) : AimpBaseManager<IAIMPServicePlaylistManager>(core)
            {

            }

            ~PlayListManager()
            {
                this->!PlayListManager();
            }

            !PlayListManager()
            {
                _core->PlaylistActivated -= gcnew PlayListHandler(this, &AIMP::SDK::PlayListManager::onPlaylistActivated);
                _core->PlaylistAdded -= gcnew PlayListHandler(this, &AIMP::SDK::PlayListManager::onPlaylistAdded);
                _core->PlaylistRemoved -= gcnew PlayListHandler(this, &AIMP::SDK::PlayListManager::onPlaylistRemoved);
            }

            virtual event PlayListHandler ^PlaylistActivated
            {
                virtual void add(PlayListHandler ^onEvent)
                {
                    _onPlaylistActivated = onEvent;
                    // Register IAimpExtensionPlaylistManagerListener
                    _core->RegisterExtension(IID_IAIMPServicePlaylistManager, this);
                }
                virtual void remove(PlayListHandler ^onEvent)
                {
                    _onPlaylistActivated = nullptr;
                    _core->UnregisterExtension(this);
                }
                void raise(String ^playListName, String ^playListId)
                {
                    if (_onPlaylistActivated != nullptr)
                    {
                        _onPlaylistActivated(playListName, playListId);
                    }
                }
            }

            virtual event PlayListHandler ^PlaylistAdded
            {
                virtual void add(PlayListHandler ^onEvent)
                {
                    _onPlaylistAdded = onEvent;
                }
                virtual void remove(PlayListHandler ^onEvent)
                {
                    _onPlaylistAdded = nullptr;
                }
                void raise(String ^playListName, String ^playListId)
                {
                    if (_onPlaylistAdded != nullptr)
                    {
                        _onPlaylistAdded(playListName, playListId);
                    }
                }
            }

            virtual event PlayListHandler ^PlaylistRemoved
            {
                virtual void add(PlayListHandler ^onEvent)
                {
                    _onPlaylistRemoved = onEvent;
                }
                virtual void remove(PlayListHandler ^onEvent)
                {
                    _onPlaylistRemoved = nullptr;
                }
                void raise(String ^playListName, String ^playListId)
                {
                    if (_onPlaylistRemoved != nullptr)
                    {
                        _onPlaylistRemoved(playListName, playListId);
                    }
                }
            }

            virtual AimpActionResult CreatePlaylist(System::String^ name, bool isActive, IAimpPlayList ^%playList)
            {
                playList = nullptr;

                IAIMPPlaylist *pl = NULL;
                IAIMPString *str = NULL;
                IAIMPServicePlaylistManager *service;
                AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));

                if (res == AimpActionResult::Ok)
                {
                    str = Converter::MakeAimpString(_core->GetAimpCore(), name);
                    res = CheckResult(service->CreatePlaylist(str, (BOOL)isActive, &pl));

                    if (res == AimpActionResult::Ok)
                    {
                        playList = gcnew AimpPlayList(pl);
                    }
                }

                if (service != NULL)
                {
                    service->Release();
                    service = NULL;
                }

                if (str != NULL)
                {
                    str->Release();
                    str = NULL;
                }

                return res;
            }

            virtual AimpActionResult CreatePlaylistFromFile(System::String^ fileName, bool isActive, IAimpPlayList ^%playList)
            {
                playList = nullptr;

                IAIMPPlaylist *pl = NULL;
                IAIMPString *str = NULL;
                IAIMPServicePlaylistManager *service;

                AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
                if (res == AimpActionResult::Ok)
                {
                    str = Converter::MakeAimpString(_core->GetAimpCore(), fileName);
                    res = CheckResult(service->CreatePlaylistFromFile(str, (BOOL)isActive, &pl));

                    if (res == AimpActionResult::Ok)
                    {
                        playList = gcnew AimpPlayList(pl);
                    }
                }

                if (service != NULL)
                {
                    service->Release();
                    service = NULL;
                }

                if (str != NULL)
                {
                    str->Release();
                    str = NULL;
                }

                return res;
            }

            virtual AimpActionResult GetActivePlaylist(IAimpPlayList ^%playList)
            {
                playList = nullptr;
                IAIMPPlaylist *pl = NULL;
                IAIMPServicePlaylistManager *service;

                AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
                if (res == AimpActionResult::Ok)
                {
                    res = CheckResult(service->GetActivePlaylist(&pl));
                    if (res == AimpActionResult::Ok)
                    {
                        playList = gcnew AimpPlayList(pl);
                    }
                }

                if (service != NULL)
                {
                    service->Release();
                    service = NULL;
                }

                return res;
            }

            virtual AimpActionResult GetLoadedPlaylist(int index, IAimpPlayList ^%playList)
            {
                playList = nullptr;
                IAIMPPlaylist *pl = NULL;
                IAIMPServicePlaylistManager *service;

                AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));

                if (res == AimpActionResult::Ok)
                {
                    res = CheckResult(service->GetLoadedPlaylist(index, &pl));
                    if (res == AimpActionResult::Ok)
                    {
                        playList = gcnew AimpPlayList(pl);
                    }
                }

                if (service != NULL)
                {
                    service->Release();
                    service = NULL;
                }

                return res;
            }

            virtual AimpActionResult GetPlayablePlaylist(IAimpPlayList ^%playList)
            {
                playList = nullptr;

                IAIMPPlaylist *pl = NULL;
                IAIMPServicePlaylistManager *service;

                AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
                if (res == AimpActionResult::Ok)
                {
                    res = CheckResult(service->GetPlayablePlaylist(&pl));
                    if (res == AimpActionResult::Ok)
                    {
                       playList = gcnew AimpPlayList(pl);
                    }
                }

                return res;
            }

            virtual AimpActionResult GetLoadedPlaylistById(System::String^ id, IAimpPlayList ^%playList)
            {
                playList = nullptr;
                IAIMPPlaylist *pl = NULL;
                IAIMPString *key = NULL;
                IAIMPServicePlaylistManager *service;

                AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
                if (res == AimpActionResult::Ok)
                {
                    key = Converter::MakeAimpString(_core->GetAimpCore(), id);
                    res = CheckResult(service->GetLoadedPlaylistByID(key, &pl));
                    if (res == AimpActionResult::Ok)
                    {
                        playList = gcnew AimpPlayList(pl);
                    }
                }

                if (pl != NULL)
                {
                    pl->Release();
                    pl = NULL;
                }

                if (key != NULL)
                {
                    key->Release();
                    key = NULL;
                }

                return res;
            }

            virtual AimpActionResult GetLoadedPlaylistByName(System::String^ name, IAimpPlayList ^%playList)
            {
                playList = nullptr;
                IAIMPPlaylist *pl = NULL;
                IAIMPString *key = NULL;
                IAIMPServicePlaylistManager *service;

                AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));

                if (res == AimpActionResult::Ok)
                {
                    key = Converter::MakeAimpString(_core->GetAimpCore(), name);
                    res = CheckResult(service->GetLoadedPlaylistByName(key, &pl));

                    if (res == AimpActionResult::Ok)
                    {
                        playList = gcnew AimpPlayList(pl);
                    }
                }

                if (pl != NULL)
                {
                    pl->Release();
                    pl = NULL;
                }

                if (key != NULL)
                {
                    key->Release();
                    key = NULL;
                }

                return res;
            }

            virtual int GetLoadedPlaylistCount()
            {
                IAIMPServicePlaylistManager *service;
                AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
                return service->GetLoadedPlaylistCount();
            }

            virtual void SetActivePlaylist(IAimpPlayList^ playList)
            {
                IAIMPServicePlaylistManager *service;
                AimpActionResult res = CheckResult(_core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service));
                CheckResult(service->SetActivePlaylist(((AimpPlayList^)playList)->InternalAimpObject));
            }

            //******** IAimpExtensionPlaylistManagerListenerExecutor ********

            virtual void OnPlaylistActivated(IAIMPPlaylist* playlist)
            {
                AimpPlayList ^pl = gcnew AimpPlayList(playlist);
                this->PlaylistActivated(pl->Name, pl->Id);
                pl = nullptr;
            }

            virtual void OnPlaylistAdded(IAIMPPlaylist* playlist)
            {
                AimpPlayList ^pl = gcnew AimpPlayList(playlist);
                this->PlaylistAdded(pl->Name, pl->Id);
                pl = nullptr;
            }

            virtual void OnPlaylistRemoved(IAIMPPlaylist* playlist)
            {
                AimpPlayList ^pl = gcnew AimpPlayList(playlist);
                this->PlaylistRemoved(pl->Name, pl->Id);
                pl = nullptr;
            }
        };
    }
}