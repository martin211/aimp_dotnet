#include "Stdafx.h"
#include "ManagedAimpCore.h"
#include "AIMP_SDK\aimp3_60_sdk.h"
#include "AIMP_SDK\IUnknownInterfaceImpl.h"
#include "Services\PlayList\AimpPlayList.h"

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
		/// Gets the specified AIMP path.
		/// </summary>
		/// <param name="pathType">Path type.</param>
		/// <param name="pathResult"></param>
		/// <returns></returns>
		AIMP::SDK::Services::ActionResult ManagedAimpCore::GetPath(AIMP::SDK::AimpMessages::AimpCorePathType pathType, String ^%pathResult)
		{
			AIMP36SDK::IAIMPString* res;

			_core->GetPath((int) pathType, &res);
			AIMP36SDK::IAIMPString_ptr path(res, false);

			pathResult = gcnew System::String(std::wstring(path->GetData(), path->GetLength()).c_str());
			return AIMP::SDK::Services::ActionResult::Ok;
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

		void ManagedAimpCore::OnPlaylistActivated(AIMP36SDK::IAIMPPlaylist *playlist)
		{			
			AIMP::SDK::PlayList::AimpPlayList ^pl = gcnew AIMP::SDK::PlayList::AimpPlayList(playlist);
			this->PlaylistActivated(pl->Name, pl->Id);
			pl = nullptr;
		}

		void ManagedAimpCore::OnPlayListAdded(AIMP36SDK::IAIMPPlaylist *playlist)
		{
			AIMP::SDK::PlayList::AimpPlayList ^pl = gcnew AIMP::SDK::PlayList::AimpPlayList(playlist);
			this->PlaylistAdded(pl->Name, pl->Id);
			pl = nullptr;
		}

		void ManagedAimpCore::OnPlayListRemoved(AIMP36SDK::IAIMPPlaylist *playlist)
		{
			AIMP::SDK::PlayList::AimpPlayList ^pl = gcnew AIMP::SDK::PlayList::AimpPlayList(playlist);
			this->PlaylistRemoved(pl->Name, pl->Id);
			pl = nullptr;
		}

		bool ManagedAimpCore::OnCheckUrl(String ^url)
		{
			return this->CheckUrl(url);
		}

		/// <summary>
		/// Somes the event proxy.
		/// </summary>
		/// <param name="This">The this.</param>
		/// <param name="param">The parameter.</param>
		/// <param name="param1">The param1.</param>
		void CoreMessageEventProxy(gcroot<ManagedAimpCore^> This, DWORD param, int param1)
		{
			This->OnCoreMessage((AIMP::SDK::AimpMessages::AimpCoreMessageType)param, param1);
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

		HRESULT ManagedAimpCore::SendMessage(AIMP::SDK::AimpMessages::AimpCoreMessageType message, int value, Object ^obj)
		{	
			HRESULT r;

			if (message == AIMP::SDK::AimpMessages::AimpCoreMessageType::AIMP_MSG_CMD_SHOW_NOTIFICATION)
			{
				r = ShowNotification(value == 0, (String^)obj);
			}
			else
			{
				r = _messageDispatcher->Send((DWORD)message, value, (void*)&obj);
			}

			return r;
		}

		HRESULT ManagedAimpCore::ShowNotification(bool autoHide, String ^notification)
		{
			IAIMPString *str = ObjectHelper::MakeAimpString(_core, notification);
			return _messageDispatcher->Send((DWORD)AIMP::SDK::AimpMessages::AimpCoreMessageType::AIMP_MSG_CMD_SHOW_NOTIFICATION, autoHide ? 0 : 1, str->GetData());
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


		//void ManagedAimpCore::CoreMessage::add(AimpEventsDelegate^ onCoreMessage)
		//{
		//	if (_coreMessage == nullptr)
		//	{
		//		_coreMessageCallback = new AIMP::Callback;
		//		*_coreMessageCallback = _nativeEventHelper->RegisterCallback(boost::bind(CoreMessageEventProxy, gcroot<ManagedAimpCore^>(this), _1, _2));
		//		_coreMessage = gcnew System::Collections::Generic::List<AimpEventsDelegate^>(2);
		//	}

		//	_coreMessage->Add(onCoreMessage);			
		//}
	
		//void ManagedAimpCore::CoreMessage::remove(AimpEventsDelegate^ onCoreMessage)
		//{
		//	if (_coreMessage != nullptr)
		//	{				
		//		System::Threading::Monitor::Enter(_coreMessage);
		//		if (_coreMessage->Contains(onCoreMessage))
		//		{
		//			_coreMessage->Remove(onCoreMessage);
		//		}
		//		System::Threading::Monitor::Exit(_coreMessage);
		//	}
		//}

		//void ManagedAimpCore::CoreMessage::raise(AIMP::SDK::AimpMessages::AimpCoreMessageType param1, int param2)
		//{
		//	if (_coreMessage == nullptr || _coreMessage->Count == 0)
		//	{
		//		return;
		//	}

		//	System::Threading::Monitor::Enter(_coreMessage);			
		//	for each (AimpEventsDelegate^ item in _coreMessage)
		//	{
		//		item(param1, param2);
		//	}
		//	System::Threading::Monitor::Exit(_coreMessage);
		//}


		//void ManagedAimpCore::PlaylistActivated::add(AIMP::SDK::Extensions::PlayListHandler ^onEvent)
		//{
		//	bool tmp = _playListActivatedHandlers == nullptr;
		//	if (tmp)
		//	{
		//		_playListActivatedHandlers = gcnew List<AIMP::SDK::Extensions::PlayListHandler^>(2);
		//		//_playlistActivated = (AIMP::SDK::Extensions::PlayListHandler^) Delegate::Combine(_playlistActivated, onEvent);
		//	}

		//	_playListActivatedHandlers->Add(onEvent);
		//}

		//void ManagedAimpCore::PlaylistActivated::remove(AIMP::SDK::Extensions::PlayListHandler ^onEvent)
		//{
		//	bool tmp = _playListActivatedHandlers != nullptr;
		//	if (tmp)
		//	{
		//		System::Threading::Monitor::Enter(_playListActivatedHandlers);
		//		if (_playListActivatedHandlers->Contains(onEvent))
		//		{
		//			_playListActivatedHandlers->Remove(onEvent);
		//		}
		//		System::Threading::Monitor::Exit(_playListActivatedHandlers);
		//	}
		//}


		//void ManagedAimpCore::PlaylistAdded::add(AIMP::SDK::Extensions::PlayListHandler ^onEvent)
		//{
		//	bool tmp = _playlistAdded == nullptr;
		//	if (tmp)
		//	{
		//		_playlistAdded = (AIMP::SDK::Extensions::PlayListHandler^) Delegate::Combine(_playlistAdded, onEvent);
		//	}
		//}

		//void ManagedAimpCore::PlaylistAdded::remove(AIMP::SDK::Extensions::PlayListHandler ^onEvent)
		//{
		//	bool tmp = _playlistAdded != nullptr;
		//	if (tmp)
		//	{
		//		_playlistAdded = (AIMP::SDK::Extensions::PlayListHandler^)Delegate::Remove(this->_playlistAdded, onEvent);
		//	}
		//}


		//void ManagedAimpCore::PlaylistRemoved::add(AIMP::SDK::Extensions::PlayListHandler ^onEvent)
		//{
		//	bool tmp = _playlistRemoved == nullptr;
		//	if (tmp)
		//	{
		//		_playlistRemoved = (AIMP::SDK::Extensions::PlayListHandler^) Delegate::Combine(_playlistRemoved, onEvent);
		//	}
		//}

		//void ManagedAimpCore::PlaylistRemoved::remove(AIMP::SDK::Extensions::PlayListHandler ^onEvent)
		//{
		//	bool tmp = _playlistRemoved != nullptr;
		//	if (tmp)
		//	{
		//		_playlistRemoved = (AIMP::SDK::Extensions::PlayListHandler^)Delegate::Remove(this->_playlistRemoved, onEvent);
		//	}
		//}


		//void ManagedAimpCore::CheckUrl::add(AIMP::SDK::Services::Playback::AimpCheckUrl ^onEvent)
		//{
		//	bool tmp = _checkUrl == nullptr;
		//	if (tmp)
		//	{
		//		_checkUrl = (AIMP::SDK::Services::Playback::AimpCheckUrl^) Delegate::Combine(_checkUrl, onEvent);
		//	}
		//}

		//void ManagedAimpCore::CheckUrl::remove(AIMP::SDK::Services::Playback::AimpCheckUrl ^onEvent)
		//{
		//	bool tmp = _checkUrl != nullptr;
		//	if (tmp)
		//	{
		//		_checkUrl = (AIMP::SDK::Services::Playback::AimpCheckUrl^) Delegate::Remove(_checkUrl, onEvent);
		//	}
		//}
	}
}