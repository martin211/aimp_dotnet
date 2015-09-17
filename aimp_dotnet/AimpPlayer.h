#pragma once

#include "DataConversion.h"
#include <vcclr.h>
#include "AIMP_SDK\aimp3_60_sdk.h"
#include "AIMPPlugin.h"
#include "ManagedAimpCore.h"
#include "DataConversion.h"


#include "Services\Menu\ServiceMenuManager.h"
#include "Services\Action\ActionManager.h"
#include "Services\MUI\MUIManager.h"
#include "Services\AlbumArt\AlbumArtManager.h"
#include "Services\Configuration\ConfigurationManager.h"
#include "Services\PlayList\AimpFileInfo.h"
#include "Services\Win32\Win32Manager.h"
#include "Services\PlayList\AimpPlayListItem.h"
#include "Services\PlayList\AimpPlayList.h"
#include "Services\PlayList\PlayListManager.h"
#include "Services\Playback\ServicePlaybackQueue.h"
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
	using namespace AIMP::SDK::Services::PlayListManager;
	using namespace AIMP::SDK::Services::Win32Manager;
	using namespace AIMP::SDK::Services::Playback;

	template<class TConvAlloc>
	private ref class AimpPlayer :
		public MarshalByRefObject,
		public IAimpPlayer
	{
	private:
		typedef DataConverter Converter;
		AIMP36SDK::IAIMPMessageHook* aimp_message_hook_;
		AIMP36SDK::IAIMPServicePlayer* _player;
		
		ManagedAimpCore ^_managedAimpCore;
		IAimpCore ^_aimpCore;
		AimpEventsDelegate^ _coreMessage;
		IMenuManager^ _menuManager;
		IActionManager^ _actionManager;
		IMUIManager^ _muiManager;
		IAlbumArtManager^ _artManager;
		IConfigurationManager^ _configManager;
		IWin32Manager ^_win32Manager;
		IAimpPlayListManager ^_playListManager;
		IPlaybackQueueService ^_playbackQueueManager;
		AIMP::SDK::PlayerState _state;

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
			AIMP36SDK::IAIMPServicePlayer* ps;
			((ManagedAimpCore^) _managedAimpCore)->GetService(AIMP36SDK::IID_IAIMPServicePlayer, reinterpret_cast<void**>(&ps));
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
					//_aimpCore->CoreMessage += gcnew AimpEventsDelegate(this, &AIMP::AimpPlayer<TConvAlloc>::OnCoreMessage);
				}

				return _aimpCore;
			}
		}

		virtual property IMenuManager^ MenuManager
		{
			IMenuManager^ get()
			{
				if (_menuManager == nullptr)
				{
					_menuManager = gcnew ServiceMenuManager(_managedAimpCore);
				}

				return _menuManager;
			}
		}

		virtual property IActionManager^ ActionManager
		{
			IActionManager^ get()
			{
				if (_actionManager == nullptr)
				{
					_actionManager = gcnew AIMP::ActionManager((ManagedAimpCore^) _managedAimpCore);
				}

				return _actionManager;
			}
		}
		
		virtual property IMUIManager^ MUIManager
		{
			IMUIManager^ get()
			{
				if (_muiManager == nullptr)
				{
					_muiManager = gcnew AIMP::MIUManager((ManagedAimpCore^) _managedAimpCore);
				}

				return _muiManager;
			}
		}

		virtual property IAlbumArtManager^ AlbumArtManager
		{
			IAlbumArtManager^ get()
			{
				if (_artManager == nullptr)
				{
					_artManager = gcnew AIMP::AlbumArtManager((ManagedAimpCore^) _managedAimpCore);
				}

				return _artManager;
			}
		}

		virtual property IConfigurationManager^ ConfigurationManager
		{
			IConfigurationManager^ get()
			{
				if (_configManager == nullptr)
				{
					_configManager = gcnew AIMP::ConfigurationManager((ManagedAimpCore^) _managedAimpCore);
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

		virtual property IPlaybackQueueService ^PlaybackQueueManager
		{
			IPlaybackQueueService ^get()
			{
				if (_playbackQueueManager == nullptr)
				{
					_playbackQueueManager = gcnew AIMP::SDK::ServicePlaybackQueue((ManagedAimpCore^) _managedAimpCore);
					((ManagedAimpCore^)_managedAimpCore)->CheckUrl +=  gcnew AIMP::SDK::Services::Playback::AimpCheckUrl(this, &AIMP::AimpPlayer<TConvAlloc>::OnCheckUrl);
				}

				return _playbackQueueManager;
			}
		}

		bool OnCheckUrl(String ^url)
		{
			System::Diagnostics::Debug::WriteLine("OnCheckUrl: " + url);
			//AIMP::SDK::Services::Playback::AimpCheckUrl ^tmp = this->_checkUrl;
			//if (tmp != nullptr)
			//{
			//	return tmp(url);
			//}

			return false;
		}

		virtual property AIMP36SDK::IAIMPServicePlayer* ServicePlayer
		{
			AIMP36SDK::IAIMPServicePlayer* get()
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

		virtual property PlayerState State
		{
			PlayerState get()
			{
				int state = _player->GetState();
				return (PlayerState)state;
			}
		}

		virtual property IAimpFileInfo^ CurrentFileInfo
		{
			IAimpFileInfo^ get()
			{
				AIMP36SDK::IAIMPFileInfo* fi;
				_player->GetInfo(&fi);

				if (fi == NULL)
				{
					return nullptr;
				}

				AIMP::PlayList::AimpFileInfo^ fileInfo = gcnew AIMP::PlayList::AimpFileInfo(fi);
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

				return gcnew AIMP::SDK::PlayList::AimpPlayListItem(item);
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
			void raise(AIMP::SDK::PlayerState state)
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

		virtual void Play(IPlaybackQueueItem ^queueItem)
		{
			_player->Play(((AimpPlaybackQueueItem^)queueItem)->InternalAimpObject);
		}

		virtual void Play(IAimpPlayListItem ^playListItem)
		{
			_player->Play2(((AIMP::SDK::PlayList::AimpPlayListItem^)playListItem)->InternalAimpObject);
		}

		virtual void Play(IAimpPlayList^ playList)
		{
			_player->Play3(((AIMP::SDK::PlayList::AimpPlayList^)playList)->InternalAimpObject);
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

		bool onCheckUrl(String ^url);
	};

	private ref class AIMPControllerInitializer : public System::MarshalByRefObject
	{
	public:
		static String^ TypeName = "";

		AimpPlayer<StaticSingleThreadAllocator>^ CreateWithStaticAllocator(AIMP::SDK360::ManagedAimpCore^ Ctrl, int PlgUID, int AppDomainID, bool CrossDmn/*, CentralizedEventController^ evCtrl*/)
		{
			return gcnew AimpPlayer<StaticSingleThreadAllocator>(Ctrl, PlgUID, AppDomainID, CrossDmn/*, evCtrl*/);
		}
	};
}
