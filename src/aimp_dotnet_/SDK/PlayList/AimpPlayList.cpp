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
#include "AimpPlayList.h"
#include "AimpPlayListGroup.h"
#include "SDK\FileManager\AimpFileInfo.h"
#include "AimpPlayListItem.h"
#include "AimpPlaylistPreimage.h"
#include "AimpPlaylistPreimageFolders.h"

AimpActionResult AimpPlayList::GetProperties(IAIMPPropertyList** properties)
{
    IAIMPPropertyList* prop = nullptr;
    AimpActionResult result = CheckResult(
        InternalAimpObject->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop)));
    *properties = prop;
    return result;
}

AimpPlayList::AimpPlayList(IAIMPPlaylist* aimpPlayList) : AimpObject(aimpPlayList)
{
}

AimpPlayList::AimpPlayList(IAimpPlaylist^ item)
{
    _aimpObject = static_cast<IAIMPPlaylist*>(AimpConverter::MakeObject(IID_IAIMPPlaylist));
    Name = item->Name;
    ReadOnly = item->ReadOnly;
    FocusedObject = item->FocusedObject;
    //GrouppingOvveriden = item->GrouppingOvveriden;
    Grouping = item->Grouping;
    GroupingTemplate = item->GroupingTemplate;
    GroupingAutomerg = item->GroupingAutomerg;
    FormatingOverride = item->FormatingOverride;
    FormattingLine1Template = item->FormattingLine1Template;
    FormattingLine2Template = item->FormattingLine2Template;
    ViewOverride = item->ViewOverride;
    ViewDuration = item->ViewDuration;
    ViewExpandButtons = item->ViewExpandButtons;
    ViewMarks = item->ViewMarks;
    ViewNumbers = item->ViewNumbers;
    ViewAbsoluteNumbers = item->ViewAbsoluteNumbers;
    ViewSecondLine = item->ViewSecondLine;
    ViewSwitches = item->ViewSwitches;
    FocusIndex = item->FocusIndex;
    PlaybackCursor = item->PlaybackCursor;
    PlayingIndex = item->PlayingIndex;
    PreImage = item->PreImage;
}

String^ AimpPlayList::Id::get()
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
        {
            return PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_ID);
        }
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return String::Empty;
}

String^ AimpPlayList::Name::get()
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
        {
            return PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_NAME);
        }
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return String::Empty;
}

void AimpPlayList::Name::set(String^ value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
        {
            PropertyListExtension::SetString(properties, AIMP_PLAYLIST_PROPID_NAME, value);
        }
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}

bool AimpPlayList::ReadOnly::get()
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_READONLY);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::ReadOnly::set(bool value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
        {
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_READONLY, value);
        }
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}

Object^ AimpPlayList::FocusedObject::get()
{
    // todo complete
    return nullptr;
}

void AimpPlayList::FocusedObject::set(Object^ value)
{
    // todo complete
}


bool AimpPlayList::GroupingOverridden::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_GROUPPING_OVERRIDEN);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::GroupingOverridden::set(bool value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
        {
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_GROUPPING_OVERRIDEN, value);
        }
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::Grouping::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_GROUPPING);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::Grouping::set(bool value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
        {
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_GROUPPING, value);
        }
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


String^ AimpPlayList::GroupingTemplate::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_GROUPPING_TEMPLATE);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return String::Empty;
}

void AimpPlayList::GroupingTemplate::set(String^ value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            PropertyListExtension::SetString(properties, AIMP_PLAYLIST_PROPID_GROUPPING_TEMPLATE, value);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::GroupingAutomerg::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_GROUPPING_AUTOMERGING);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::GroupingAutomerg::set(bool value)
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_GROUPPING_AUTOMERGING, value);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::FormatingOverride::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_FORMATING_OVERRIDEN);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::FormatingOverride::set(bool value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_FORMATING_OVERRIDEN, value);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


String^ AimpPlayList::FormattingLine1Template::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_FORMATING_LINE1_TEMPLATE);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return String::Empty;
}

void AimpPlayList::FormattingLine1Template::set(String^ value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            PropertyListExtension::SetString(properties, AIMP_PLAYLIST_PROPID_FORMATING_LINE1_TEMPLATE, value);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


String^ AimpPlayList::FormattingLine2Template::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_FORMATING_LINE2_TEMPLATE);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return String::Empty;
}

void AimpPlayList::FormattingLine2Template::set(String^ value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            PropertyListExtension::SetString(properties, AIMP_PLAYLIST_PROPID_FORMATING_LINE2_TEMPLATE, value);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::ViewOverride::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_OVERRIDEN);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::ViewOverride::set(bool value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_OVERRIDEN, value);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::ViewDuration::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_DURATION);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::ViewDuration::set(bool value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_DURATION, value);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::ViewExpandButtons::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_EXPAND_BUTTONS);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::ViewExpandButtons::set(bool value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_EXPAND_BUTTONS, value);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::ViewMarks::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_MARKS);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::ViewMarks::set(bool value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_MARKS, value);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::ViewNumbers::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_NUMBERS);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::ViewNumbers::set(bool value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_NUMBERS, value);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::ViewAbsoluteNumbers::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_NUMBERS_ABSOLUTE);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::ViewAbsoluteNumbers::set(bool value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_NUMBERS_ABSOLUTE, value);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::ViewSecondLine::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_SECOND_LINE);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::ViewSecondLine::set(bool value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_SECOND_LINE, value);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::ViewSwitches::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_SWITCHES);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::ViewSwitches::set(bool value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_SWITCHES, value);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


int AimpPlayList::FocusIndex::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetInt32(properties, AIMP_PLAYLIST_PROPID_FOCUSINDEX);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return 0;
}

void AimpPlayList::FocusIndex::set(int value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            PropertyListExtension::SetInt32(properties, AIMP_PLAYLIST_PROPID_FOCUSINDEX, value);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


int AimpPlayList::PlaybackCursor::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetInt32(properties, AIMP_PLAYLIST_PROPID_PLAYBACKCURSOR);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return 0;
}

void AimpPlayList::PlaybackCursor::set(int value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            PropertyListExtension::SetInt32(properties, AIMP_PLAYLIST_PROPID_PLAYBACKCURSOR, value);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


int AimpPlayList::PlayingIndex::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetInt32(properties, AIMP_PLAYLIST_PROPID_PLAYINGINDEX);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return 0;
}

void AimpPlayList::PlayingIndex::set(int value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            PropertyListExtension::SetInt32(properties, AIMP_PLAYLIST_PROPID_PLAYINGINDEX, value);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


double AimpPlayList::Duration::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            return PropertyListExtension::GetFloat(properties, AIMP_PLAYLIST_PROPID_DURATION);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return 0;
}


double AimpPlayList::Size::get()
{
    IAIMPPropertyList* properties = nullptr;
    double size = 0;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
            PropertyListExtension::GetFloat(properties, AIMP_PLAYLIST_PROPID_SIZE, *&size);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return size;
}

IAimpPlaylistPreimage^ AimpPlayList::PreImage::get()
{
    IAIMPPropertyList* properties = nullptr;

    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
        {
            IAIMPPlaylistPreimage* preImage = nullptr;
            AimpActionResult res = Utils::CheckResult(properties->GetValueAsObject(
                AIMP_PLAYLIST_PROPID_PREIMAGE, IID_IAIMPPlaylistPreimage, reinterpret_cast<void**>(&preImage)));
            if (res == AimpActionResult::OK && preImage != nullptr)
            {
                IAIMPPlaylistPreimageFolders* preimageFolders = static_cast<IAIMPPlaylistPreimageFolders*>(preImage);
                if (preimageFolders != nullptr)
                {
                    return gcnew AimpPlaylistPreimageFolders(preimageFolders);
                }

                return gcnew AimpPlaylistPreimage(preImage);
            }
        }
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
    return nullptr;
}

void AimpPlayList::PreImage::set(IAimpPlaylistPreimage^ value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
        {
            IAIMPPlaylistPreimage* preImage = nullptr;

            if (value != nullptr)
            {
                AimpPlaylistPreimageFolders^ folders = dynamic_cast<AimpPlaylistPreimageFolders^>(value);

                if (folders != nullptr)
                {
                    IAIMPPlaylistPreimageFolders* f = static_cast<IAIMPPlaylistPreimageFolders*>(folders->
                        InternalAimpObject);
                    AimpActionResult res = Utils::CheckResult(
                        properties->SetValueAsObject(AIMP_PLAYLIST_PROPID_PREIMAGE, f));
                }
                else
                {
                    preImage = static_cast<AimpPlaylistPreimage^>(value)->InternalAimpObject;
                    AimpActionResult res = Utils::CheckResult(
                        properties->SetValueAsObject(AIMP_PLAYLIST_PROPID_PREIMAGE, preImage));
                }
            }
            else
            {
                IAIMPPlaylistPreimage* preImage = nullptr;
                AimpActionResult res = Utils::CheckResult(properties->GetValueAsObject(
                    AIMP_PLAYLIST_PROPID_PREIMAGE, IID_IAIMPPlaylistPreimage, reinterpret_cast<void**>(&preImage)));
                if (res == AimpActionResult::OK && preImage != nullptr)
                {
                    preImage->Release();
                    preImage = nullptr;
                    properties->SetValueAsObject(AIMP_PLAYLIST_PROPID_PREIMAGE, static_cast<IUnknown*>(nullptr));
                }
            }
        }
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}


AimpActionResult AimpPlayList::Add(IAimpFileInfo^ fileInfo, PlaylistFlags flags, PlaylistFilePosition filePosition)
{
    AimpFileInfo^ file = CreateFileInfo(fileInfo);
    AimpActionResult result = CheckResult(
        InternalAimpObject->Add(file->InternalAimpObject, DWORD(flags), int(filePosition)));
    file->InternalAimpObject->Release();
    return result;
}

AimpActionResult AimpPlayList::Add(String^ fileUrl, PlaylistFlags flags, PlaylistFilePosition filePosition)
{
    IAIMPString* url = AimpConverter::ToAimpString(fileUrl);
    AimpActionResult res = CheckResult(InternalAimpObject->Add(url, DWORD(flags), int(filePosition)));
    url->Release();
    url = nullptr;
    return res;
}

AimpActionResult AimpPlayList::AddList(Generic::IList<IAimpFileInfo^>^ files, PlaylistFlags flags,
                                       PlaylistFilePosition filePosition)
{
    AimpActionResult res = AimpActionResult::Fail;

    if (files->Count > 0)
    {
        IAIMPObjectList* list = nullptr;
        ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPObjectList, reinterpret_cast<void**>(&list));

        if (list != nullptr)
        {
            for (int i = 0; i < files->Count; i++)
            {
                AimpFileInfo^ file = CreateFileInfo(files[i]);
                list->Add(file->InternalAimpObject);
                file->InternalAimpObject->Release();
            }

            res = CheckResult(InternalAimpObject->AddList(list, DWORD(flags), int(filePosition)));

            list->Release();
            list = nullptr;
        }
    }

    return res;
}

AimpActionResult AimpPlayList::AddList(Generic::IList<String^>^ fileUrlList, PlaylistFlags flags,
                                       PlaylistFilePosition filePosition)
{
    AimpActionResult res = AimpActionResult::Fail;
    IAIMPObjectList* list = nullptr;

    if (fileUrlList->Count > 0)
    {
        try
        {
            ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPObjectList, reinterpret_cast<void**>(&list));

            if (list != nullptr)
            {
                for (int i = 0; i < fileUrlList->Count; i++)
                {
                    IAIMPString* str = AimpConverter::ToAimpString(fileUrlList[i]);
                    list->Add(str);
                    str->Release();
                    str = nullptr;
                }

                res = CheckResult(InternalAimpObject->AddList(list, DWORD(flags), int(filePosition)));
            }
        }
        finally
        {
            if (list != nullptr)
            {
                list->Release();
                list = nullptr;
            }
        }
    }

    return res;
}

AimpActionResult AimpPlayList::Delete(IAimpPlaylistItem^ item)
{
    return CheckResult(InternalAimpObject->Delete(static_cast<AimpPlaylistItem^>(item)->InternalAimpObject));
}

AimpActionResult AimpPlayList::Delete(int index)
{
    return CheckResult(InternalAimpObject->Delete2(index));
}

AimpActionResult AimpPlayList::DeleteAll()
{
    return CheckResult(InternalAimpObject->DeleteAll());
}

AimpActionResult AimpPlayList::Delete(PlaylistDeleteFlags deleteFlags, Object^ customFilterData,
                                      Func<IAimpPlaylistItem^, Object^, bool>^ filterFunc)
{
    void* customData = GCHandle::ToIntPtr(GCHandle::Alloc(customFilterData)).ToPointer();
    _deleteFilterFunc = filterFunc;
    _deleteCallback = gcnew OnDeleteCallback(this, &AimpPlayList::OnDeleteReceive);
    IntPtr functionHandle = Marshal::GetFunctionPointerForDelegate(_deleteCallback);
    return CheckResult(InternalAimpObject->Delete3(DWORD(deleteFlags),
                                                   static_cast<TAIMPPlaylistDeleteProc(_stdcall*)>(functionHandle.
                                                       ToPointer()), customData));
}

AimpActionResult AimpPlayList::Sort(PlaylistSort sort)
{
    return CheckResult(InternalAimpObject->Sort(int(sort)));
}

AimpActionResult AimpPlayList::Sort(Object^ customSortData,
                                    Func<IAimpPlaylistItem^, IAimpPlaylistItem^, Object^, PlaylistSortComapreResult>^
                                    compareFunc)
{
    void* customData = GCHandle::ToIntPtr(GCHandle::Alloc(customSortData)).ToPointer();
    _compareFunc = compareFunc;
    _sortCallback = gcnew OnSortCallback(this, &AimpPlayList::OnSortReceive);
    IntPtr functionHandle = Marshal::GetFunctionPointerForDelegate(_sortCallback);
    return CheckResult(
        InternalAimpObject->Sort3(static_cast<TAIMPPlaylistCompareProc(_stdcall*)>(functionHandle.ToPointer()),
                                  customData));
}

AimpActionResult AimpPlayList::Sort(String^ templateString)
{
    IAIMPString* templateStr = AimpConverter::ToAimpString(templateString);
    const AimpActionResult res = CheckResult(InternalAimpObject->Sort2(templateStr));
    templateStr->Release();
    templateStr = nullptr;
    return res;
}

AimpActionResult AimpPlayList::BeginUpdate()
{
    return CheckResult(InternalAimpObject->BeginUpdate());
}

AimpActionResult AimpPlayList::EndUpdate()
{
    return CheckResult(InternalAimpObject->EndUpdate());
}

AimpActionResult AimpPlayList::Close(PlaylistCloseFlag closeFlag)
{
    if (_listner != nullptr)
    {
        InternalAimpObject->ListenerRemove(_listner);
        _listner->Release();
        _listner = nullptr;
    }

    return CheckResult(InternalAimpObject->Close(DWORD(closeFlag)));
}

AimpActionResult AimpPlayList::GetFiles(PlaylistGetFilesFlag filesFlag, Generic::IList<String^>^% files)
{
    IAIMPObjectList* collection = nullptr;
    AimpActionResult actionResult = AimpActionResult::Fail;
    actionResult = CheckResult(InternalAimpObject->GetFiles(DWORD(filesFlag), &collection));
    files = nullptr;

    if (actionResult == AimpActionResult::OK)
    {
        files = gcnew List<String^>();

        const int count = collection->GetCount();

        for (int i = 0; i < count; i++)
        {
            IAIMPString* str = nullptr;
            if (collection->GetObject(i, IID_IAIMPString, reinterpret_cast<void**>(&str)) == S_OK)
            {
                files->Add(AimpConverter::ToManagedString(str));
                str->Release();
                str = nullptr;
            }
        }
    }

    return actionResult;
}

AimpActionResult AimpPlayList::ReloadFromPreimage()
{
    return CheckResult(InternalAimpObject->ReloadFromPreimage());
}

AimpActionResult AimpPlayList::ReloadInfo(bool fullReload)
{
    return CheckResult(InternalAimpObject->ReloadInfo(fullReload));
}

IAimpPlaylistItem^ AimpPlayList::GetItem(int index)
{
    IAimpPlaylistItem^ result = nullptr;
    IAIMPPlaylistItem* item = nullptr;

    if (InternalAimpObject->GetItem(index, IID_IAIMPPlaylistItem, reinterpret_cast<void**>(&item)) == S_OK)
    {
        result = gcnew AimpPlaylistItem(item);
    }

    return result;
}

int AimpPlayList::GetItemCount()
{
    return InternalAimpObject->GetItemCount();
}

AimpActionResult AimpPlayList::MergeGroup(IAimpPlaylistGroup^ playlistGroup)
{
    return CheckResult(
        InternalAimpObject->MergeGroup(dynamic_cast<AimpPlayListGroup^>(playlistGroup)->InternalAimpObject));
}

IAimpPlaylistGroup^ AimpPlayList::GetGroup(int index)
{
    IAimpPlaylistGroup^ result = nullptr;
    IAIMPPlaylistGroup* group = nullptr;

    try
    {
        if (CheckResult(InternalAimpObject->GetGroup(index, IID_IAIMPPlaylistGroup, reinterpret_cast<void**>(&group)))
            == AimpActionResult::OK)
        {
            result = gcnew AimpPlayListGroup(group);
        }

        return nullptr;
    }
    finally
    {
        if (group != nullptr)
        {
            group->Release();
            group = nullptr;
        }
    }

    return result;
}

int AimpPlayList::GetGroupCount()
{
    return InternalAimpObject->GetGroupCount();
}

void AimpPlayList::RegisterListner()
{
    if (_listner == nullptr)
    {
        _listner = new AimpPlaylistListener(this);
        InternalAimpObject->ListenerAdd(_listner);
        _listner->AddRef();
    }
}


void AimpPlayList::Activated::add(AimpPlayListHandler^ onEvent)
{
    RegisterListner();
    if (_onActivated == nullptr)
    {
        _onActivated = static_cast<AimpPlayListHandler^>(Delegate::Combine(_onActivated, onEvent));
    }
}

void AimpPlayList::Activated::remove(AimpPlayListHandler^ onEvent)
{
    if (_onActivated != nullptr)
    {
        _onActivated = static_cast<AimpPlayListHandler^>(Delegate::Remove(_onActivated, onEvent));
    }
}

void AimpPlayList::Activated::raise(IAimpPlaylist^ sender)
{
    AimpPlayListHandler^ tmp = this->_onActivated;
    if (tmp != nullptr)
    {
        _onActivated(sender);
    }
}


void AimpPlayList::Removed::add(AimpPlayListHandler^ onEvent)
{
    RegisterListner();
    if (_onRemoved != nullptr)
    {
        _onRemoved = static_cast<AimpPlayListHandler^>(Delegate::Combine(_onRemoved, onEvent));
    }
}

void AimpPlayList::Removed::remove(AimpPlayListHandler^ onEvent)
{
    if (_onRemoved != nullptr)
    {
        _onRemoved = static_cast<AimpPlayListHandler^>(Delegate::Remove(_onRemoved, onEvent));
    }
}

void AimpPlayList::Removed::raise(IAimpPlaylist^ sender)
{
    AimpPlayListHandler^ tmp = this->_onRemoved;
    if (tmp != nullptr)
    {
        _onRemoved(sender);
    }
}


void AimpPlayList::Changed::add(PlayListChangedHandler^ onEvent)
{
    RegisterListner();
    if (_onChanged == nullptr)
    {
        _onChanged = static_cast<PlayListChangedHandler^>(Delegate::Combine(_onChanged, onEvent));
    }
}

void AimpPlayList::Changed::remove(PlayListChangedHandler^ onEvent)
{
    if (_onChanged != nullptr)
    {
        _onChanged = static_cast<PlayListChangedHandler^>(Delegate::Remove(_onChanged, onEvent));
    }
}

void AimpPlayList::Changed::raise(IAimpPlaylist^ sender, PlaylistNotifyType notifyType)
{
    PlayListChangedHandler^ tmp = this->_onChanged;
    if (tmp != nullptr)
    {
        _onChanged(sender, notifyType);
    }
}

AimpFileInfo^ AimpPlayList::CreateFileInfo(IAimpFileInfo^ fi)
{
    AimpFileInfo^ result = gcnew AimpFileInfo();

    result->Album = fi->Album;
    result->AlbumArt = fi->AlbumArt;
    result->AlbumArtist = fi->AlbumArtist;
    result->Artist = fi->Artist;
    result->BitDepth = fi->BitDepth;
    result->BitRate = fi->BitRate;
    result->BPM = fi->BPM;
    result->Channels = fi->Channels;
    result->Codec = fi->Codec;
    result->Comment = fi->Comment;
    result->Composer = fi->Composer;
    result->CopyRight = fi->CopyRight;
    result->CUESheet = fi->CUESheet;
    result->CustomData = fi->CustomData;
    result->Date = fi->Date;
    result->DiskNumber = fi->DiskNumber;
    result->DiskTotal = fi->DiskTotal;
    result->Duration = fi->Duration;
    result->FileName = fi->FileName;
    result->FileSize = fi->FileSize;
    result->Gain = fi->Gain;
    result->Genre = fi->Genre;
    //result->LastPlayedDate = fi->LastPlayedDate;
    result->Lyrics = fi->Lyrics;
    result->Mark = fi->Mark;
    result->Peak = fi->Peak;
    //result->PlayCount = fi->PlayCount;
    result->Publisher = fi->Publisher;
    result->SampleRate = fi->SampleRate;
    result->SampleRate = fi->StateRating;
    result->StatMark = fi->StatMark;
    result->Title = fi->Title;
    result->TrackGain = fi->TrackGain;
    result->TrackNumber = fi->TrackNumber;
    result->TrackPeak = fi->TrackPeak;
    result->TrackTotal = fi->TrackTotal;

    return result;
}

void AimpPlayList::ScanningBegin::add(AimpPlayListHandler^ onEvent)
{
    if (this->_scanningBeginHandler == nullptr)
    {
        _scanningBeginHandler = static_cast<AimpPlayListHandler^>(Delegate::Combine(_scanningBeginHandler, onEvent));
    }
}

void AimpPlayList::ScanningBegin::remove(AimpPlayListHandler^ onEvent)
{
    if (this->_scanningBeginHandler != nullptr)
    {
        _scanningBeginHandler = static_cast<AimpPlayListHandler^>(Delegate::Remove(_scanningBeginHandler, onEvent));
    }
}

void AimpPlayList::ScanningBegin::raise(IAimpPlaylist^ sender)
{
    if (this->_scanningBeginHandler != nullptr)
    {
        _scanningBeginHandler(sender);
    }
}

void AimpPlayList::ScanningProgress::add(AimpPlayListHandler<ScanningProgressEventArgs^>^ onEvent)
{
    if (this->_scanningProgressHandler == nullptr)
    {
        _scanningProgressHandler = static_cast<AimpPlayListHandler<ScanningProgressEventArgs^>^>(Delegate::Combine(
            _scanningProgressHandler, onEvent));
    }
}

void AimpPlayList::ScanningProgress::remove(AimpPlayListHandler<ScanningProgressEventArgs^>^ onEvent)
{
    if (this->_scanningProgressHandler != nullptr)
    {
        _scanningProgressHandler = static_cast<AimpPlayListHandler<ScanningProgressEventArgs^>^>(Delegate::Remove(
            _scanningProgressHandler, onEvent));
    }
}

void AimpPlayList::ScanningProgress::raise(IAimpPlaylist^ sender, ScanningProgressEventArgs^ args)
{
    if (this->_scanningProgressHandler != nullptr)
    {
        _scanningProgressHandler(sender, args);
    }
}

void AimpPlayList::ScanningEnd::add(AimpPlayListHandler<ScanningEndEventArgs^>^ onEvent)
{
    if (this->_scanningEndHandler == nullptr)
    {
        _scanningEndHandler = static_cast<AimpPlayListHandler<ScanningEndEventArgs^>^>(Delegate::Combine(
            _scanningEndHandler, onEvent));
    }
}

void AimpPlayList::ScanningEnd::remove(AimpPlayListHandler<ScanningEndEventArgs^>^ onEvent)
{
    if (this->_scanningEndHandler != nullptr)
    {
        _scanningEndHandler = static_cast<AimpPlayListHandler<ScanningEndEventArgs^>^>(Delegate::Remove(
            _scanningEndHandler, onEvent));
    }
}

void AimpPlayList::ScanningEnd::raise(IAimpPlaylist^ sender, ScanningEndEventArgs^ args)
{
    if (this->_scanningEndHandler != nullptr)
    {
        _scanningEndHandler(sender, args);
    }
}

void AimpPlayList::OnChanged(DWORD flags)
{
    this->Changed(this, PlaylistNotifyType(flags));
}

void AimpPlayList::OnActivated()
{
    this->Activated(this);
}

void AimpPlayList::OnRemoved()
{
    this->Removed(this);
}

void AimpPlayList::OnScanningBegin()
{
    this->ScanningBegin(this);
}

void AimpPlayList::OnScanningProgress(const double progress)
{
    this->ScanningProgress(this, gcnew ScanningProgressEventArgs(progress));
}

void AimpPlayList::OnScanningEnd(bool hasChanges, bool canceled)
{
    this->ScanningEnd(this, gcnew ScanningEndEventArgs(hasChanges, canceled));
}

int AimpPlayList::OnSortReceive(IAIMPPlaylistItem* item1, IAIMPPlaylistItem* item2, void* userData)
{
    GCHandle h = GCHandle::FromIntPtr(IntPtr(userData));
    Object^ customData = h.Target;
    h.Free();
    return int(_compareFunc(gcnew AimpPlaylistItem(item1), gcnew AimpPlaylistItem(item2), customData));
}

bool AimpPlayList::OnDeleteReceive(IAIMPPlaylistItem* item1, void* customFilterData)
{
    GCHandle h = GCHandle::FromIntPtr(IntPtr(customFilterData));
    Object^ customData = h.Target;
    h.Free();
    return bool(_deleteFilterFunc(gcnew AimpPlaylistItem(item1), customData));
}

void AimpPlayList::FreeResources()
{
    if (_internalPreImage != nullptr)
    {
        _internalPreImage->Release();
        delete _internalPreImage;
        _internalPreImage = nullptr;
    }

    if (_listner != nullptr)
    {
        _listner->Release();
        delete _listner;
        _listner = nullptr;
    }
}

#pragma region AimpPlaylistListener

AimpPlaylistListener::AimpPlaylistListener(gcroot<IPlayListListnerExecutor^> playList)
{
    _playList = playList;
}

void WINAPI AimpPlaylistListener::Activated()
{
    _playList->OnActivated();
}

void WINAPI AimpPlaylistListener::Changed(DWORD flags)
{
    _playList->OnChanged(flags);
}

void WINAPI AimpPlaylistListener::Removed()
{
    _playList->OnRemoved();
}

void WINAPI AimpPlaylistListener::ScanningBegin()
{
    _playList->OnScanningBegin();
}

void WINAPI AimpPlaylistListener::ScanningProgress(const double Progress)
{
    _playList->OnScanningProgress(Progress);
}

void WINAPI AimpPlaylistListener::ScanningEnd(BOOL HasChanges, BOOL Canceled)
{
    _playList->OnScanningEnd(HasChanges, Canceled);
}

HRESULT WINAPI AimpPlaylistListener::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPPlaylistListener)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPPlaylistListener2)
    {
        *ppvObject = static_cast<IAIMPPlaylistListener2*>(this);
        AddRef();
        return S_OK;
    }

    ppvObject = nullptr;
    return res;
}

ULONG WINAPI AimpPlaylistListener::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI AimpPlaylistListener::Release(void)
{
    return Base::Release();
}
#pragma endregion
