// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpPlayList.h"
#include "AimpPlayListGroup.h"
#include "SDK\FileManager\AimpFileInfo.h"
#include "AimpPlayListItem.h"
#include "AimpPlaylistPreimage.h"
#include "AimpPlaylistPreimageFolders.h"

ActionResultType AimpPlayList::GetProperties(IAIMPPropertyList** properties) {
    IAIMPPropertyList* prop = nullptr;
    const auto result = CheckResult(
        InternalAimpObject->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop)));
    if (result != ActionResultType::OK) {
        ACTION_ERROR2(result, "Unable to get a Playlist properties.");
    }

    *properties = prop;
    return result;
}

AimpPlayList::AimpPlayList(IAIMPPlaylist* aimpPlayList) : AimpObject(aimpPlayList) {
}

AimpPlayList::AimpPlayList(IAIMPPlaylist* item, bool registerAtMemoryManager) : AimpObject(
    item, registerAtMemoryManager) {
}

AimpPlayList::AimpPlayList(IAimpPlaylist^ item) {
    _aimpObject = static_cast<IAIMPPlaylist*>(AimpConverter::MakeObject(IID_IAIMPPlaylist));
    Name = item->Name;
    ReadOnly = item->ReadOnly;
    FocusedItem = item->FocusedItem;
    FocusedGroup = item->FocusedGroup;
    //GrouppingOvveriden = item->GrouppingOvveriden;
    Grouping = item->Grouping;
    GroupingTemplate = item->GroupingTemplate;
    GroupingAutomerg = item->GroupingAutomerg;
    FormattingOverride = item->FormattingOverride;
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

String^ AimpPlayList::Id::get() {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK) {
            return PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_ID);
        }
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return String::Empty;
}

String^ AimpPlayList::Name::get() {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK) {
            return PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_NAME);
        }
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return String::Empty;
}

void AimpPlayList::Name::set(String^ value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK) {
            PropertyListExtension::SetString(properties, AIMP_PLAYLIST_PROPID_NAME, value);
        }
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}

bool AimpPlayList::ReadOnly::get() {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_READONLY);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::ReadOnly::set(bool value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK) {
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_READONLY, value);
        }
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}

IAimpPlaylistItem^ AimpPlayList::FocusedItem::get() {
    IAimpPlaylistItem^ item = nullptr;
    IAIMPPropertyList* properties = nullptr;

    try {
        IAIMPPlaylistItem* group = nullptr;
        GetProperties(&properties);
        PropertyListExtension::GetObject(properties, AIMP_PLAYLIST_PROPID_FOCUSED_OBJECT, IID_IAIMPPlaylistItem,
                                         reinterpret_cast<void**>(&group));
        if (group != nullptr) {
            item = gcnew AimpPlaylistItem(group);
        }
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return item;
}

void AimpPlayList::FocusedItem::set(IAimpPlaylistItem^ value) {
    const auto item = static_cast<AimpPlaylistItem^>(value);

    if (item->InternalAimpObject == nullptr) {
        NULL_REFERENCE()
    }

    IAIMPPropertyList* properties = nullptr;
    try {
        GetProperties(&properties);
        PropertyListExtension::SetObject(properties, AIMP_PLAYLIST_PROPID_FOCUSED_OBJECT, item->InternalAimpObject);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}

IAimpPlaylistGroup^ AimpPlayList::FocusedGroup::get() {
    IAimpPlaylistGroup^ item = nullptr;
    IAIMPPropertyList* properties = nullptr;

    try {
        IAIMPPlaylistGroup* group = nullptr;
        GetProperties(&properties);
        PropertyListExtension::GetObject(properties, AIMP_PLAYLIST_PROPID_FOCUSED_OBJECT, IID_IAIMPPlaylistGroup,
                                         reinterpret_cast<void**>(&group));
        if (group != nullptr) {
            item = gcnew AimpPlayListGroup(group);
        }
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return item;
}

void AimpPlayList::FocusedGroup::set(IAimpPlaylistGroup^ value) {
    const auto item = static_cast<AimpPlayListGroup^>(value);

    if (item->InternalAimpObject == nullptr) {
        NULL_REFERENCE()
    }

    IAIMPPropertyList* properties = nullptr;
    try {
        GetProperties(&properties);
        PropertyListExtension::SetObject(properties, AIMP_PLAYLIST_PROPID_FOCUSED_OBJECT, item->InternalAimpObject);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::GroupingOverridden::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_GROUPPING_OVERRIDEN);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::GroupingOverridden::set(bool value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK) {
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_GROUPPING_OVERRIDEN, value);
        }
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::Grouping::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_GROUPPING);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::Grouping::set(bool value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK) {
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_GROUPPING, value);
        }
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


String^ AimpPlayList::GroupingTemplate::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_GROUPPING_TEMPLATE);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return String::Empty;
}

void AimpPlayList::GroupingTemplate::set(String^ value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            PropertyListExtension::SetString(properties, AIMP_PLAYLIST_PROPID_GROUPPING_TEMPLATE, value);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::GroupingAutomerg::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_GROUPPING_AUTOMERGING);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::GroupingAutomerg::set(bool value) {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_GROUPPING_AUTOMERGING, value);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::FormattingOverride::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_FORMATING_OVERRIDEN);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::FormattingOverride::set(bool value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_FORMATING_OVERRIDEN, value);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


String^ AimpPlayList::FormattingLine1Template::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_FORMATING_LINE1_TEMPLATE);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return String::Empty;
}

void AimpPlayList::FormattingLine1Template::set(String^ value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            PropertyListExtension::SetString(properties, AIMP_PLAYLIST_PROPID_FORMATING_LINE1_TEMPLATE, value);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


String^ AimpPlayList::FormattingLine2Template::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_FORMATING_LINE2_TEMPLATE);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return String::Empty;
}

void AimpPlayList::FormattingLine2Template::set(String^ value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            PropertyListExtension::SetString(properties, AIMP_PLAYLIST_PROPID_FORMATING_LINE2_TEMPLATE, value);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::ViewOverride::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_OVERRIDEN);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::ViewOverride::set(bool value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_OVERRIDEN, value);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::ViewDuration::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_DURATION);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::ViewDuration::set(bool value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_DURATION, value);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::ViewExpandButtons::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_EXPAND_BUTTONS);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::ViewExpandButtons::set(bool value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_EXPAND_BUTTONS, value);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::ViewMarks::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_MARKS);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::ViewMarks::set(bool value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_MARKS, value);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::ViewNumbers::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_NUMBERS);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::ViewNumbers::set(bool value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_NUMBERS, value);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::ViewAbsoluteNumbers::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_NUMBERS_ABSOLUTE);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::ViewAbsoluteNumbers::set(bool value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_NUMBERS_ABSOLUTE, value);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::ViewSecondLine::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_SECOND_LINE);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::ViewSecondLine::set(bool value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_SECOND_LINE, value);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


bool AimpPlayList::ViewSwitches::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_SWITCHES);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return false;
}

void AimpPlayList::ViewSwitches::set(bool value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_SWITCHES, value);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


int AimpPlayList::FocusIndex::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetInt32(properties, AIMP_PLAYLIST_PROPID_FOCUSINDEX);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return 0;
}

void AimpPlayList::FocusIndex::set(int value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            PropertyListExtension::SetInt32(properties, AIMP_PLAYLIST_PROPID_FOCUSINDEX, value);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


int AimpPlayList::PlaybackCursor::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetInt32(properties, AIMP_PLAYLIST_PROPID_PLAYBACKCURSOR);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return 0;
}

void AimpPlayList::PlaybackCursor::set(int value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            PropertyListExtension::SetInt32(properties, AIMP_PLAYLIST_PROPID_PLAYBACKCURSOR, value);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


int AimpPlayList::PlayingIndex::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetInt32(properties, AIMP_PLAYLIST_PROPID_PLAYINGINDEX);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return 0;
}

void AimpPlayList::PlayingIndex::set(int value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            PropertyListExtension::SetInt32(properties, AIMP_PLAYLIST_PROPID_PLAYINGINDEX, value);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


double AimpPlayList::Duration::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            return PropertyListExtension::GetFloat(properties, AIMP_PLAYLIST_PROPID_DURATION);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return 0;
}


double AimpPlayList::Size::get() {
    IAIMPPropertyList* properties = nullptr;
    double size = 0;

    try {
        if (GetProperties(&properties) == ActionResultType::OK)
            PropertyListExtension::GetFloat(properties, AIMP_PLAYLIST_PROPID_SIZE, *&size);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }

    return size;
}

IAimpPlaylistPreimage^ AimpPlayList::PreImage::get() {
    IAIMPPropertyList* properties = nullptr;

    try {
        if (GetProperties(&properties) == ActionResultType::OK) {
            IAIMPPlaylistPreimage* preImage = nullptr;
            ActionResultType res = Utils::CheckResult(properties->GetValueAsObject(
                AIMP_PLAYLIST_PROPID_PREIMAGE, IID_IAIMPPlaylistPreimage, reinterpret_cast<void**>(&preImage)));
            if (res == ActionResultType::OK && preImage != nullptr) {
                IAIMPPlaylistPreimageFolders* preimageFolders = static_cast<IAIMPPlaylistPreimageFolders*>(preImage);
                if (preimageFolders != nullptr) {
                    return gcnew AimpPlaylistPreimageFolders(preimageFolders);
                }

                return gcnew AimpPlaylistPreimage(preImage);
            }
        }
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
    return nullptr;
}

void AimpPlayList::PreImage::set(IAimpPlaylistPreimage^ value) {
    IAIMPPropertyList* properties = nullptr;
    try {
        if (GetProperties(&properties) == ActionResultType::OK) {
            IAIMPPlaylistPreimage* preImage = nullptr;

            if (value != nullptr) {
                AimpPlaylistPreimageFolders^ folders = dynamic_cast<AimpPlaylistPreimageFolders^>(value);

                if (folders != nullptr) {
                    IAIMPPlaylistPreimageFolders* f = static_cast<IAIMPPlaylistPreimageFolders*>(folders->
                        InternalAimpObject);
                    ActionResultType res = Utils::CheckResult(
                        properties->SetValueAsObject(AIMP_PLAYLIST_PROPID_PREIMAGE, f));
                }
                else {
                    preImage = static_cast<AimpPlaylistPreimage^>(value)->InternalAimpObject;
                    ActionResultType res = Utils::CheckResult(
                        properties->SetValueAsObject(AIMP_PLAYLIST_PROPID_PREIMAGE, preImage));
                }
            }
            else {
                IAIMPPlaylistPreimage* preImage = nullptr;
                ActionResultType res = Utils::CheckResult(properties->GetValueAsObject(
                    AIMP_PLAYLIST_PROPID_PREIMAGE, IID_IAIMPPlaylistPreimage, reinterpret_cast<void**>(&preImage)));
                if (res == ActionResultType::OK && preImage != nullptr) {
                    preImage->Release();
                    preImage = nullptr;
                    properties->SetValueAsObject(AIMP_PLAYLIST_PROPID_PREIMAGE, static_cast<IUnknown*>(nullptr));
                }
            }
        }
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
            properties = nullptr;
        }
    }
}


ActionResult AimpPlayList::Add(IAimpFileInfo^ fileInfo, PlaylistFlags flags, PlaylistFilePosition filePosition) {
    AimpFileInfo^ file = CreateFileInfo(fileInfo);
    const auto result = CheckResult(
        InternalAimpObject->Add(file->InternalAimpObject, DWORD(flags), static_cast<int>(filePosition)));
    file->InternalAimpObject->Release();
    return ACTION_RESULT(result);
}

ActionResult AimpPlayList::Add(String^ fileUrl, PlaylistFlags flags, PlaylistFilePosition filePosition) {
    Assert::NotNull(fileUrl, "fileUri");

    IAIMPString* url = AimpConverter::ToAimpString(fileUrl);
    const auto res = CheckResult(InternalAimpObject->Add(url, DWORD(flags), static_cast<int>(filePosition)));
    url->Release();
    url = nullptr;
    return ACTION_RESULT(res);
}

ActionResult AimpPlayList::AddList(Generic::IList<IAimpFileInfo^>^ files, PlaylistFlags flags,
                                   PlaylistFilePosition filePosition) {
    ActionResultType res = ActionResultType::Fail;

    if (files->Count > 0) {
        IAIMPObjectList* list = nullptr;
        ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPObjectList, reinterpret_cast<void**>(&list));

        if (list != nullptr) {
            for (int i = 0; i < files->Count; i++) {
                AimpFileInfo^ file = CreateFileInfo(files[i]);
                list->Add(file->InternalAimpObject);
                file->InternalAimpObject->Release();
            }

            res = CheckResult(InternalAimpObject->AddList(list, DWORD(flags), static_cast<int>(filePosition)));

            list->Release();
            list = nullptr;
        }
    }

    return ACTION_RESULT(res);
}

ActionResult AimpPlayList::AddList(Generic::IList<String^>^ fileUrlList, PlaylistFlags flags,
                                   PlaylistFilePosition filePosition) {
    ActionResultType res = ActionResultType::Fail;
    IAIMPObjectList* list = nullptr;

    Assert::NotNull(fileUrlList, "fileUrlList");

    if (fileUrlList->Count > 0) {
        try {
            ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPObjectList, reinterpret_cast<void**>(&list));

            if (list != nullptr) {
                for (int i = 0; i < fileUrlList->Count; i++) {
                    IAIMPString* str = AimpConverter::ToAimpString(fileUrlList[i]);
                    list->Add(str);
                    str->Release();
                    str = nullptr;
                }

                res = CheckResult(InternalAimpObject->AddList(list, DWORD(flags), int(filePosition)));
            }
        }
        finally {
            if (list != nullptr) {
                list->Release();
                list = nullptr;
            }
        }
    }

    return ACTION_RESULT(res);
}

ActionResult AimpPlayList::Delete(IAimpPlaylistItem^ item) {
    return ACTION_RESULT(
        CheckResult(InternalAimpObject->Delete(static_cast<AimpPlaylistItem^>(item)->InternalAimpObject)));
}

ActionResult AimpPlayList::Delete(int index) {
    return ACTION_RESULT(CheckResult(InternalAimpObject->Delete2(index)));
}

ActionResult AimpPlayList::DeleteAll() {
    return ACTION_RESULT(CheckResult(InternalAimpObject->DeleteAll()));
}

ActionResult AimpPlayList::Delete(PlaylistDeleteFlags deleteFlags, Object^ customFilterData,
                                  Func<IAimpPlaylistItem^, Object^, bool>^ filterFunc) {
    void* customData = GCHandle::ToIntPtr(GCHandle::Alloc(customFilterData)).ToPointer();
    _deleteFilterFunc = filterFunc;
    _deleteCallback = gcnew OnDeleteCallback(this, &AimpPlayList::OnDeleteReceive);
    IntPtr functionHandle = Marshal::GetFunctionPointerForDelegate(_deleteCallback);
    return ACTION_RESULT(CheckResult(InternalAimpObject->Delete3(DWORD(deleteFlags),
        static_cast<TAIMPPlaylistDeleteProc(_stdcall*)>(functionHandle.
            ToPointer()), customData)));
}

ActionResult AimpPlayList::Sort(PlaylistSort sort) {
    return ACTION_RESULT(CheckResult(InternalAimpObject->Sort(static_cast<int>(sort))));
}

ActionResult AimpPlayList::Sort(Object^ customSortData,
                                Func<IAimpPlaylistItem^, IAimpPlaylistItem^, Object^, PlaylistSortComapreResult>^
                                compareFunc) {
    void* customData = GCHandle::ToIntPtr(GCHandle::Alloc(customSortData)).ToPointer();
    _compareFunc = compareFunc;
    _sortCallback = gcnew OnSortCallback(this, &AimpPlayList::OnSortReceive);
    IntPtr functionHandle = Marshal::GetFunctionPointerForDelegate(_sortCallback);
    return ACTION_RESULT(CheckResult(
        InternalAimpObject->Sort3(static_cast<TAIMPPlaylistCompareProc(_stdcall*)>(functionHandle.ToPointer()),
            customData)));
}

ActionResult AimpPlayList::Sort(String^ templateString) {
    IAIMPString* templateStr = AimpConverter::ToAimpString(templateString);
    const ActionResultType res = CheckResult(InternalAimpObject->Sort2(templateStr));
    templateStr->Release();
    templateStr = nullptr;
    return ACTION_RESULT(res);
}

ActionResult AimpPlayList::BeginUpdate() {
    return ACTION_RESULT(CheckResult(InternalAimpObject->BeginUpdate()));
}

ActionResult AimpPlayList::EndUpdate() {
    return ACTION_RESULT(CheckResult(InternalAimpObject->EndUpdate()));
}

ActionResult AimpPlayList::Close(PlaylistCloseFlag closeFlag) {
    if (_listner != nullptr) {
        InternalAimpObject->ListenerRemove(_listner);
        _listner->Release();
        _listner = nullptr;
    }

    const auto result = ACTION_RESULT(CheckResult(InternalAimpObject->Close(DWORD(closeFlag))));
    FreeResources();
    return result;
}

AimpActionResult<Generic::IList<String^>^>^ AimpPlayList::GetFiles(PlaylistGetFilesFlag filesFlag) {
    IAIMPObjectList* collection = nullptr;
    ActionResultType actionResult = ActionResultType::Fail;
    actionResult = CheckResult(InternalAimpObject->GetFiles(DWORD(filesFlag), &collection));
    auto files = gcnew List<String^>();

    if (actionResult == ActionResultType::OK) {
        const int count = collection->GetCount();

        for (int i = 0; i < count; i++) {
            IAIMPString* str = nullptr;
            if (collection->GetObject(i, IID_IAIMPString, reinterpret_cast<void**>(&str)) == S_OK) {
                files->Add(AimpConverter::ToManagedString(str));
                str->Release();
                str = nullptr;
            }
        }
    }

    return gcnew AimpActionResult<Generic::IList<String^>^>(actionResult, files);
}

ActionResult AimpPlayList::ReloadFromPreimage() {
    return ACTION_RESULT(CheckResult(InternalAimpObject->ReloadFromPreimage()));
}

ActionResult AimpPlayList::ReloadInfo(bool fullReload) {
    return ACTION_RESULT(CheckResult(InternalAimpObject->ReloadInfo(fullReload)));
}

AimpActionResult<IAimpPlaylistItem^>^ AimpPlayList::GetItem(int index) {
    IAimpPlaylistItem^ plItem = nullptr;
    IAIMPPlaylistItem* item = nullptr;
    const auto result = CheckResult(
        InternalAimpObject->GetItem(index, IID_IAIMPPlaylistItem, reinterpret_cast<void**>(&item)));

    if (result == ActionResultType::OK) {
        plItem = gcnew AimpPlaylistItem(item);
    }

    return gcnew AimpActionResult<IAimpPlaylistItem^>(result, plItem);
}

int AimpPlayList::GetItemCount() {
    return InternalAimpObject->GetItemCount();
}

ActionResult AimpPlayList::MergeGroup(IAimpPlaylistGroup^ playlistGroup) {
    return ACTION_RESULT(CheckResult(
        InternalAimpObject->MergeGroup(dynamic_cast<AimpPlayListGroup^>(playlistGroup)->InternalAimpObject)));
}

AimpActionResult<IAimpPlaylistGroup^>^ AimpPlayList::GetGroup(int index) {
    IAimpPlaylistGroup^ aimpGroup = nullptr;
    IAIMPPlaylistGroup* group = nullptr;
    auto result = ActionResultType::Fail;

    result = CheckResult(InternalAimpObject->GetGroup(index, IID_IAIMPPlaylistGroup, reinterpret_cast<void**>(&group)));

    if (result == ActionResultType::OK) {
        aimpGroup = gcnew AimpPlayListGroup(group);
    }

    return gcnew AimpActionResult<IAimpPlaylistGroup^>(result, aimpGroup);
}

int AimpPlayList::GetGroupCount() {
    return InternalAimpObject->GetGroupCount();
}

void AimpPlayList::RegisterListner() {
    if (_listner == nullptr) {
        _listner = new AimpPlaylistListener(this);
        InternalAimpObject->ListenerAdd(_listner);
        _listner->AddRef();
    }
}


void AimpPlayList::Activated::add(AimpPlayListHandler^ onEvent) {
    RegisterListner();
    if (_onActivated == nullptr) {
        _onActivated = static_cast<AimpPlayListHandler^>(Delegate::Combine(_onActivated, onEvent));
    }
}

void AimpPlayList::Activated::remove(AimpPlayListHandler^ onEvent) {
    if (_onActivated != nullptr) {
        _onActivated = static_cast<AimpPlayListHandler^>(Delegate::Remove(_onActivated, onEvent));
    }
}

void AimpPlayList::Activated::raise(IAimpPlaylist^ sender) {
    AimpPlayListHandler^ tmp = this->_onActivated;
    if (tmp != nullptr) {
        _onActivated(sender);
    }
}


void AimpPlayList::Removed::add(AimpPlayListHandler^ onEvent) {
    RegisterListner();
    if (_onRemoved != nullptr) {
        _onRemoved = static_cast<AimpPlayListHandler^>(Delegate::Combine(_onRemoved, onEvent));
    }
}

void AimpPlayList::Removed::remove(AimpPlayListHandler^ onEvent) {
    if (_onRemoved != nullptr) {
        _onRemoved = static_cast<AimpPlayListHandler^>(Delegate::Remove(_onRemoved, onEvent));
    }
}

void AimpPlayList::Removed::raise(IAimpPlaylist^ sender) {
    AimpPlayListHandler^ tmp = this->_onRemoved;
    if (tmp != nullptr) {
        _onRemoved(sender);
    }
}


void AimpPlayList::Changed::add(PlayListChangedHandler^ onEvent) {
    RegisterListner();
    if (_onChanged == nullptr) {
        _onChanged = static_cast<PlayListChangedHandler^>(Delegate::Combine(_onChanged, onEvent));
    }
}

void AimpPlayList::Changed::remove(PlayListChangedHandler^ onEvent) {
    if (_onChanged != nullptr) {
        _onChanged = static_cast<PlayListChangedHandler^>(Delegate::Remove(_onChanged, onEvent));
    }
}

void AimpPlayList::Changed::raise(IAimpPlaylist^ sender, PlaylistNotifyType notifyType) {
    PlayListChangedHandler^ tmp = this->_onChanged;
    if (tmp != nullptr) {
        _onChanged(sender, notifyType);
    }
}

AimpFileInfo^ AimpPlayList::CreateFileInfo(IAimpFileInfo^ fi) {
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

void AimpPlayList::ScanningBegin::add(AimpPlayListHandler^ onEvent) {
    if (this->_scanningBeginHandler == nullptr) {
        _scanningBeginHandler = static_cast<AimpPlayListHandler^>(Delegate::Combine(_scanningBeginHandler, onEvent));
    }
}

void AimpPlayList::ScanningBegin::remove(AimpPlayListHandler^ onEvent) {
    if (this->_scanningBeginHandler != nullptr) {
        _scanningBeginHandler = static_cast<AimpPlayListHandler^>(Delegate::Remove(_scanningBeginHandler, onEvent));
    }
}

void AimpPlayList::ScanningBegin::raise(IAimpPlaylist^ sender) {
    if (this->_scanningBeginHandler != nullptr) {
        _scanningBeginHandler(sender);
    }
}

void AimpPlayList::ScanningProgress::add(AimpPlayListHandler<ScanningProgressEventArgs^>^ onEvent) {
    if (this->_scanningProgressHandler == nullptr) {
        _scanningProgressHandler = static_cast<AimpPlayListHandler<ScanningProgressEventArgs^>^>(Delegate::Combine(
            _scanningProgressHandler, onEvent));
    }
}

void AimpPlayList::ScanningProgress::remove(AimpPlayListHandler<ScanningProgressEventArgs^>^ onEvent) {
    if (this->_scanningProgressHandler != nullptr) {
        _scanningProgressHandler = static_cast<AimpPlayListHandler<ScanningProgressEventArgs^>^>(Delegate::Remove(
            _scanningProgressHandler, onEvent));
    }
}

void AimpPlayList::ScanningProgress::raise(IAimpPlaylist^ sender, ScanningProgressEventArgs^ args) {
    if (this->_scanningProgressHandler != nullptr) {
        _scanningProgressHandler(sender, args);
    }
}

void AimpPlayList::ScanningEnd::add(AimpPlayListHandler<ScanningEndEventArgs^>^ onEvent) {
    if (this->_scanningEndHandler == nullptr) {
        _scanningEndHandler = static_cast<AimpPlayListHandler<ScanningEndEventArgs^>^>(Delegate::Combine(
            _scanningEndHandler, onEvent));
    }
}

void AimpPlayList::ScanningEnd::remove(AimpPlayListHandler<ScanningEndEventArgs^>^ onEvent) {
    if (this->_scanningEndHandler != nullptr) {
        _scanningEndHandler = static_cast<AimpPlayListHandler<ScanningEndEventArgs^>^>(Delegate::Remove(
            _scanningEndHandler, onEvent));
    }
}

void AimpPlayList::ScanningEnd::raise(IAimpPlaylist^ sender, ScanningEndEventArgs^ args) {
    if (this->_scanningEndHandler != nullptr) {
        _scanningEndHandler(sender, args);
    }
}

void AimpPlayList::OnChanged(DWORD flags) {
    this->Changed(this, PlaylistNotifyType(flags));
}

void AimpPlayList::OnActivated() {
    this->Activated(this);
}

void AimpPlayList::OnRemoved() {
    this->Removed(this);
}

void AimpPlayList::OnScanningBegin() {
    this->ScanningBegin(this);
}

void AimpPlayList::OnScanningProgress(const double progress) {
    this->ScanningProgress(this, gcnew ScanningProgressEventArgs(progress));
}

void AimpPlayList::OnScanningEnd(bool hasChanges, bool canceled) {
    this->ScanningEnd(this, gcnew ScanningEndEventArgs(hasChanges, canceled));
}

int AimpPlayList::OnSortReceive(IAIMPPlaylistItem* item1, IAIMPPlaylistItem* item2, void* userData) {
    GCHandle h = GCHandle::FromIntPtr(IntPtr(userData));
    Object^ customData = h.Target;
    h.Free();
    return int(_compareFunc(gcnew AimpPlaylistItem(item1), gcnew AimpPlaylistItem(item2), customData));
}

bool AimpPlayList::OnDeleteReceive(IAIMPPlaylistItem* item1, void* customFilterData) {
    GCHandle h = GCHandle::FromIntPtr(IntPtr(customFilterData));
    Object^ customData = h.Target;
    h.Free();
    return bool(_deleteFilterFunc(gcnew AimpPlaylistItem(item1), customData));
}

void AimpPlayList::FreeResources() {
    if (_internalPreImage != nullptr) {
        _internalPreImage->Release();
        delete _internalPreImage;
        _internalPreImage = nullptr;
    }

    if (_listner != nullptr) {
        _listner->Release();
        delete _listner;
        _listner = nullptr;
    }
}

#pragma region AimpPlaylistListener

AimpPlaylistListener::AimpPlaylistListener(gcroot<IPlayListListenerExecutor^> playList) {
    _playList = playList;
}

void WINAPI AimpPlaylistListener::Activated() {
    _playList->OnActivated();
}

void WINAPI AimpPlaylistListener::Changed(DWORD flags) {
    _playList->OnChanged(flags);
}

void WINAPI AimpPlaylistListener::Removed() {
    _playList->OnRemoved();
}

void WINAPI AimpPlaylistListener::ScanningBegin() {
    _playList->OnScanningBegin();
}

void WINAPI AimpPlaylistListener::ScanningProgress(const double Progress) {
    _playList->OnScanningProgress(Progress);
}

void WINAPI AimpPlaylistListener::ScanningEnd(BOOL HasChanges, BOOL Canceled) {
    _playList->OnScanningEnd(HasChanges, Canceled);
}

HRESULT WINAPI AimpPlaylistListener::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPPlaylistListener) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPPlaylistListener2) {
        *ppvObject = static_cast<IAIMPPlaylistListener2*>(this);
        AddRef();
        return S_OK;
    }

    ppvObject = nullptr;
    return res;
}

ULONG WINAPI AimpPlaylistListener::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI AimpPlaylistListener::Release(void) {
    return Base::Release();
}
#pragma endregion
