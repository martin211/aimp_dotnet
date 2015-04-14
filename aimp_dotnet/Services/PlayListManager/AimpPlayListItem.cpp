#include "Stdafx.h"
#include "AimpPlayListItem.h"
#include "AimpPlayListGroup.h"
#include "..\..\ManagedAimpCore.h"

namespace AIMP
{
	namespace SDK
	{
		namespace PlayList
		{
			using namespace System;

			using namespace AIMP36SDK;
			using namespace AIMP::SDK::Services::PlayListManager;

			AimpPlayListItem::AimpPlayListItem()
			{
				_aimpObject = ObjectHelper::MakeObject<AIMP36SDK::IAIMPPlaylistItem>(AIMP::SDK360::IID_IAIMPPlaylistItem);
			}

			System::String^ AimpPlayListItem::DisplayText::get()
			{
				return ObjectHelper::GetString(_aimpObject, AIMP_PLAYLISTITEM_PROPID_DISPLAYTEXT);
			}

			void AimpPlayListItem::DisplayText::set(String^ value)
			{
				ObjectHelper::SetString(_aimpObject, AIMP_PLAYLISTITEM_PROPID_DISPLAYTEXT, value);
			}

			String^ AimpPlayListItem::FileName::get()
			{
				return ObjectHelper::GetString(_aimpObject, AIMP_PLAYLISTITEM_PROPID_FILENAME);
			}

			void AimpPlayListItem::FileName::set(String ^value)
			{
				ObjectHelper::SetString(_aimpObject, AIMP_PLAYLISTITEM_PROPID_FILENAME, value);
			}

			int AimpPlayListItem::Index::get()
			{
				return ObjectHelper::GetInt32(_aimpObject, AIMP_PLAYLISTITEM_PROPID_INDEX);
			}

			void AimpPlayListItem::Index::set(int value)
			{
				ObjectHelper::SetInt32(_aimpObject, AIMP_PLAYLISTITEM_PROPID_INDEX, value);
			}

			double AimpPlayListItem::Mark::get()
			{
				return ObjectHelper::GetFloat(_aimpObject, AIMP_PLAYLISTITEM_PROPID_MARK);
			}

			void AimpPlayListItem::Mark::set(double value)
			{
				ObjectHelper::SetFloat(_aimpObject, AIMP_PLAYLISTITEM_PROPID_MARK, value);
			}

			int AimpPlayListItem::PlaybackIndex::get()
			{
				return ObjectHelper::GetInt32(_aimpObject, AIMP_PLAYLISTITEM_PROPID_PLAYBACKQUEUEINDEX);
			}

			bool AimpPlayListItem::PlaybackSwitch::get()
			{
				return ObjectHelper::GetBool(_aimpObject, AIMP_PLAYLISTITEM_PROPID_PLAYINGSWITCH);
			}

			void AimpPlayListItem::PlaybackSwitch::set(bool value)
			{
				ObjectHelper::SetInt32(_aimpObject, AIMP_PLAYLISTITEM_PROPID_PLAYINGSWITCH, value ? 1 : 0);
			}

			bool AimpPlayListItem::Selected::get()
			{
				return ObjectHelper::GetBool(_aimpObject, AIMP_PLAYLISTITEM_PROPID_SELECTED);
			}

			void AimpPlayListItem::Selected::set(bool value)
			{
				ObjectHelper::SetInt32(_aimpObject, AIMP_PLAYLISTITEM_PROPID_SELECTED, value ? 1 : 0);
			}

			IAimpFileInfo^ AimpPlayListItem::FileInfo::get()
			{
				// TODO: complete it
				return nullptr;
			}

			IAimpPlayListGroup^ AimpPlayListItem::Group::get()
			{
				if (_group == nullptr)
				{
					IAIMPPlaylistGroup *group;
					ObjectHelper::GetObject(_aimpObject, AIMP_PLAYLISTITEM_PROPID_GROUP, IID_IAIMPPlaylistGroup, (void**) &group);
					_group = gcnew AimpPlayListGroup(group);
				}

				return _group;
			}

			IAimpPlayList^ AimpPlayListItem::PlayList::get()
			{
				// TODO: complete it
				return nullptr;
			}

			void AimpPlayListItem::PlayList::set(IAimpPlayList^ val)
			{
				// TODO: complete it
			}

			void AimpPlayListItem::ReloadInfo()
			{
				_aimpObject->ReloadInfo();
			}
		}
	}
}