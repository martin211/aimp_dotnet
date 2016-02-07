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
                IAIMPServicePlaylistManager *service;
                if (CheckResult(core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service)) != AimpActionResult::Ok)
                {
                    throw gcnew System::ApplicationException("Unable create AIMP service");
                }

                _service = service;

                _core->PlaylistActivated += gcnew AIMP::SDK::Extensions::PlayListHandler(this, &AIMP::SDK::PlayListManager::onPlaylistActivated);
                _core->PlaylistAdded += gcnew AIMP::SDK::Extensions::PlayListHandler(this, &AIMP::SDK::PlayListManager::onPlaylistAdded);
                _core->PlaylistRemoved += gcnew AIMP::SDK::Extensions::PlayListHandler(this, &AIMP::SDK::PlayListManager::onPlaylistRemoved);
            }

            ~PlayListManager()
            {
                System::Diagnostics::Trace::TraceInformation("Dispose PlayListManager");
                System::Diagnostics::Trace::Flush();

                _service->Release();
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

            virtual IAimpPlayList^ CreatePlaylist(System::String^ name, bool isActive)
            {
                IAIMPPlaylist *playList = NULL;
                IAIMPString *str = NULL;
                try
                {
                    str = Converter::MakeAimpString(_core->GetAimpCore(), name);
                    if (CheckResult(_service->CreatePlaylist(str, (BOOL)isActive, &playList)) == AimpActionResult::Ok)
                    {
                        return gcnew AimpPlayList(playList);
                    }
                }
                finally
                {
                    //if (playList != NULL)
                    //{
                    //    playList->Release();
                    //    playList = NULL;
                    //}

                    if (str != NULL)
                    {
                        str->Release();
                        str = NULL;
                    }
                }

                return nullptr;
            }

            virtual IAimpPlayList^ CreatePlaylistFromFile(System::String^ fileName, bool isActive)
            {
                IAIMPPlaylist *playList = NULL;
                IAIMPString *str = NULL;

                try
                {
                    str = Converter::MakeAimpString(_core->GetAimpCore(), fileName);
                    if (CheckResult(_service->CreatePlaylistFromFile(str, (BOOL)isActive, &playList)) == AimpActionResult::Ok)
                    {
                        return gcnew AimpPlayList(playList);
                    }
                }
                finally
                {
                    if (playList != NULL)
                    {
                        playList->Release();
                        playList = NULL;
                    }

                    if (str != NULL)
                    {
                        str->Release();
                        str = NULL;
                    }
                }

                return nullptr;
            }

            virtual IAimpPlayList^ GetActivePlaylist()
            {
                IAIMPPlaylist *playList = NULL;
                try
                {
                    if (CheckResult(_service->GetActivePlaylist(&playList)) == AimpActionResult::Ok)
                    {
                        return gcnew AimpPlayList(playList);
                    }
                }
                finally
                {
                    if (playList != NULL)
                    {
                        playList->Release();
                        playList = NULL;
                    }
                }

                return nullptr;
            }

            virtual IAimpPlayList^ GetLoadedPlaylist(int index)
            {
                IAIMPPlaylist *playList = NULL;

                try
                {
                    if (CheckResult(_service->GetLoadedPlaylist(index, &playList)) == AimpActionResult::Ok)
                    {
                        return gcnew AimpPlayList(playList);
                    }
                }
                finally
                {
                    if (playList != NULL)
                    {
                        playList->Release();
                        playList = NULL;
                    }
                }

                return nullptr;
            }

            virtual IAimpPlayList^ GetPlayablePlaylist()
            {
                IAIMPPlaylist *playList = NULL;

                try
                {
                    if (CheckResult(_service->GetPlayablePlaylist(&playList)) == AimpActionResult::Ok)
                    {
                        return gcnew AimpPlayList(playList);
                    }                    
                }
                finally
                {
                    if (playList != NULL)
                    {
                        playList->Release();
                        playList = NULL;
                    }
                }

                return nullptr;
            }

            virtual IAimpPlayList^ GetLoadedPlaylistById(System::String^ id)
            {
                IAIMPPlaylist *playList = NULL;
                IAIMPString *key = NULL;
                try
                {
                    key = Converter::MakeAimpString(_core->GetAimpCore(), id);
                    if (CheckResult(_service->GetLoadedPlaylistByID(key, &playList)) == AimpActionResult::Ok)
                    {
                        return gcnew AimpPlayList(playList);
                    }
                }
                finally
                {
                    if (playList != NULL)
                    {
                        playList->Release();
                        playList = NULL;
                    }

                    if (key != NULL)
                    {
                        key->Release();
                        key = NULL;
                    }
                }

                return nullptr;
            }

            virtual IAimpPlayList^ GetLoadedPlaylistByName(System::String^ name)
            {
                IAIMPPlaylist *playList = NULL;
                IAIMPString *key = NULL;

                try
                {
                    key = Converter::MakeAimpString(_core->GetAimpCore(), name);
                    if (CheckResult(_service->GetLoadedPlaylistByName(key, &playList)) == AimpActionResult::Ok)
                    {
                        return gcnew AimpPlayList(playList);
                    }
                }
                finally
                {
                    if (playList != NULL)
                    {
                        playList->Release();
                        playList = NULL;
                    }

                    if (key != NULL)
                    {
                        key->Release();
                        key = NULL;
                    }
                }

                return nullptr;
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