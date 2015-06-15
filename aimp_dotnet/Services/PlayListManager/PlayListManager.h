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

		class PlaylistManagerListener : public AIMP36SDK::IUnknownInterfaceImpl<AIMP36SDK::IAIMPExtensionPlaylistManagerListener>
		{
		private:
			AIMP36SDK::IUnknownInterfaceImpl<AIMP36SDK::IAIMPPlugin> *_aimpPlugin;

		public:
			PlaylistManagerListener(AIMP36SDK::IUnknownInterfaceImpl<AIMP36SDK::IAIMPPlugin> *aimpPlugin)
			{
				_aimpPlugin = aimpPlugin;
			}

			virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
			{
				return _aimpPlugin->QueryInterface(riid, ppvObject);
			}

			virtual ULONG WINAPI AddRef(void)
			{
				return _aimpPlugin->AddRef();
			}

			virtual ULONG WINAPI Release(void)
			{
				return _aimpPlugin->Release();
			}

			virtual void WINAPI PlaylistActivated(AIMP36SDK::IAIMPPlaylist* Playlist)
			{
				System::Diagnostics::Debug::WriteLine("PlaylistActivated");
			}

			virtual void WINAPI PlaylistAdded(AIMP36SDK::IAIMPPlaylist* Playlist)
			{
				System::Diagnostics::Debug::WriteLine("PlaylistAdded");
			}

			virtual void WINAPI PlaylistRemoved(AIMP36SDK::IAIMPPlaylist* Playlist)
			{
				System::Diagnostics::Debug::WriteLine("PlaylistRemoved");
			}			
		};

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

				AIMP36SDK::IAIMPExtensionPlaylistManagerListener* eventExtension = new PlaylistManagerListener(core->AimpNativePlugin());
				core->RegisterExtensionPlaylistManagerListener(eventExtension);			
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
				
			}
		};
	}
}