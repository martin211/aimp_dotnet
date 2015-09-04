#pragma once
#include "..\BaseManager.h"

namespace  AIMP
{
	namespace SDK
	{
		using namespace System;

		using namespace AIMP36SDK;
		using namespace AIMP::SDK;
		using namespace AIMP::Services::PlaybackManager;

		public ref class PlaybackManager : public AimpBaseManager, IPlaybackQueueService
		{
		private:
			IAIMPServicePlaybackQueue *_service;

		public:
			explicit PlaybackManager(ManagedAimpCore ^core) : AimpBaseManager(core)
			{
				IAIMPServicePlaybackQueue *service;
				if (!CheckResult(core->GetService(IID_IAIMPServicePlaybackQueue, (void**)&service)))
				{
					throw gcnew System::ApplicationException("Unable create AIMP service");
				}

				_service = service;
			}

			virtual event AimpCheckUrl ^OnCheckURL
			{
				void add(AimpCheckUrl ^onEvent)
				{

				}
				void remove(AimpCheckUrl ^onEvent)
				{

				}
			}

			virtual IPlaybackQueueItem ^GetNextTrack()
			{
				IAIMPPlaybackQueueItem *track;

				if (CheckResult(_service->GetNextTrack(&track)))
				{
					return gcnew
				}
			}

			virtual IPlaybackQueueItem ^GetPrevTrack()
			{

			}
		};
	}
}



