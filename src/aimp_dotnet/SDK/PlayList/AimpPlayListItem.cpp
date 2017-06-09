// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
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

namespace AIMP
{
    namespace SDK
    {
        using namespace System;

        using namespace AIMP::SDK::Playlist;

        AimpPlaylistItem::AimpPlaylistItem()
        {
            _aimpObject = (IAIMPPlaylistItem*)AimpConverter::MakeObject(IID_IAIMPPlaylistItem);
        }

        AimpPlaylistItem::~AimpPlaylistItem()
        {
            this->!AimpPlaylistItem();
        }

        AimpPlaylistItem::!AimpPlaylistItem()
        {
            _aimpObject->Release();
        }

        AimpPlaylistItem::AimpPlaylistItem(IAimpPlaylistItem ^item)
        {
            _aimpObject = (IAIMPPlaylistItem*)AimpConverter::MakeObject(IID_IAIMPPlaylistItem);
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
            return PropertyListExtension::GetString(_aimpObject, AIMP_PLAYLISTITEM_PROPID_DISPLAYTEXT);
        }

        void AimpPlaylistItem::DisplayText::set(String^ value)
        {
            PropertyListExtension::SetString(_aimpObject, AIMP_PLAYLISTITEM_PROPID_DISPLAYTEXT, value);
        }

        String^ AimpPlaylistItem::FileName::get()
        {
            return PropertyListExtension::GetString(_aimpObject, AIMP_PLAYLISTITEM_PROPID_FILENAME);
        }

        void AimpPlaylistItem::FileName::set(String ^value)
        {
            PropertyListExtension::SetString(_aimpObject, AIMP_PLAYLISTITEM_PROPID_FILENAME, value);
        }

        int AimpPlaylistItem::Index::get()
        {
            return PropertyListExtension::GetInt32(_aimpObject, AIMP_PLAYLISTITEM_PROPID_INDEX);
        }

        void AimpPlaylistItem::Index::set(int value)
        {
            PropertyListExtension::SetInt32(_aimpObject, AIMP_PLAYLISTITEM_PROPID_INDEX, value);
        }

        double AimpPlaylistItem::Mark::get()
        {
            return PropertyListExtension::GetFloat(_aimpObject, AIMP_PLAYLISTITEM_PROPID_MARK);
        }

        void AimpPlaylistItem::Mark::set(double value)
        {
            PropertyListExtension::SetFloat(_aimpObject, AIMP_PLAYLISTITEM_PROPID_MARK, value);
        }

        int AimpPlaylistItem::PlaybackIndex::get()
        {
            return PropertyListExtension::GetInt32(_aimpObject, AIMP_PLAYLISTITEM_PROPID_PLAYBACKQUEUEINDEX);
        }

        bool AimpPlaylistItem::PlaybackSwitch::get()
        {
            return PropertyListExtension::GetBool(_aimpObject, AIMP_PLAYLISTITEM_PROPID_PLAYINGSWITCH);
        }

        void AimpPlaylistItem::PlaybackSwitch::set(bool value)
        {
            PropertyListExtension::SetInt32(_aimpObject, AIMP_PLAYLISTITEM_PROPID_PLAYINGSWITCH, value ? 1 : 0);
        }

        bool AimpPlaylistItem::Selected::get()
        {
            return PropertyListExtension::GetBool(_aimpObject, AIMP_PLAYLISTITEM_PROPID_SELECTED);
        }

        void AimpPlaylistItem::Selected::set(bool value)
        {
            PropertyListExtension::SetInt32(_aimpObject, AIMP_PLAYLISTITEM_PROPID_SELECTED, value ? 1 : 0);
        }

        IAimpFileInfo^ AimpPlaylistItem::FileInfo::get()
        {
            IAIMPFileInfo *fileInfo;
            if (CheckResult(_aimpObject->GetValueAsObject(AIMP_PLAYLISTITEM_PROPID_FILEINFO, IID_IAIMPFileInfo, (void**)&fileInfo)) != AimpActionResult::Ok)
            {
                return nullptr;
            }

            //ObjectHelper::GetObject(_aimpObject, AIMP_PLAYLISTITEM_PROPID_FILEINFO, AIMP36SDK::IID_IAIMPFileInfo, (void**) &fileInfo);
            return gcnew AimpFileInfo(fileInfo);
        }

        IAimpPlaylistGroup^ AimpPlaylistItem::Group::get()
        {
            if (_group == nullptr)
            {
                IAIMPPlaylistGroup *group;
                if (PropertyListExtension::GetObject(_aimpObject, AIMP_PLAYLISTITEM_PROPID_GROUP, IID_IAIMPPlaylistGroup, (void**)&group) != AimpActionResult::Ok)
                {
                    return nullptr;
                }

                _group = gcnew AimpPlayListGroup(group);
            }

            return _group;
        }

        IAimpPlaylist^ AimpPlaylistItem::PlayList::get()
        {
            IAIMPPlaylist *obj;
            if (CheckResult(_aimpObject->GetValueAsObject(AIMP_PLAYLISTITEM_PROPID_PLAYLIST, IID_IAIMPPlaylist, (void**)&obj)) != AimpActionResult::Ok)
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
            return CheckResult(_aimpObject->ReloadInfo());
        }
    }
}
