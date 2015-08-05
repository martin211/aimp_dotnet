#pragma once

#include "DataConversion.h"
#include <vcclr.h>
#include "AIMP_SDK\aimp3_60_sdk.h"
#include "AIMPPlugin.h"
#include "ManagedAimpCore.h"
#include "DataConversion.h"


#include "Services\MenuManager\ServiceMenuManager.h"
#include "Services\ActionManager\ActionManager.h"
#include "Services\MUIManager\MUIManager.h"
#include "Services\AlbumArtManager\AlbumArtManager.h"
#include "Services\ConfigurationManager\ConfigurationManager.h"
#include "Services\PlayListManager\AimpFileInfo.h"
#include "Services\Win32Manager\Win32Manager.h"
#include "Services\PlayListManager\AimpPlaybackQueueItem.h"
#include "Services\PlayListManager\AimpPlayListItem.h"
#include "Services\PlayListManager\AimpPlayList.h"
#include "Services\PlayListManager\PlayListManager.h"
#include "Services\PlayListManager\ServicePlaybackQueue.h"



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

	template<class TConvAlloc>
	private ref class AimpPlayer :
		public MarshalByRefObject,
		public IAimpPlayer
	{
	private:
		typedef DataConverter Converter;

	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="AIMP3Controller{TConvAlloc}" /> class.
		/// </summary>
		/// <param name="core">The aimp core.</param>
		/// <param name="pluginId">The plugin identifier.</param>
		/// <param name="applicationDomainId">The application domain identifier.</param>
		/// <param name="isCrossDomain">The is cross domain.</param>
		AimpPlayer(AIMP::SDK360::ManagedAimpCore ^core, int pluginId, int applicationDomainId, bool isCrossDomain)
		{
			//_aimpCore = core;
			//_managerCore = gcnew AIMP::SDK360::ManagedAimpCore(core, nullptr);
			_managerCore = core;
			AIMP36SDK::IAIMPServicePlayer* ps;
			((ManagedAimpCore^) _managerCore)->GetService(AIMP36SDK::IID_IAIMPServicePlayer, reinterpret_cast<void**>(&ps));
			_player = ps;

			_managerCore->CoreMessage += gcnew AimpEventsDelegate(this, &AIMP::AimpPlayer<TConvAlloc>::OnCoreMessage);
		}

		~AimpPlayer()
		{
			_managerCore->CoreMessage -= gcnew AimpEventsDelegate(this, &AIMP::AimpPlayer<TConvAlloc>::OnCoreMessage);
			_managerCore = nullptr;
			_player->Release();
			_player = nullptr;
		}

		virtual property IAimpCore^ Core
		{
			IAimpCore^ get()
			{
				return _managerCore;
			}

		}

		virtual property IMenuManager^ MenuManager
		{
			IMenuManager^ get()
			{
				if (_menuManager == nullptr)
				{
					_menuManager = gcnew ServiceMenuManager((ManagedAimpCore^) _managerCore);
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
					_actionManager = gcnew AIMP::ActionManager((ManagedAimpCore^) _managerCore);
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
					_muiManager = gcnew AIMP::MIUManager((ManagedAimpCore^) _managerCore);
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
					_artManager = gcnew AIMP::AlbumArtManager((ManagedAimpCore^) _managerCore);
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
					_configManager = gcnew AIMP::ConfigurationManager((ManagedAimpCore^) _managerCore);
				}

				return _configManager;
			}
		}
				
		virtual property IPlayListManager ^PlayListManager
		{
			IPlayListManager ^get()
			{
				if (_playListManager == nullptr)
				{
					_playListManager = gcnew AIMP::SDK::PlayListManager((ManagedAimpCore^) _managerCore);
				}

				return _playListManager;
			}
		}

		virtual property IServicePlaybackQueue ^PlaybackQueueManager
		{
			IServicePlaybackQueue ^get()
			{
				if (_playbackQueueManager == nullptr)
				{
					_playbackQueueManager = gcnew AIMP::SDK::ServicePlaybackQueue((ManagedAimpCore^) _managerCore);
				}

				return _playbackQueueManager;
			}
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
				CheckResult(_player->GetMute(&value));
				return value;
			}

			void set(bool value)
			{
				CheckResult(_player->SetMute(value));
			}
		}

		virtual property float Volume
		{
			float get()
			{
				float value;
				CheckResult(_player->GetVolume(&value));
				return value;
			}

			void set(float value)
			{
				CheckResult(_player->SetVolume(value));
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
				CheckResult(_player->GetPosition(&value));
				return value;
			}

			void set(double value)
			{
				CheckResult(_player->SetPosition(value));
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
					_onStateChanged = onAction;
				}
			}
			void remove(AimpStateChanged^ onAction)
			{
				if (this->_onStateChanged != nullptr)
				{
					_onStateChanged = nullptr;
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
				_onLanguageChanged = (EventHandler^)Delegate::Combine(_onLanguageChanged, onAction);
				if (tmp && _onLanguageChanged == nullptr)
				{
					_onLanguageChanged = onAction;
				}
			}
			void remove(EventHandler ^onAction)
			{
				bool tmp = _onLanguageChanged == nullptr;
				_onLanguageChanged = (EventHandler^)Delegate::Combine(_onLanguageChanged, onAction);
				if (tmp && _onLanguageChanged != nullptr)
				{
					_onLanguageChanged = nullptr;
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
				_onLanguageChanged = (EventHandler^) Delegate::Combine(_onTrackChanged, onAction);
				if (tmp && _onTrackChanged == nullptr)
				{
					_onTrackChanged = onAction;
				}
			}
			void remove(EventHandler ^onAction)
			{
				bool tmp = _onTrackChanged == nullptr;
				_onTrackChanged = (EventHandler^) Delegate::Combine(_onTrackChanged, onAction);
				if (tmp && _onTrackChanged != nullptr)
				{
					_onTrackChanged = nullptr;
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
			_player->Play2(((AIMP::SDK::PlayList::AimpPlayListItem^)playListItem)->InternalAimpObject);
		}

		virtual void Play(IAimpPlayList^ playList)
		{
			_player->Play3(((AIMP::SDK::PlayList::AimpPlayList^)playList)->InternalAimpObject);
		}

	private:
		void CheckResult(HRESULT result)
		{
			((ManagedAimpCore^)_managerCore)->CheckResult(result);
		}

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

		AIMP36SDK::IAIMPMessageHook* aimp_message_hook_;
		AIMP36SDK::IAIMPServicePlayer* _player;
		//AIMP36SDK::IAIMPCore* _aimpCore;		 
		IAimpCore^ _managerCore;		
		AimpEventsDelegate^ _coreMessage;
		IMenuManager^ _menuManager;
		IActionManager^ _actionManager;
		IMUIManager^ _muiManager;
		IAlbumArtManager^ _artManager;
		IConfigurationManager^ _configManager;
		IWin32Manager ^_win32Manager;
		IPlayListManager ^_playListManager;
		IServicePlaybackQueue ^_playbackQueueManager;
		AIMP::SDK::PlayerState _state;
		
		AimpStateChanged ^_onStateChanged;
		EventHandler ^_onLanguageChanged;
		EventHandler ^_onTrackChanged;
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
