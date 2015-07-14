#include "..\..\AIMP_SDK\aimp3_60_sdk.h"
#include "..\BaseManager.h"

namespace AIMP
{
	namespace SDK
	{
		using namespace System::Collections;
		using namespace System::Collections::Generic;

		using namespace AIMP36SDK;
		using namespace AIMP::SDK;

		public ref class PlayListManager : public AimpBaseManager, public AIMP::SDK::Services::PlayListManager::IPlayListManager, public IExtensionPlaylistManagerListener
		{
		private:
			IAIMPServicePlaylistManager *_service;
			PlayListHandler ^_onPlaylistActivated;
			PlayListHandler ^_onPlaylistAdded;
			PlayListHandler ^_onPlaylistRemoved;

		public:
			explicit PlayListManager(ManagedAimpCore ^core) : AimpBaseManager(core)
			{
				IAIMPServicePlaylistManager *service;
				if (!CheckResult(core->GetService(IID_IAIMPServicePlaylistManager, (void**) &service)))
				{
					throw gcnew System::ApplicationException("Unable create AIMP service");
				}

				_service = service;

				core->PlaylistActivated += gcnew PlayListHandler(this, &AIMP::SDK::PlayListManager::onPlaylistActivated);
				core->PlaylistAdded += gcnew PlayListHandler(this, &AIMP::SDK::PlayListManager::onPlaylistAdded);
				core->PlaylistRemoved += gcnew PlayListHandler(this, &AIMP::SDK::PlayListManager::onPlaylistRemoved);
			}

			virtual event PlayListHandler ^PlaylistActivated
			{
				virtual void add(PlayListHandler ^onEvent)
				{
					_onPlaylistActivated = onEvent;
				}
				virtual void remove(PlayListHandler ^onEvent)
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

			virtual IAimpPlayList^ CreatePlaylist(System::String^ name, bool isActive)
			{
				IAIMPPlaylist *playList;
				if (CheckResult(_service->CreatePlaylist(ObjectHelper::MakeAimpString(_core->GetAimpCore(), name), (BOOL)isActive, &playList)))
				{
					return gcnew AIMP::SDK::PlayList::AimpPlayList(playList);
				}

				return nullptr;
			}

			virtual IAimpPlayList^ CreatePlaylistFromFile(System::String^ fileName, bool isActive)
			{
				IAIMPPlaylist *playList;
				if (CheckResult(_service->CreatePlaylistFromFile(ObjectHelper::MakeAimpString(_core->GetAimpCore(), fileName), (BOOL)isActive, &playList)))
				{
					return gcnew AIMP::SDK::PlayList::AimpPlayList(playList);
				}

				return nullptr;
			}

			virtual IAimpPlayList^ GetActivePlaylist()
			{
				IAIMPPlaylist *playList;
				if (CheckResult(_service->GetActivePlaylist(&playList)))
				{
					return gcnew AIMP::SDK::PlayList::AimpPlayList(playList);
				}

				return nullptr;
			}

			virtual IAimpPlayList^ GetLoadedPlaylist(int index)
			{
				IAIMPPlaylist *playList;
				if (CheckResult(_service->GetLoadedPlaylist(index, &playList)))
				{
					return gcnew AIMP::SDK::PlayList::AimpPlayList(playList);
				}

				return nullptr;
			}

			virtual IAimpPlayList^ GetPlayablePlaylist()
			{
				IAIMPPlaylist *playList;
				if (CheckResult(_service->GetPlayablePlaylist(&playList)))
				{
					return gcnew AIMP::SDK::PlayList::AimpPlayList(playList);
				}

				return nullptr;
			}

			virtual IAimpPlayList^ GetLoadedPlaylistById(System::String^ id)
			{
				IAIMPPlaylist *playList;
				if (CheckResult(_service->GetLoadedPlaylistByID(ObjectHelper::MakeAimpString(_core->GetAimpCore(), id), &playList)))
				{
					return gcnew AIMP::SDK::PlayList::AimpPlayList(playList);
				}

				return nullptr;
			}

			virtual IAimpPlayList^ GetLoadedPlaylistByName(System::String^ name)
			{
				IAIMPPlaylist *playList;
				if (CheckResult(_service->GetLoadedPlaylistByName(ObjectHelper::MakeAimpString(_core->GetAimpCore(), name), &playList)))
				{
					return gcnew AIMP::SDK::PlayList::AimpPlayList(playList);
				}

				return nullptr;
			}

			virtual int GetLoadedPlaylistCount()
			{
				return _service->GetLoadedPlaylistCount();
			}

			virtual void SetActivePlaylist(AIMP::SDK::Services::PlayListManager::IAimpPlayList^ playList)
			{
				CheckResult(_service->SetActivePlaylist(((AIMP::SDK::PlayList::AimpPlayList^)playList)->InternalAimpObject));
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