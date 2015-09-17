#pragma once
#include "..\..\AIMP_SDK\aimp3_60_sdk.h"
#include "..\BaseManager.h"
#include "AimpPlaybackQueueItem.h"

namespace AIMP
{
	namespace SDK
	{		
		using namespace AIMP36SDK;
		using namespace AIMP::SDK;

		using namespace AIMP::SDK::Services::PlayListManager;
		using namespace AIMP::SDK::Services::Playback;

		public ref class ServicePlaybackQueue : public AimpBaseManager,  public IPlaybackQueueService
		{
		private:
			IAIMPServicePlaybackQueue *_service;
			AimpCheckUrl ^_checkUrlHandler;

		public:
			explicit ServicePlaybackQueue(ManagedAimpCore ^core) : AimpBaseManager(core)
			{
				IAIMPServicePlaybackQueue *service;
				if (!CheckResult(core->GetService(IID_IAIMPServicePlaybackQueue, (void**) &service)))
				{
					throw gcnew System::ApplicationException("Unable create AIMP service");
				}

				_service = service;
			}

			virtual IPlaybackQueueItem^ GetNextTrack()
			{
				IAIMPPlaybackQueueItem *item;
				if (!CheckResult(_service->GetNextTrack(&item)))
				{
		//			return gcnew AimpPlaybackQueueItem(item);
				}

				return nullptr;
			}

			virtual IPlaybackQueueItem^ GetPrevTrack()
			{
				IAIMPPlaybackQueueItem *item;
				if (!CheckResult(_service->GetPrevTrack(&item)))
				{
//					return gcnew AimpPlaybackQueueItem(item);
				}

				return nullptr;
			}

			virtual event AimpCheckUrl ^OnCheckURL
			{
				void add(AimpCheckUrl ^onEvent)
				{
					bool tmp = _checkUrlHandler == nullptr;
					if (tmp)
					{
						_checkUrlHandler = (AimpCheckUrl^)System::Delegate::Combine(_checkUrlHandler, onEvent);
					}
				}

				void remove(AimpCheckUrl ^onEvent)
				{
					bool tmp = _checkUrlHandler != nullptr;
					if (tmp)
					{
						_checkUrlHandler = (AimpCheckUrl^)System::Delegate::Remove(_checkUrlHandler, onEvent);
					}
				}
			}
		};
	}
}