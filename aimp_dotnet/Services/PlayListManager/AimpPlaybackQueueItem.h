#include "..\..\AIMP_SDK\aimp3_60_sdk.h"
#include "..\..\AimpObjectExtension.h"
#include "..\PlayListManager\AimpPlayListItem.h"

namespace AIMP
{
	namespace PlayList
	{
		using namespace System;
		using namespace AIMP36SDK;
		using namespace AIMP::SDK::Services::PlayListManager;

		public ref class AimpPlaybackQueueItem : public AimpObject<AIMP36SDK::IAIMPPlaybackQueueItem>, public IAimpPlaybackQueueItem
		{
		public:
			virtual property Object^ UserData
			{
				Object^ get()
				{
					throw gcnew System::NotImplementedException("Not implemented");
				}
				void set(Object^ value)
				{
					throw gcnew System::NotImplementedException("Not implemented");
				}
			}

			virtual property IAimpPlayListItem^ PlayListItem
			{
				IAimpPlayListItem^ get()
				{
					IAIMPPlaylistItem *item;
					_aimpObject->GetValueAsObject(AIMP_PLAYBACKQUEUEITEM_PROPID_PLAYLISTITEM, IID_IAIMPPlaylistItem, (void**) &item);
					return gcnew AIMP::PlayList::AimpPlayListItem(item);
				}
				void set(IAimpPlayListItem^ value)
				{
					_aimpObject->SetValueAsObject(AIMP_PLAYBACKQUEUEITEM_PROPID_PLAYLISTITEM, ((AimpPlayListItem^)value)->InternalAimpObject);
				}
			}
		};
	}
}