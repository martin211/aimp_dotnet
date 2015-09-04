#pragma once
#include "AIMP_SDK\aimp3_60_sdk.h"
#include "EventHelper.h"
#include <Unknwnbase.h>
#include "AIMP_SDK\IUnknownInterfaceImpl.h"

namespace AIMP36SDK
{
	#include "AIMP_SDK\AIMP360\apiMenu.h"	
}

namespace AIMP
{	
	namespace SDK360
	{
		using namespace System;
		using namespace AIMP::SDK;
		using namespace AIMP::SDK::Interfaces;
		using namespace AIMP::SDK::Extensions;
		using namespace AIMP36SDK;		
		using namespace AIMP::SDK::Services::PlayListManager;

		delegate void ChangeHandler(AimpMessages::AimpCoreMessageType, int);

		/// <summary>
		/// Managed Core class.
		/// </summary>
		public ref class ManagedAimpCore : public IAimpCore
		{		
			
		public:			
			/// <summary>
			/// Initializes a new instance of the <see cref="ManagedAimpCore"/> class.
			/// </summary>
			/// <param name="core">The core.</param>
			ManagedAimpCore(AIMP36SDK::IAIMPCore* core);
			
			/// <summary>
			/// Finalizes an instance of the <see cref="ManagedAimpCore"/> class.
			/// </summary>
			~ManagedAimpCore();
			
			virtual String^ GetPath(AimpMessages::AimpCorePathType pathType);

			virtual void SendMessage(AIMP::SDK::AimpMessages::AimpCoreMessageType message, int value, Object ^obj);			
			
			//virtual bool RegisterExtension(Guid extensionId, IUnknown* extension);
			
			virtual event AimpEventsDelegate^ CoreMessage
			{
				virtual void add(AimpEventsDelegate^ onCoreMessage);
				virtual void remove(AimpEventsDelegate^ onCoreMessage);
				void raise(AIMP::SDK::AimpMessages::AimpCoreMessageType param1, int param2);
			}

			virtual event AIMP::SDK::Extensions::PlayListHandler ^PlaylistActivated
			{
				virtual void add(AIMP::SDK::Extensions::PlayListHandler ^onEvent);
				virtual void remove(AIMP::SDK::Extensions::PlayListHandler ^onEvent);
			}

			virtual event AIMP::SDK::Extensions::PlayListHandler ^PlaylistAdded
			{
				virtual void add(AIMP::SDK::Extensions::PlayListHandler ^onEvent);
				virtual void remove(AIMP::SDK::Extensions::PlayListHandler ^onEvent);
			}

			virtual event AIMP::SDK::Extensions::PlayListHandler ^PlaylistRemoved
			{
				virtual void add(AIMP::SDK::Extensions::PlayListHandler ^onEvent);
				virtual void remove(AIMP::SDK::Extensions::PlayListHandler ^onEvent);
			}

			void OnCoreMessage(AIMP::SDK::AimpMessages::AimpCoreMessageType param1, int param2);			

		internal:
			IAIMPActionEvent* CreateActionEvent();

			HRESULT GetService(REFIID iid, void** service);

			static IUnknown *QueryInterface(REFIID iid);

			bool RegisterExtension(GUID iid, IUnknown* extension);

			void UnregisterExtension(IUnknown* extension);

			void CheckResult(HRESULT result);

			static AIMP36SDK::IAIMPCore* GetAimpCore();

			void ShowNotification(bool autoHide, String ^notification);

			AIMP36SDK::IAIMPStream* CreateStream();

			void OnPlaylistActivated(AIMP36SDK::IAIMPPlaylist *playlist);

			void OnPlayListAdded(AIMP36SDK::IAIMPPlaylist *playlist);

			void OnPlayListRemoved(AIMP36SDK::IAIMPPlaylist *playlist);

			bool OnCheckUrl(String ^url);

		private:
			static IAIMPCore* _core;			
			EventHelper* _nativeEventHelper;
			Callback* _coreMessageCallback;
			Callback* _playListActivatedCallback;

			AIMP36SDK::IAIMPServiceMessageDispatcher* _messageDispatcher;
			IAIMPMessageHook* _hook;			

			AimpEventsDelegate ^_coreMessage;
			AIMP::SDK::Extensions::PlayListHandler ^_playlistActivated;
			AIMP::SDK::Extensions::PlayListHandler ^_playlistAdded;
			AIMP::SDK::Extensions::PlayListHandler ^_playlistRemoved;
			/*AIMP::SDK::Services::Player::AimpCheckUrl ^_checkUrl;*/
		};
	}
}