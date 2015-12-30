#include "..\..\Stdafx.h"
#include "AimpPlayListGroup.h"
#include "AimpPlayListItem.h"
#include "..\..\SDK\AimpConverter.h"

namespace AIMP
{
	namespace SDK
	{
		using namespace AIMP::SDK::PlayList;

		AimpPlayListGroup::AimpPlayListGroup()
		{
			IAIMPPlaylistGroup *group = (IAIMPPlaylistGroup*)ManagedAimpCore::QueryInterface(IID_IAIMPPlaylistGroup);
		}

		AimpPlayListGroup::AimpPlayListGroup(IAIMPPlaylistGroup *item) : AimpObject(item)
		{
		}

		System::String^ AimpPlayListGroup::Name::get()
		{
			return AimpConverter::GetString(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_NAME);
		}

		bool AimpPlayListGroup::Expanded::get()
		{
			return AimpConverter::GetBool(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_EXPANDED);
		}

		void AimpPlayListGroup::Expanded::set(bool value)
		{
			AimpConverter::SetBool(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_EXPANDED, value);
		}

		double AimpPlayListGroup::Duration::get()
		{
			return AimpConverter::GetFloat(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_DURATION);
		}

		void AimpPlayListGroup::Duration::set(double value)
		{
			AimpConverter::SetFloat(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_DURATION, value);
		}

		int AimpPlayListGroup::Index::get()
		{
			return AimpConverter::GetInt32(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_INDEX);
		}

		bool AimpPlayListGroup::Selected::get()
		{
			return AimpConverter::GetBool(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_SELECTED);
		}

		void AimpPlayListGroup::Selected::set(bool value)
		{
			AimpConverter::SetBool(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_SELECTED, value);
		}

		int AimpPlayListGroup::Count::get()
		{
			return InternalAimpObject->GetItemCount();
		}

		IAimpPlayListItem ^AimpPlayListGroup::GetItem(int index)
		{
			if (_item == nullptr)
			{
				IAIMPPlaylistItem *item;
				InternalAimpObject->GetItem(index, IID_IAIMPPlaylistItem, (void**)&item);
				_item = gcnew AimpPlayListItem(item);
			}

			return _item;
		}
	}
}