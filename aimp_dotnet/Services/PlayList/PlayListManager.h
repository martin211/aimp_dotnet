#include "..\BaseManager.h"

namespace AIMP
{
	namespace SDK
	{
		using namespace System::Collections;
		using namespace System::Collections::Generic;

		using namespace AIMP::SDK;
		using namespace AIMP::SDK::Services::PlayList;

		public ref class PlayListManager : public AimpBaseManager, public IAimpPlayListManager, public IExtensionPlaylistManagerListener
		{
		private:
			IAIMPServicePlaylistManager *_service;
			AIMP::SDK::Extensions::PlayListHandler ^_onPlaylistActivated;
			AIMP::SDK::Extensions::PlayListHandler ^_onPlaylistAdded;
			AIMP::SDK::Extensions::PlayListHandler ^_onPlaylistRemoved;

		public:
			explicit PlayListManager(ManagedAimpCore ^core) : AimpBaseManager(core)
			{
				IAIMPServicePlaylistManager *service;
				if (!CheckResult(core->GetService(IID_IAIMPServicePlaylistManager, (void**)&service)))
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

			virtual void SetActivePlaylist(IAimpPlayList^ playList)
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