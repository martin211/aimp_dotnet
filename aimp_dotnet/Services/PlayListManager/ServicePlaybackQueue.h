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

		public ref class ServicePlaybackQueue : public AimpBaseManager,  public AIMP::SDK::Services::PlayListManager::IServicePlaybackQueue
		{
		private:
			IAIMPServicePlaybackQueue *_service;

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

			virtual IAimpPlaybackQueueItem^ GetNextTrack()
			{
				IAIMPPlaybackQueueItem *item;
				if (!CheckResult(_service->GetNextTrack(&item)))
				{
					return gcnew AimpPlaybackQueueItem(item);
				}

				return nullptr;
			}

			virtual IAimpPlaybackQueueItem^ GetPrevTrack()
			{
				IAIMPPlaybackQueueItem *item;
				if (!CheckResult(_service->GetPrevTrack(&item)))
				{
					return gcnew AimpPlaybackQueueItem(item);
				}

				return nullptr;
			}
		};
	}
}