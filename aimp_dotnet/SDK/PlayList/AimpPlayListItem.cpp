#include "..\..\Stdafx.h"
#include "AimpPlayListItem.h"
#include "AimpPlayListGroup.h"
#include "AimpFileInfo.h"
#include "AimpPlayList.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;

        using namespace AIMP::SDK::PlayList;

        AimpPlayListItem::AimpPlayListItem()
        {
            _aimpObject = Converter::MakeObject<IAIMPPlaylistItem>(IID_IAIMPPlaylistItem);
        }

        AimpPlayListItem::AimpPlayListItem(IAimpPlayListItem ^item)
        {
            _aimpObject = Converter::MakeObject<IAIMPPlaylistItem>(IID_IAIMPPlaylistItem);
            this->FileName = item->FileName;
            this->Index = item->Index;
            this->Mark = item->Mark;
            this->PlaybackSwitch = item->PlaybackSwitch;
            this->Selected = item->Selected;
            this->PlayList = gcnew AimpPlayList(item->PlayList);
            //this->FileInfo = gcnew AimpFileInfo(item->FileInfo);
        }

        System::String^ AimpPlayListItem::DisplayText::get()
        {
            return Converter::GetString(_aimpObject, AIMP_PLAYLISTITEM_PROPID_DISPLAYTEXT);
        }

        void AimpPlayListItem::DisplayText::set(String^ value)
        {
            Converter::SetString(_aimpObject, AIMP_PLAYLISTITEM_PROPID_DISPLAYTEXT, value);
        }

        String^ AimpPlayListItem::FileName::get()
        {
            return Converter::GetString(_aimpObject, AIMP_PLAYLISTITEM_PROPID_FILENAME);
        }

        void AimpPlayListItem::FileName::set(String ^value)
        {
            Converter::SetString(_aimpObject, AIMP_PLAYLISTITEM_PROPID_FILENAME, value);
        }

        int AimpPlayListItem::Index::get()
        {
            return Converter::GetInt32(_aimpObject, AIMP_PLAYLISTITEM_PROPID_INDEX);
        }

        void AimpPlayListItem::Index::set(int value)
        {
            Converter::SetInt32(_aimpObject, AIMP_PLAYLISTITEM_PROPID_INDEX, value);
        }

        double AimpPlayListItem::Mark::get()
        {
            return Converter::GetFloat(_aimpObject, AIMP_PLAYLISTITEM_PROPID_MARK);
        }

        void AimpPlayListItem::Mark::set(double value)
        {
            Converter::SetFloat(_aimpObject, AIMP_PLAYLISTITEM_PROPID_MARK, value);
        }

        int AimpPlayListItem::PlaybackIndex::get()
        {
            return Converter::GetInt32(_aimpObject, AIMP_PLAYLISTITEM_PROPID_PLAYBACKQUEUEINDEX);
        }

        bool AimpPlayListItem::PlaybackSwitch::get()
        {
            return Converter::GetBool(_aimpObject, AIMP_PLAYLISTITEM_PROPID_PLAYINGSWITCH);
        }

        void AimpPlayListItem::PlaybackSwitch::set(bool value)
        {
            Converter::SetInt32(_aimpObject, AIMP_PLAYLISTITEM_PROPID_PLAYINGSWITCH, value ? 1 : 0);
        }

        bool AimpPlayListItem::Selected::get()
        {
            return Converter::GetBool(_aimpObject, AIMP_PLAYLISTITEM_PROPID_SELECTED);
        }

        void AimpPlayListItem::Selected::set(bool value)
        {
            Converter::SetInt32(_aimpObject, AIMP_PLAYLISTITEM_PROPID_SELECTED, value ? 1 : 0);
        }

        IAimpFileInfo^ AimpPlayListItem::FileInfo::get()
        {
            IAIMPFileInfo *fileInfo;
            if (CheckResult(_aimpObject->GetValueAsObject(AIMP_PLAYLISTITEM_PROPID_FILEINFO, IID_IAIMPFileInfo, (void**)&fileInfo)) != AimpActionResult::Ok)
            {
                return nullptr;
            }

            //ObjectHelper::GetObject(_aimpObject, AIMP_PLAYLISTITEM_PROPID_FILEINFO, AIMP36SDK::IID_IAIMPFileInfo, (void**) &fileInfo);
            return gcnew AimpFileInfo(fileInfo);
        }

        IAimpPlayListGroup^ AimpPlayListItem::Group::get()
        {
            if (_group == nullptr)
            {
                IAIMPPlaylistGroup *group;
                if (CheckResult(Converter::GetObject(_aimpObject, AIMP_PLAYLISTITEM_PROPID_GROUP, IID_IAIMPPlaylistGroup, (void**)&group)) != AimpActionResult::Ok)
                {
                    return nullptr;
                }

                _group = gcnew AimpPlayListGroup(group);
            }

            return _group;
        }

        IAimpPlayList^ AimpPlayListItem::PlayList::get()
        {
            IAIMPPlaylist *obj;
            if (CheckResult(_aimpObject->GetValueAsObject(AIMP_PLAYLISTITEM_PROPID_PLAYLIST, IID_IAIMPPlaylist, (void**)&obj)) != AimpActionResult::Ok)
            {
                return nullptr;
            }

            return gcnew AimpPlayList(obj);
        }

        void AimpPlayListItem::PlayList::set(IAimpPlayList^ val)
        {
            // TODO: complete it
        }

        AimpActionResult AimpPlayListItem::ReloadInfo()
        {
            return CheckResult(_aimpObject->ReloadInfo());
        }
    }
}