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

		delegate void ChangeHandler(AimpMessages::AimpCoreMessageType, int);

		/// <summary>
		/// Managed Core class.
		/// </summary>
		public ref class ManagedAimpCore : public IAimpCore, public IExtensionPlaylistManagerListener
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

			//virtual bool RegisterExtension(Guid extensionId, IUnknown* extension);
			
			virtual event AimpEventsDelegate^ CoreMessage
			{
				virtual void add(AimpEventsDelegate^ onCoreMessage);
				virtual void remove(AimpEventsDelegate^ onCoreMessage);
				void raise(AIMP::SDK::AimpMessages::AimpCoreMessageType param1, int param2);
			}

			virtual event EventHandler ^PlaylistActivated
			{
				virtual void add(EventHandler ^onCoreMessage);
				virtual void remove(EventHandler ^onCoreMessage);
				void raise(Object ^object, EventArgs ^args);
			}

			virtual event EventHandler ^PlaylistAdded
			{
				virtual void add(EventHandler ^onCoreMessage);
				virtual void remove(EventHandler ^onCoreMessage);
				void raise(Object ^object, EventArgs ^args);
			}

			virtual event EventHandler ^PlaylistRemoved
			{
				virtual void add(EventHandler ^onCoreMessage);
				virtual void remove(EventHandler ^onCoreMessage);
				void raise(Object ^object, EventArgs ^args);
			}

			void OnCoreMessage(AIMP::SDK::AimpMessages::AimpCoreMessageType param1, int param2);
			
			void OnPlaylistActivated(Object ^sender, EventArgs ^args);

		internal:
			IAIMPActionEvent* CreateActionEvent();

			HRESULT GetService(REFIID iid, void** service);

			static IUnknown *QueryInterface(REFIID iid);

			bool RegisterExtension(GUID iid, IUnknown* extension);

			void UnregisterExtension(IUnknown* extension);

			void CheckResult(HRESULT result);

			static AIMP36SDK::IAIMPCore* GetAimpCore();

			int Send(int message, int value);

			AIMP36SDK::IAIMPStream* CreateStream();


		private:
			static IAIMPCore* _core;			
			EventHelper* _nativeEventHelper;
			Callback* _coreMessageCallback;
			Callback* _playListActivatedCallback;

			AIMP36SDK::IAIMPServiceMessageDispatcher* _messageDispatcher;
			IAIMPMessageHook* _hook;			

			AimpEventsDelegate ^_coreMessage;
			EventHandler ^_playlistActivated;
			EventHandler ^_playlistAdded;
			EventHandler ^_playlistRemoved;
		};
	}
}