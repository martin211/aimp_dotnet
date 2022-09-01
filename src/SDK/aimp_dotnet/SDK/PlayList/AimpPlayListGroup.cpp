//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "SDK\ManagedAimpCore.h"
#include "AimpPlayListGroup.h"
#include "AimpPlayListItem.h"

using namespace Playlist;

AimpPlayListGroup::AimpPlayListGroup() {
}

AimpPlayListGroup::AimpPlayListGroup(IAIMPPlaylistGroup* item) : AimpObject(item) {
}

String^ AimpPlayListGroup::Name::get() {
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_NAME);
}

bool AimpPlayListGroup::Expanded::get() {
    return PropertyListExtension::GetBool(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_EXPANDED);
}

void AimpPlayListGroup::Expanded::set(bool value) {
    PropertyListExtension::SetBool(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_EXPANDED, value);
}

double AimpPlayListGroup::Duration::get() {
    return PropertyListExtension::GetFloat(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_DURATION);
}

int AimpPlayListGroup::Index::get() {
    return PropertyListExtension::GetInt32(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_INDEX);
}

bool AimpPlayListGroup::Selected::get() {
    return PropertyListExtension::GetBool(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_SELECTED);
}

void AimpPlayListGroup::Selected::set(bool value) {
    PropertyListExtension::SetBool(InternalAimpObject, AIMP_PLAYLISTGROUP_PROPID_SELECTED, value);
}

int AimpPlayListGroup::Count::get() {
    return InternalAimpObject->GetItemCount();
}

AimpActionResult<IAimpPlaylistItem^>^ AimpPlayListGroup::GetItem(int index) {
    ActionResultType result = ActionResultType::Fail;

    IAIMPPlaylistItem* item = nullptr;
    result = CheckResult(InternalAimpObject->GetItem(index, IID_IAIMPPlaylistItem, reinterpret_cast<void**>(&item)));
    auto plItem = gcnew AimpPlaylistItem(item);

    return gcnew AimpActionResult<IAimpPlaylistItem^>(result, plItem);
}
