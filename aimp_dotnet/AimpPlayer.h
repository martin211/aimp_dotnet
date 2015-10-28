#pragma once

#include <vcclr.h>
#include "AIMPPlugin.h"
#include "ManagedAimpCore.h"

#include "SDK\Menu\AimpMenuManager.h"
#include "SDK\Action\AimpActionManager.h"
#include "SDK\MUI\MUIManager.h"
#include "SDK\AlbumArt\AimpAlbumArtManager.h"
#include "SDK\Configuration\AimpConfigurationManager.h"
#include "SDK\PlayList\AimpFileInfo.h"
#include "SDK\Win32\Win32Manager.h"
#include "SDK\PlayList\AimpPlayListItem.h"
#include "SDK\PlayList\AimpPlayList.h"
#include "SDK\PlayList\PlayListManager.h"
#include "SDK\Playback\AimpServicePlaybackQueue.h"
#include "SDK\Threading\AimpServiceSynchronizer.h"
#include "AimpCore.h"



//http://stackoverflow.com/questions/163757/how-to-use-boostbind-in-c-cli-to-bind-a-member-of-a-managed-class


namespace AIMP
{
	using namespace System;
	using namespace System::Runtime::InteropServices;
	using namespace AIMP::SDK;
	using namespace AIMP::SDK::Interfaces;
	using namespace AIMP::SDK::Services::ActionManager;
	using namespace AIMP::SDK::Services::AlbumArtManager;
	using namespace AIMP::SDK::Services::ConfigurationManager;
	using namespace AIMP::SDK::Services::PlayList;
	using namespace AIMP::SDK::Services::Win32Manager;
	using namespace AIMP::SDK::Services::Playback;

	template<class TConvAlloc>
	private ref class AimpPlayer :
		public MarshalByRefObject,
		public IAimpPlayer
	{
	private:
		IAIMPMessageHook* aimp_message_hook_;
		IAIMPServicePlayer* _player;
		
		ManagedAimpCore ^_managedAimpCore;
		IAimpCore ^_aimpCore;
		AimpEventsDelegate^ _coreMessage;
		IAimpMenuManager^ _menuManager;
		IAimpActionManager^ _actionManager;
		IAimpMUIManager^ _muiManager;
		IAimpAlbumArtManager^ _artManager;
		IAimpConfigurationManager^ _configManager;
		IWin32Manager ^_win32Manager;
		IAimpPlayListManager ^_playListManager;
		IAimpPlaybackQueueService ^_playbackQueueManager;
		AimpPlayerState _state;

		AimpStateChanged ^_onStateChanged;
		EventHandler ^_onLanguageChanged;
		EventHandler ^_onTrackChanged;

	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="AIMP3Controller{TConvAlloc}" /> class.
		/// </summary>
		/// <param name="core">The aimp core.</param>
		/// <param name="pluginId">The plugin identifier.</param>
		/// <param name="applicationDomainId">The application domain identifier.</param>
		/// <param name="isCrossDomain">The is cross domain.</param>
		AimpPlayer(ManagedAimpCore ^core, int pluginId, int applicationDomainId, bool isCrossDomain)
		{
			//_aimpCore = core;
			//_managerCore = gcnew AIMP::SDK360::ManagedAimpCore(core, nullptr);
			_managedAimpCore = core;
			IAIMPServicePlayer* ps;
			((ManagedAimpCore^) _managedAimpCore)->GetService(IID_IAIMPServicePlayer, reinterpret_cast<void**>(&ps));
			_player = ps;
		}

		~AimpPlayer()
		{
			_player->Release();
			delete _aimpCore;
			delete _menuManager;
			delete _actionManager;
			delete _muiManager;
			delete _artManager;
			delete _configManager;
			delete _playListManager;
			delete _playbackQueueManager;
		}

		virtual property IAimpCore^ Core
		{
			IAimpCore^ get()
			{
				if (_aimpCore == nullptr)
				{
					_aimpCore = gcnew AimpCore(_managedAimpCore);
					_aimpCore->CoreMessage += gcnew AimpEventsDelegate(this, &AIMP::AimpPlayer<TConvAlloc>::OnCoreMessage);
				}

				return _aimpCore;
			}
		}

		virtual property IAimpMenuManager^ MenuManager
		{
			IAimpMenuManager^ get()
			{
				if (_menuManager == nullptr)
				{
					_menuManager = gcnew AimpMenuManager(_managedAimpCore);
				}

				return _menuManager;
			}
		}

		virtual property IAimpActionManager^ ActionManager
		{
			IAimpActionManager^ get()
			{
				if (_actionManager == nullptr)
				{
					_actionManager = gcnew AIMP::AimpActionManager((ManagedAimpCore^) _managedAimpCore);
				}

				return _actionManager;
			}
		}
		
		virtual property IAimpMUIManager^ MUIManager
		{
			IAimpMUIManager^ get()
			{
				if (_muiManager == nullptr)
				{
					_muiManager = gcnew AIMP::AimpMIUManager((ManagedAimpCore^) _managedAimpCore);
				}

				return _muiManager;
			}
		}

		virtual property IAimpAlbumArtManager^ AlbumArtManager
		{
			IAimpAlbumArtManager^ get()
			{
				if (_artManager == nullptr)
				{
					_artManager = gcnew AIMP::AimpAlbumArtManager((ManagedAimpCore^) _managedAimpCore);
				}

				return _artManager;
			}
		}

		virtual property IAimpConfigurationManager^ ConfigurationManager
		{
			IAimpConfigurationManager^ get()
			{
				if (_configManager == nullptr)
				{
					_configManager = gcnew AIMP::AimpConfigurationManager((ManagedAimpCore^) _managedAimpCore);
				}

				return _configManager;
			}
		}

		virtual property IAimpPlayListManager ^PlayListManager
		{
			IAimpPlayListManager ^get()
			{
				if (_playListManager == nullptr)
				{
					_playListManager = gcnew AIMP::SDK::PlayListManager((ManagedAimpCore^) _managedAimpCore);
				}

				return _playListManager;
			}
		}

		virtual property IAimpPlaybackQueueService ^PlaybackQueueManager
		{
			IAimpPlaybackQueueService ^get()
			{
				System::Diagnostics::Debug::WriteLine("Get PlaybackQueueManager");
				if (_playbackQueueManager == nullptr)
				{
					_playbackQueueManager = gcnew AIMP::SDK::AimpServicePlaybackQueue((ManagedAimpCore^) _managedAimpCore);
					((ManagedAimpCore^)_managedAimpCore)->CheckUrl +=  gcnew AIMP::SDK::Services::Playback::AimpCheckUrl(this, &AIMP::AimpPlayer<TConvAlloc>::OnCheckUrl);
				}

				return _playbackQueueManager;
			}
		}

		bool OnCheckUrl(String^ %url)
		{
			return ((AIMP::SDK::AimpServicePlaybackQueue^)this->_playbackQueueManager)->RaiseCheckUrl(url);
		}

		virtual property IAIMPServicePlayer* ServicePlayer
		{
			IAIMPServicePlayer* get()
			{
				return _player;
			}
		}

		virtual property bool IsMute
		{
			bool get()
			{
				bool value;
				Utils::CheckResult(_player->GetMute(&value));
				return value;
			}

			void set(bool value)
			{
				Utils::CheckResult(_player->SetMute(value));
			}
		}

		virtual property float Volume
		{
			float get()
			{
				float value;
				Utils::CheckResult(_player->GetVolume(&value));
				return value;
			}

			void set(float value)
			{
				Utils::CheckResult(_player->SetVolume(value));
			}
		}

		virtual property double Duration
		{
			double get()
			{
				double value;
				_player->GetDuration(&value);
				return value;
			}
		}

		virtual property double Position
		{
			double get()
			{
				double value;
				Utils::CheckResult(_player->GetPosition(&value));
				return value;
			}

			void set(double value)
			{
				Utils::CheckResult(_player->SetPosition(value));
			}
		}

		virtual property AimpPlayerState State
		{
			AimpPlayerState get()
			{
				int state = _player->GetState();
				return (AimpPlayerState)state;
			}
		}

		virtual property IAimpFileInfo^ CurrentFileInfo
		{
			IAimpFileInfo^ get()
			{
				IAIMPFileInfo* fi;
				_player->GetInfo(&fi);

				if (fi == NULL)
				{
					return nullptr;
				}

				AimpFileInfo^ fileInfo = gcnew AimpFileInfo(fi);
				return fileInfo;
			}
		}

		virtual property IAimpPlayListItem^ CurrentPlayListItem
		{
			IAimpPlayListItem^ get()
			{
				IAIMPPlaylistItem* item;
				_player->GetPlaylistItem(&item);

				if (item == NULL)
				{
					return nullptr;
				}

				return gcnew AimpPlayListItem(item);
			}
		}

		virtual property IWin32Manager ^Win32Manager
		{
			IWin32Manager ^get()
			{
				if (_win32Manager == nullptr)
				{
					_win32Manager = gcnew AIMP::Win32::Win32Manager();
				}

				return _win32Manager;
			}
		}
		
		virtual event AimpStateChanged^ StateChanged
		{
			void add(AimpStateChanged^ onAction)
			{
				if (this->_onStateChanged == nullptr)
				{
					_onStateChanged = (AimpStateChanged^)Delegate::Combine(_onStateChanged, onAction);
				}
			}
			void remove(AimpStateChanged^ onAction)
			{
				bool tmp = this->_onStateChanged != nullptr;
				if (tmp)
				{
					_onStateChanged = (AimpStateChanged^)Delegate::Remove(_onStateChanged, onAction);
				}
			}
			void raise(AIMP::SDK::AimpPlayerState state)
			{
				if (this->_onStateChanged != nullptr)
				{
					_onStateChanged(state);
				}
			}
		}

		virtual event EventHandler ^LanguageChanged
		{
			void add(EventHandler ^onAction)
			{
				bool tmp = _onLanguageChanged == nullptr;
				if (tmp)
				{
					_onLanguageChanged = (EventHandler^)Delegate::Combine(_onLanguageChanged, onAction);
				}
			}
			void remove(EventHandler ^onAction)
			{
				bool tmp = _onLanguageChanged != nullptr;
				if (tmp)
				{
					_onLanguageChanged = (EventHandler^)Delegate::Remove(_onLanguageChanged, onAction);
				}
			}
			void raise(Object ^sender, EventArgs ^e)
			{
				if (_onLanguageChanged != nullptr)
				{
					_onLanguageChanged(sender, e);
				}
			}
		}

		virtual event EventHandler ^TrackChanged
		{
			void add(EventHandler ^onAction)
			{
				bool tmp = _onTrackChanged == nullptr;
				if (tmp)
				{
					_onTrackChanged = (EventHandler^)Delegate::Combine(_onTrackChanged, onAction);
				}
			}
			void remove(EventHandler ^onAction)
			{
				bool tmp = _onTrackChanged != nullptr;
				if (tmp)
				{
					_onTrackChanged = (EventHandler^) Delegate::Remove(_onTrackChanged, onAction);
				}
			}
			void raise(Object ^sender, EventArgs ^e)
			{
				if (_onTrackChanged != nullptr)
				{
					_onTrackChanged(sender, e);
				}
			}
		}

		virtual void Pause()
		{
			_player->Pause();
		}

		virtual void Stop()
		{
			_player->Stop();
		}

		virtual void Resume()
		{
			_player->Resume();
		}

		virtual void StopAfterTrack()
		{
			_player->StopAfterTrack();
		}

		virtual void GoToNext()
		{
			_player->GoToNext();
		}

		virtual void GoToPrev()
		{
			_player->GoToPrev();
		}

		virtual void Play(IAimpPlaybackQueueItem ^queueItem)
		{
			_player->Play(((AimpPlaybackQueueItem^)queueItem)->InternalAimpObject);
		}

		virtual void Play(IAimpPlayListItem ^playListItem)
		{
			_player->Play2(((AimpPlayListItem^)playListItem)->InternalAimpObject);
		}

		virtual void Play(IAimpPlayList^ playList)
		{
			_player->Play3(((AimpPlayList^)playList)->InternalAimpObject);
		}

	private:
		void OnCoreMessage(AimpMessages::AimpCoreMessageType param1, int param2)
		{
			if (param1 == AimpMessages::AimpCoreMessageType::AIMP_MSG_EVENT_PLAYER_STATE && _state != this->State)
			{
				_state = this->State;
				StateChanged(_state);
			}
			else if (param1 == AimpMessages::AimpCoreMessageType::AIMP_MSG_EVENT_LANGUAGE)
			{
				LanguageChanged(this, EventArgs::Empty);
			} 
			else if (param1 == AimpMessages::AimpCoreMessageType::AIMP_MSG_EVENT_STREAM_START || param1 == AimpMessages::AimpCoreMessageType::AIMP_MSG_EVENT_STREAM_START_SUBTRACK)
			{
				TrackChanged(this, EventArgs::Empty);
			}
		}

		//bool onCheckUrl([Runtime::InteropServices::Out] String^ %url);
	};

	private ref class AIMPControllerInitializer : public System::MarshalByRefObject
	{
	public:
		static String^ TypeName = "";

		AimpPlayer<StaticSingleThreadAllocator>^ CreateWithStaticAllocator(ManagedAimpCore^ Ctrl, int PlgUID, int AppDomainID, bool CrossDmn/*, CentralizedEventController^ evCtrl*/)
		{
			return gcnew AimpPlayer<StaticSingleThreadAllocator>(Ctrl, PlgUID, AppDomainID, CrossDmn/*, evCtrl*/);
		}
	};
}
