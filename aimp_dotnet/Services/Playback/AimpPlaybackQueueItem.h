#pragma once

#include "..\..\ObjectHelper.h"
#include "..\PlayList\AimpPlayListItem.h"

namespace AIMP
{
	namespace SDK
	{
		using namespace System;
		
		public ref class AimpPlaybackQueueItem : public AimpObject<IAIMPPlaybackQueueItem>, public AIMP::SDK::Services::Playback::IAimpPlaybackQueueItem
		{
		public:
			explicit AimpPlaybackQueueItem(IAIMPPlaybackQueueItem *aimpItem) : AimpObject(aimpItem)
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