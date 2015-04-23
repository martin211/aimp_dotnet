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

		public ref class PlayListManager : public AimpBaseManager, public AIMP::SDK::Services::PlayListManager::IPlayListManager
		{
		private:
			IAIMPServicePlaylistManager *_service;

		public:
			explicit PlayListManager(ManagedAimpCore ^core) : AimpBaseManager(core)
			{
				IAIMPServicePlaylistManager *service;
				if (!CheckResult(core->GetService(IID_IAIMPServicePlaylistManager, (void**) &service)))
				{
					throw gcnew System::ApplicationException("Unable create AIMP service");
				}

				_service = service;
			}

			virtual IAimpPlayList^ CreatePlaylist(System::String^ name, bool isActive)
			{
				IAIMPPlaylist *playList;
				if (CheckResult(_service->CreatePlaylist(ObjectHelper::MakeAimpString(_core->GetAimpCore(), name), (BOOL)isActive, &playList)))
				{
					return gcnew AIMP::SDK::PlayList::AimpPlayList(playList);
				}
			}

			virtual IAimpPlayList^ CreatePlaylistFromFile(System::String^ fileName, bool isActive)
			{
				IAIMPPlaylist *playList;
				if (CheckResult(_service->CreatePlaylistFromFile(ObjectHelper::MakeAimpString(_core->GetAimpCore(), fileName), (BOOL)isActive, &playList)))
				{
					return gcnew AIMP::SDK::PlayList::AimpPlayList(playList);
				}
			}

			virtual IAimpPlayList^ GetActivePlaylist()
			{
				IAIMPPlaylist *playList;
				if (CheckResult(_service->GetActivePlaylist(&playList)))
				{
					return gcnew AIMP::SDK::PlayList::AimpPlayList(playList);
				}
			}

			virtual IAimpPlayList^ GetLoadedPlaylist(int index)
			{
				IAIMPPlaylist *playList;
				if (CheckResult(_service->GetLoadedPlaylist(index, &playList)))
				{
					return gcnew AIMP::SDK::PlayList::AimpPlayList(playList);
				}
			}

			virtual IAimpPlayList^ GetPlayablePlaylist()
			{
				IAIMPPlaylist *playList;
				if (CheckResult(_service->GetPlayablePlaylist(&playList)))
				{
					return gcnew AIMP::SDK::PlayList::AimpPlayList(playList);
				}
			}

			virtual IAimpPlayList^ GetLoadedPlaylistById(System::String^ id)
			{
				IAIMPPlaylist *playList;
				if (CheckResult(_service->GetLoadedPlaylistByID(ObjectHelper::MakeAimpString(_core->GetAimpCore(), id), &playList)))
				{
					return gcnew AIMP::SDK::PlayList::AimpPlayList(playList);
				}
			}

			virtual IAimpPlayList^ GetLoadedPlaylistByName(System::String^ name)
			{
				IAIMPPlaylist *playList;
				if (CheckResult(_service->GetLoadedPlaylistByName(ObjectHelper::MakeAimpString(_core->GetAimpCore(), name), &playList)))
				{
					return gcnew AIMP::SDK::PlayList::AimpPlayList(playList);
				}
			}

			virtual int GetLoadedPlaylistCount()
			{
				return _service->GetLoadedPlaylistCount();
			}

			virtual void SetActivePlaylist(AIMP::SDK::Services::PlayListManager::IAimpPlayList^ playList)
			{
				
			}
		};
	}
}