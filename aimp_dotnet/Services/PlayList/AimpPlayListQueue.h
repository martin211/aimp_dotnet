#pragma once

#include "..\..\AIMP_SDK\aimp3_60_sdk.h"
#include "..\..\ObjectHelper.h"

namespace AIMP
{
	namespace SDK
	{
		namespace PlayList
		{
			using namespace AIMP36SDK;
			using namespace AIMP::SDK;

			public ref class AimpPlaylistQueue : public AimpObject<AIMP36SDK::IAIMPPlaylistQueue>, public IAimpPlayListQueue
			{
			public:
				virtual property bool IsSuspended
				{
					bool get()
					{
						IAIMPPropertyList *properties;
						_aimpObject->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
						return AIMP::ObjectHelper::GetBool(properties, AIMP_PLAYLISTQUEUE_PROPID_SUSPENDED);
					}
					void set(bool value)
					{
						IAIMPPropertyList *properties;
						_aimpObject->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
						AIMP::ObjectHelper::SetBool(properties, AIMP_PLAYLISTQUEUE_PROPID_SUSPENDED, value);
					}
				}

				virtual void Add(AIMP::SDK::Services::PlayListManager::IAimpPlayListItem^ item, bool insertAtBeginning)
				{
				}

				virtual void AddList(System::Collections::Generic::IList<AIMP::SDK::Services::PlayListManager::IAimpPlayListItem^>^ items, bool insertAtBeginning)
				{
				}

				virtual int Count()
				{
					return _aimpObject->GetItemCount();
				}

				virtual void Delete(AIMP::SDK::Services::PlayListManager::IAimpPlayList^ playList)
				{
				}

				virtual void Delete(AIMP::SDK::Services::PlayListManager::IAimpPlayListItem^ item)
				{
				}

				virtual void Move(AIMP::SDK::Services::PlayListManager::IAimpPlayListItem^ item, int index)
				{
				}

				virtual void Move(int index, int targetIndex)
				{
				}
			};
		}
	}
}