#include <Stdafx.h>
#include "AimpPlayListGroup.h"
#include "AimpPlayListItem.h"

namespace AIMP
{
	namespace SDK
	{
		namespace PlayList
		{
			using namespace AIMP36SDK;
			using namespace AIMP::SDK::Services::PlayListManager;

			System::String^ AimpPlayListGroup::Name::get()
			{
				return ObjectHelper::GetString(_aimpObject, AIMP_PLAYLISTGROUP_PROPID_NAME);
			}

			bool AimpPlayListGroup::Expanded::get()
			{
				return ObjectHelper::GetBool(_aimpObject, AIMP_PLAYLISTGROUP_PROPID_EXPANDED);
			}

			void AimpPlayListGroup::Expanded::set(bool value)
			{
				ObjectHelper::SetBool(_aimpObject, AIMP_PLAYLISTGROUP_PROPID_EXPANDED, value);
			}

			double AimpPlayListGroup::Duration::get()
			{
				return ObjectHelper::GetFloat(_aimpObject, AIMP_PLAYLISTGROUP_PROPID_DURATION);
			}

			void AimpPlayListGroup::Duration::set(double value)
			{
				ObjectHelper::SetFloat(_aimpObject, AIMP_PLAYLISTGROUP_PROPID_DURATION, value);
			}

			int AimpPlayListGroup::Index::get()
			{
				return ObjectHelper::GetInt32(_aimpObject, AIMP_PLAYLISTGROUP_PROPID_INDEX);
			}

			bool AimpPlayListGroup::Selected::get()
			{
				return ObjectHelper::GetBool(_aimpObject, AIMP_PLAYLISTGROUP_PROPID_SELECTED);
			}

			void AimpPlayListGroup::Selected::set(bool value)
			{
				ObjectHelper::SetBool(_aimpObject, AIMP_PLAYLISTGROUP_PROPID_SELECTED, value);
			}

			int AimpPlayListGroup::Count::get()
			{
				return _aimpObject->GetItemCount();
			}

			IAimpPlayListItem ^AimpPlayListGroup::GetItem(int index)
			{
				if (_item == nullptr)
				{
					AIMP36SDK::IAIMPPlaylistItem *item;
					_aimpObject->GetItem(index, IID_IAIMPPlaylistItem, (void**) &item);
					_item = gcnew AimpPlayListItem(item);
				}

				return _item;
			}
		}
	}
}