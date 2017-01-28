/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#include "Stdafx.h"
#include "..\ManagedAimpCore.h"
#include "AimpPlayListGroup.h"
#include "AimpPlayListItem.h"

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
            _item = nullptr;
        }

        System::String^ AimpPlayListGroup::Name::get()
        {
            return PropertyListExtension::GetString(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_NAME);
        }

        bool AimpPlayListGroup::Expanded::get()
        {
            return PropertyListExtension::GetBool(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_EXPANDED);
        }

        void AimpPlayListGroup::Expanded::set(bool value)
        {
            PropertyListExtension::SetBool(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_EXPANDED, value);
        }

        double AimpPlayListGroup::Duration::get()
        {
            return PropertyListExtension::GetFloat(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_DURATION);
        }

        void AimpPlayListGroup::Duration::set(double value)
        {
            PropertyListExtension::SetFloat(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_DURATION, value);
        }

        int AimpPlayListGroup::Index::get()
        {
            return PropertyListExtension::GetInt32(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_INDEX);
        }

        bool AimpPlayListGroup::Selected::get()
        {
            return PropertyListExtension::GetBool(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_SELECTED);
        }

        void AimpPlayListGroup::Selected::set(bool value)
        {
            PropertyListExtension::SetBool(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_SELECTED, value);
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
                item->Release();
                item = NULL;
            }

            return _item;
        }
    }
}
