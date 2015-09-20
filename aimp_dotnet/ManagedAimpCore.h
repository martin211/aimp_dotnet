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
		using namespace System::Collections::Generic;

		using namespace AIMP::SDK;
		using namespace AIMP::SDK::Interfaces;
		using namespace AIMP::SDK::Extensions;
		using namespace AIMP36SDK;		
		using namespace AIMP::SDK::Services::PlayListManager;

		delegate void ChangeHandler(AimpMessages::AimpCoreMessageType, int);

		/// <summary>
		/// Wrapper on IAIMPCore interface.
		/// </summary>
		public ref class ManagedAimpCore
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
			
			virtual AIMP::SDK::Services::ActionResult GetPath(AimpMessages::AimpCorePathType pathType, String ^%path);

			virtual HRESULT SendMessage(AIMP::SDK::AimpMessages::AimpCoreMessageType message, int value, Object ^obj);			
			
			//virtual bool RegisterExtension(Guid extensionId, IUnknown* extension);
			
			virtual event AimpEventsDelegate^ CoreMessage;

			virtual event AIMP::SDK::Extensions::PlayListHandler ^PlaylistActivated;

			virtual event AIMP::SDK::Extensions::PlayListHandler ^PlaylistAdded;

			virtual event AIMP::SDK::Extensions::PlayListHandler ^PlaylistRemoved;

			virtual event AIMP::SDK::Services::Playback::AimpCheckUrl ^CheckUrl;

			void OnCoreMessage(AIMP::SDK::AimpMessages::AimpCoreMessageType param1, int param2);

		internal:
			IAIMPActionEvent* CreateActionEvent();

			HRESULT GetService(REFIID iid, void** service);

			static IUnknown *QueryInterface(REFIID iid);

			bool RegisterExtension(GUID iid, IUnknown* extension);

			void UnregisterExtension(IUnknown* extension);

			static AIMP36SDK::IAIMPCore* GetAimpCore();

			HRESULT ShowNotification(bool autoHide, String ^notification);

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

			List<AimpEventsDelegate^> ^_coreMessage;
			List<AIMP::SDK::Extensions::PlayListHandler^> ^_playListActivatedHandlers;

			
			AIMP::SDK::Extensions::PlayListHandler ^_playlistAdded;
			AIMP::SDK::Extensions::PlayListHandler ^_playlistRemoved;
			AIMP::SDK::Services::Playback::AimpCheckUrl ^_checkUrl;
		};
	}
}