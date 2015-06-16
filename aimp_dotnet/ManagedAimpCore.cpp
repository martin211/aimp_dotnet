#include "Stdafx.h"
#include "ManagedAimpCore.h"
#include "AIMP_SDK\aimp3_60_sdk.h"
#include "AIMP_SDK\IUnknownInterfaceImpl.h"

namespace AIMP
{
	/// <summary>
	/// 
	/// </summary>
	namespace SDK360
	{
		using namespace System;
		using namespace System::Runtime::InteropServices;

		using namespace AIMP36SDK;
		
		class AIMPMessageHook : public AIMP36SDK::IUnknownInterfaceImpl<AIMP36SDK::IAIMPMessageHook>
		{
		public:
			explicit AIMPMessageHook(gcroot<ManagedAimpCore^> aimp36_manager)
				:
				aimp36_manager_(aimp36_manager)
			{}

			virtual void WINAPI CoreMessage(DWORD AMessage, int AParam1, void *AParam2, HRESULT *AResult) {
				aimp36_manager_->OnCoreMessage((AIMP::SDK::AimpMessages::AimpCoreMessageType)AMessage, AParam1);
			}

		private:
			gcroot<ManagedAimpCore^> aimp36_manager_;
		};

		ManagedAimpCore::ManagedAimpCore(AIMP36SDK::IAIMPCore* core)
		{
			_core = core;
			_nativeEventHelper = new EventHelper();

			AIMP36SDK::IAIMPServiceMessageDispatcher* aimp_service_message_dispatcher;
			core->QueryInterface(AIMP36SDK::IID_IAIMPServiceMessageDispatcher, reinterpret_cast<void**>(&aimp_service_message_dispatcher));
			_hook = new AIMPMessageHook(this);			
			aimp_service_message_dispatcher->Hook(_hook);
			_messageDispatcher = aimp_service_message_dispatcher;
		}

		ManagedAimpCore::~ManagedAimpCore()
		{
			_messageDispatcher->Unhook(_hook);
			_core->Release();
			_core = NULL;
		}

		/// <summary>
		/// Gets the specified path.
		/// </summary>
		/// <param name="pathType">Type of the path.</param>
		/// <returns></returns>
		String^ ManagedAimpCore::GetPath(AIMP::SDK::AimpMessages::AimpCorePathType pathType)
		{
			AIMP36SDK::IAIMPString* res;

			_core->GetPath((int) pathType, &res);
			AIMP36SDK::IAIMPString_ptr path(res, false);

			return gcnew System::String(std::wstring(path->GetData(), path->GetLength()).c_str());			
		}
		
		/// <summary>
		/// Registers the extension.
		/// </summary>
		/// <param name="extensionId">The extension identifier.</param>
		/// <param name="extension">The extension.</param>
		/// <returns></returns>
		bool ManagedAimpCore::RegisterExtension(GUID extensionId, IUnknown* extension)
		{
			HRESULT result = _core->RegisterExtension(extensionId, extension);
			return result == S_OK;
		}

		void ManagedAimpCore::UnregisterExtension(IUnknown* extension)
		{
			_core->UnregisterExtension(extension);
		}
		
		/// <summary>
		/// Called when [core message].
		/// </summary>
		/// <param name="param1">The param1.</param>
		/// <param name="param2">The param2.</param>
		void ManagedAimpCore::OnCoreMessage(AIMP::SDK::AimpMessages::AimpCoreMessageType param1, int param2)
		{			
			CoreMessage(param1, param2);			
		}

		void ManagedAimpCore::OnPlaylistActivated(Object ^sender, EventArgs ^args)
		{
			PlaylistActivated(sender, args);
		}

		/// <summary>
		/// Somes the event proxy.
		/// </summary>
		/// <param name="This">The this.</param>
		/// <param name="param">The parameter.</param>
		/// <param name="param1">The param1.</param>
		void SomeEventProxy(gcroot<ManagedAimpCore^> This, DWORD param, int param1)
		{
			This->OnCoreMessage((AIMP::SDK::AimpMessages::AimpCoreMessageType)param, param1);
		}

		void PlaylistActivatedEventProxy(gcroot<ManagedAimpCore^> This)
		{
		}

		/// <summary>
		/// Gets the service.
		/// </summary>
		/// <param name="iid">The iid.</param>
		/// <param name="service">The service.</param>
		/// <returns></returns>
		HRESULT ManagedAimpCore::GetService(REFIID iid, void** service)
		{
			return _core->QueryInterface(iid, service);			
		}			

		IUnknown* ManagedAimpCore::QueryInterface(REFIID iid)
		{
			IUnknown* service;
			HRESULT result = _core->QueryInterface(iid, (void**)&service);
			if (result != S_OK)
			{
				return NULL;
			}

			return service;
		}
			
		/// <summary>
		/// Creates the action event.
		/// </summary>
		/// <returns></returns>
		IAIMPActionEvent* ManagedAimpCore::CreateActionEvent()
		{
			IAIMPActionEvent* actionEvent = NULL;
			CheckResult(_core->CreateObject(IID_IAIMPActionEvent, (void**)&actionEvent));
			return actionEvent;
		}

		/// <summary>
		/// Checks the result.
		/// </summary>
		/// <param name="result">The result.</param>
		void ManagedAimpCore::CheckResult(HRESULT result)
		{
			if (result != S_OK)
			{
				throw "Invalid operation";
			}
		}

		int ManagedAimpCore::Send(int message, int value)
		{
			void* val;
			_messageDispatcher->Send((DWORD)message, value, &val);
			return (int) val;
		}
		
		/// <summary>
		/// Creates the new AIMP stream.
		/// </summary>
		AIMP36SDK::IAIMPStream* ManagedAimpCore::CreateStream()
		{
			AIMP36SDK::IAIMPStream* stream;
			_core->CreateObject(AIMP36SDK::IID_IAIMPMemoryStream, (void**)&stream);
			return stream;
		}

		AIMP36SDK::IAIMPCore* ManagedAimpCore::GetAimpCore()
		{
			return _core;
		}


		void ManagedAimpCore::CoreMessage::add(AimpEventsDelegate^ onCoreMessage)
		{
			bool tmp = this->_coreMessage == nullptr;
			this->_coreMessage = (AimpEventsDelegate^) Delegate::Combine(this->_coreMessage, onCoreMessage);
			if (tmp && this->_coreMessage != nullptr)
			{				
				_coreMessageCallback = new AIMP::Callback;
				*_coreMessageCallback = _nativeEventHelper->RegisterCallback(boost::bind(SomeEventProxy, gcroot<ManagedAimpCore^>(this), _1, _2));				
			}
		}
		
		void ManagedAimpCore::CoreMessage::remove(AimpEventsDelegate^ onCoreMessage)
		{
			bool tmp = this->_coreMessage == nullptr;
			this->_coreMessage = (AimpEventsDelegate^) Delegate::Combine(this->_coreMessage, onCoreMessage);
			if (tmp && this->_coreMessage != nullptr)
			{
				_nativeEventHelper->UnregisterCallback(*_coreMessageCallback);
			}
		}

		void ManagedAimpCore::CoreMessage::raise(AIMP::SDK::AimpMessages::AimpCoreMessageType param1, int param2)
		{			
			AimpEventsDelegate^ tmp = this->_coreMessage;
			if (tmp != nullptr)
			{
				tmp(param1, param2);
			}			
		}


		void ManagedAimpCore::PlaylistActivated::add(EventHandler ^onEvent)
		{
			bool tmp = this->_playlistActivated == nullptr;
			this->_playlistActivated = (EventHandler^) Delegate::Combine(this->_playlistActivated, onEvent);
			if (tmp && this->_playlistActivated != nullptr)
			{
				_playListActivatedCallback = new AIMP::Callback;
				*_playListActivatedCallback = _nativeEventHelper->RegisterCallback(boost::bind(PlaylistActivatedEventProxy, gcroot<ManagedAimpCore^>(this), _1));
			}
		}

		void ManagedAimpCore::PlaylistActivated::remove(EventHandler ^onCoreMessage)
		{
		}

		void ManagedAimpCore::PlaylistActivated::raise(Object ^object, EventArgs ^args)
		{
		}


		void ManagedAimpCore::PlaylistAdded::add(EventHandler ^onCoreMessage)
		{
		}

		void ManagedAimpCore::PlaylistAdded::remove(EventHandler ^onCoreMessage)
		{
		}

		void ManagedAimpCore::PlaylistAdded::raise(Object ^object, EventArgs ^args)
		{
		}


		void ManagedAimpCore::PlaylistRemoved::add(EventHandler ^onCoreMessage)
		{
		}

		void ManagedAimpCore::PlaylistRemoved::remove(EventHandler ^onCoreMessage)
		{
		}

		void ManagedAimpCore::PlaylistRemoved::raise(Object ^object, EventArgs ^args)
		{
		}
	}
}