#pragma once
#include "..\..\AIMP_SDK\aimp3_60_sdk.h"
#include "..\..\ObjectHelper.h"
#include "..\PlayListManager\AimpPlayListItem.h"

namespace AIMP
{
	namespace SDK
	{
		using namespace System;
		using namespace AIMP36SDK;
		using namespace AIMP::SDK::Services::PlayListManager;

		public ref class AimpPlaybackQueueItem : public AimpObject<AIMP36SDK::IAIMPPlaybackQueueItem>, public IPlaybackQueueItem
		{
		public:
			explicit AimpPlaybackQueueItem(AIMP36SDK::IAIMPPlaybackQueueItem *aimpItem) : AimpObject(aimpItem)
			{ }

			virtual property Object ^UserData
			{
				Object ^get()
				{
					IUnknown *item;
					InternalAimpObject->GetValueAsObject(AIMP_PLAYBACKQUEUEITEM_PROPID_CUSTOM, IID_IUnknown, (void**) &item);
					return System::Runtime::InteropServices::Marshal::GetObjectForIUnknown(IntPtr(item));					
				}
				void set(Object^ value)
				{
					//InternalAimpObject->SetValueAsObject(AIMP_PLAYBACKQUEUEITEM_PROPID_CUSTOM, value);
					throw gcnew System::NotImplementedException("Not implemented");
				}
			}

			virtual property IAimpPlayListItem^ PlayListItem
			{
				IAimpPlayListItem^ get()
				{
					IAIMPPlaylistItem *item;
					InternalAimpObject->GetValueAsObject(AIMP_PLAYBACKQUEUEITEM_PROPID_PLAYLISTITEM, IID_IAIMPPlaylistItem, (void**) &item);
					return gcnew PlayList::AimpPlayListItem(item);
				}
				void set(IAimpPlayListItem^ value)
				{
					InternalAimpObject->SetValueAsObject(AIMP_PLAYBACKQUEUEITEM_PROPID_PLAYLISTITEM, ((PlayList::AimpPlayListItem^)value)->InternalAimpObject);
				}
			}
		};
	}
}