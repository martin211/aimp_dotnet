#include "..\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System::Collections;
        using namespace System::Collections::Generic;

        using namespace AIMP::SDK;
        using namespace AIMP::SDK::PlayList;

        public ref class PlayListManager : public AimpBaseManager<IAIMPServicePlaylistManager>, public IAimpPlayListManager, public IExtensionPlaylistManagerListener
        {
        private:
            IAIMPServicePlaylistManager *_service;
            AIMP::SDK::Extensions::PlayListHandler ^_onPlaylistActivated;
            AIMP::SDK::Extensions::PlayListHandler ^_onPlaylistAdded;
            AIMP::SDK::Extensions::PlayListHandler ^_onPlaylistRemoved;

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
                _core->PlaylistActivated -= gcnew AIMP::SDK::Extensions::PlayListHandler(this, &AIMP::SDK::PlayListManager::onPlaylistActivated);
                _core->PlaylistAdded -= gcnew AIMP::SDK::Extensions::PlayListHandler(this, &AIMP::SDK::PlayListManager::onPlaylistAdded);
                _core->PlaylistRemoved -= gcnew AIMP::SDK::Extensions::PlayListHandler(this, &AIMP::SDK::PlayListManager::onPlaylistRemoved);
            }

            virtual event AIMP::SDK::Extensions::PlayListHandler ^PlaylistActivated
            {
                virtual void add(AIMP::SDK::Extensions::PlayListHandler ^onEvent)
                {
                    _onPlaylistActivated = onEvent;
                }
                virtual void remove(AIMP::SDK::Extensions::PlayListHandler ^onEvent)
                {
                    _onPlaylistActivated = nullptr;
                }
                void raise(String ^playListName, String ^playListId)
                {
                    if (_onPlaylistActivated != nullptr)
                    {
                        _onPlaylistActivated(playListName, playListId);
                    }
                }
            }

            virtual event AIMP::SDK::Extensions::PlayListHandler ^PlaylistAdded
            {
                virtual void add(AIMP::SDK::Extensions::PlayListHandler ^onEvent)
                {
                    _onPlaylistAdded = onEvent;
                }
                virtual void remove(AIMP::SDK::Extensions::PlayListHandler ^onEvent)
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

            virtual event AIMP::SDK::Extensions::PlayListHandler ^PlaylistRemoved
            {
                virtual void add(AIMP::SDK::Extensions::PlayListHandler ^onEvent)
                {
                    _onPlaylistRemoved = onEvent;
                }
                virtual void remove(AIMP::SDK::Extensions::PlayListHandler ^onEvent)
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
                    res = CheckResult(_service->CreatePlaylist(str, (BOOL)isActive, &pl));

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
                    res = CheckResult(_service->CreatePlaylistFromFile(str, (BOOL)isActive, &pl));

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
                    res = CheckResult(_service->GetPlayablePlaylist(&pl));
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
                    res = CheckResult(_service->GetLoadedPlaylistByID(key, &pl));
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
                    res = CheckResult(_service->GetLoadedPlaylistByName(key, &pl));

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
                return _service->GetLoadedPlaylistCount();
            }

            virtual void SetActivePlaylist(IAimpPlayList^ playList)
            {
                CheckResult(_service->SetActivePlaylist(((AimpPlayList^)playList)->InternalAimpObject));
            }
        private:
            virtual void onPlaylistActivated(String ^playListName, String ^playListId)
            {
                PlaylistActivated(playListName, playListId);
            }

            virtual void onPlaylistAdded(String ^playListName, String ^playListId)
            {
                PlaylistAdded(playListName, playListId);
            }

            virtual void onPlaylistRemoved(String ^playListName, String ^playListId)
            {
                PlaylistRemoved(playListName, playListId);
            }
        };
    }
}