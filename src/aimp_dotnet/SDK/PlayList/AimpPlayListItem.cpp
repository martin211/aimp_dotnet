// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpPlayListItem.h"
#include "AimpPlayListGroup.h"
#include "SDK\FileManager\AimpFileInfo.h"
#include "AimpPlayList.h"

using namespace System;
using namespace Playlist;

AimpPlaylistItem::AimpPlaylistItem()
{
    _aimpObject = static_cast<IAIMPPlaylistItem*>(AimpConverter::MakeObject(IID_IAIMPPlaylistItem));
}

AimpPlaylistItem::~AimpPlaylistItem()
{
    this->!AimpPlaylistItem();
}

AimpPlaylistItem::!AimpPlaylistItem()
{
    InternalAimpObject->Release();
}

AimpPlaylistItem::AimpPlaylistItem(IAimpPlaylistItem^ item)
{
    _aimpObject = static_cast<IAIMPPlaylistItem*>(AimpConverter::MakeObject(IID_IAIMPPlaylistItem));
    this->FileName = item->FileName;
    this->Index = item->Index;
    this->Mark = item->Mark;
    this->PlaybackSwitch = item->PlaybackSwitch;
    this->Selected = item->Selected;
    this->PlayList = gcnew AimpPlayList(item->PlayList);
    // todo
    //this->FileInfo = gcnew AimpFileInfo(item->FileInfo);
}

System::String^ AimpPlaylistItem::DisplayText::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_PLAYLISTITEM_PROPID_DISPLAYTEXT);
}

void AimpPlaylistItem::DisplayText::set(String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMP_PLAYLISTITEM_PROPID_DISPLAYTEXT, value);
}

String^ AimpPlaylistItem::FileName::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_PLAYLISTITEM_PROPID_FILENAME);
}

void AimpPlaylistItem::FileName::set(String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMP_PLAYLISTITEM_PROPID_FILENAME, value);
}

int AimpPlaylistItem::Index::get()
{
    return PropertyListExtension::GetInt32(InternalAimpObject, AIMP_PLAYLISTITEM_PROPID_INDEX);
}

void AimpPlaylistItem::Index::set(int value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMP_PLAYLISTITEM_PROPID_INDEX, value);
}

double AimpPlaylistItem::Mark::get()
{
    return PropertyListExtension::GetFloat(InternalAimpObject, AIMP_PLAYLISTITEM_PROPID_MARK);
}

void AimpPlaylistItem::Mark::set(double value)
{
    PropertyListExtension::SetFloat(InternalAimpObject, AIMP_PLAYLISTITEM_PROPID_MARK, value);
}

int AimpPlaylistItem::PlaybackIndex::get()
{
    return PropertyListExtension::GetInt32(InternalAimpObject, AIMP_PLAYLISTITEM_PROPID_PLAYBACKQUEUEINDEX);
}

bool AimpPlaylistItem::PlaybackSwitch::get()
{
    return PropertyListExtension::GetBool(InternalAimpObject, AIMP_PLAYLISTITEM_PROPID_PLAYINGSWITCH);
}

void AimpPlaylistItem::PlaybackSwitch::set(bool value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMP_PLAYLISTITEM_PROPID_PLAYINGSWITCH, value ? 1 : 0);
}

bool AimpPlaylistItem::Selected::get()
{
    return PropertyListExtension::GetBool(InternalAimpObject, AIMP_PLAYLISTITEM_PROPID_SELECTED);
}

void AimpPlaylistItem::Selected::set(bool value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMP_PLAYLISTITEM_PROPID_SELECTED, value ? 1 : 0);
}

IAimpFileInfo^ AimpPlaylistItem::FileInfo::get()
{
    IAIMPFileInfo* fileInfo;
    if (CheckResult(InternalAimpObject->GetValueAsObject(AIMP_PLAYLISTITEM_PROPID_FILEINFO, IID_IAIMPFileInfo,
                                                  reinterpret_cast<void**>(&fileInfo))) != AimpActionResult::OK)
    {
        return nullptr;
    }

    //ObjectHelper::GetObject(InternalAimpObject, AIMP_PLAYLISTITEM_PROPID_FILEINFO, AIMP36SDK::IID_IAIMPFileInfo, (void**) &fileInfo);
    return gcnew AimpFileInfo(fileInfo);
}

IAimpPlaylistGroup^ AimpPlaylistItem::Group::get()
{
    if (_group == nullptr)
    {
        IAIMPPlaylistGroup* group;
        if (PropertyListExtension::GetObject(InternalAimpObject, AIMP_PLAYLISTITEM_PROPID_GROUP, IID_IAIMPPlaylistGroup,
                                             reinterpret_cast<void**>(&group)) != AimpActionResult::OK)
        {
            return nullptr;
        }

        _group = gcnew AimpPlayListGroup(group);
    }

    return _group;
}

IAimpPlaylist^ AimpPlaylistItem::PlayList::get()
{
    IAIMPPlaylist* obj;
    if (CheckResult(InternalAimpObject->GetValueAsObject(AIMP_PLAYLISTITEM_PROPID_PLAYLIST, IID_IAIMPPlaylist,
                                                  reinterpret_cast<void**>(&obj))) != AimpActionResult::OK)
    {
        return nullptr;
    }

    return gcnew AimpPlayList(obj);
}

void AimpPlaylistItem::PlayList::set(IAimpPlaylist^ val)
{
    // TODO: complete it
}

AimpActionResult AimpPlaylistItem::ReloadInfo()
{
    return CheckResult(InternalAimpObject->ReloadInfo());
}
