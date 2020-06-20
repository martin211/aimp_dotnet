// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpLyrics.h"

using namespace AIMP::SDK;

AimpLyrics::AimpLyrics(IAIMPLyrics* lyrics) : AimpObject(lyrics)
{
}

ActionResultType AimpLyrics::Assign(IAimpLyrics^ source)
{
    //TODO Complete it
    return ActionResultType::Fail; // CheckResult(InternalAimpObject->Assign());
}

ActionResultType AimpLyrics::Clone(IAimpLyrics^% lyrics)
{
    IAIMPLyrics** target = nullptr;
    auto result = Utils::CheckResult(InternalAimpObject->Clone(target));

    if (result == ActionResultType::OK)
    {
        lyrics = gcnew AimpLyrics(*target);
    }

    return result;
}

ActionResultType AimpLyrics::Add(int timeStart, int timeFinish, String^ text)
{
    auto str = AimpConverter::ToAimpString(text);
    auto result = Utils::CheckResult(InternalAimpObject->Add(timeStart, timeFinish, str));
    str->Release();
    str = nullptr;

    return result;
}

ActionResultType AimpLyrics::Delete(int index)
{
    return Utils::CheckResult(InternalAimpObject->Delete(index));
}

ActionResultType AimpLyrics::Find(int time, int index, String^% text)
{
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;
    //auto  result = Utils::CheckResult(InternalAimpObject->Find(time, index, &str));

    if (result == ActionResultType::OK)
    {
        text = AimpConverter::ToManagedString(str);
    }

    return result;
}

ActionResultType AimpLyrics::Get(int index, int timeStart, int timeFinish, String^% text)
{
    return ActionResultType::Fail;
}

ActionResultType AimpLyrics::GetCount(int% value)
{
    return ActionResultType::Fail;
}

ActionResultType AimpLyrics::LoadFromFile(String^ virtualFileName)
{
    return ActionResultType::Fail;
}

ActionResultType AimpLyrics::LoadFromStream(IAimpStream^ stream, LyricsFormat format)
{
    return ActionResultType::Fail;
}

ActionResultType AimpLyrics::LoadFromString(String^ lyrics, LyricsFormat format)
{
    return ActionResultType::Fail;
}

ActionResultType AimpLyrics::SaveToFile(String^ fileUri)
{
    auto str = AimpConverter::ToAimpString(fileUri);
    auto result = Utils::CheckResult(InternalAimpObject->SaveToFile(str));
    str->Release();
    str = nullptr;
    return result;
}

ActionResultType AimpLyrics::SaveToStream(IAimpStream^ stream, LyricsFormat format)
{
    return ActionResultType::Fail;
}

ActionResultType AimpLyrics::SaveToString(String^% lyrics, LyricsFormat format)
{
    IAIMPString* str = AimpConverter::ToAimpString(lyrics);
    auto result = Utils::CheckResult(InternalAimpObject->SaveToString(&str, static_cast<int>(format)));
    str->Release();
    str = nullptr;
    return result;
}

String^ AimpLyrics::Text::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_LYRICS_PROPID_TEXT);
}

void AimpLyrics::Text::set(String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMP_LYRICS_PROPID_TEXT, value);
}

String^ AimpLyrics::Author::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_LYRICS_PROPID_LYRICIST);
}

void AimpLyrics::Author::set(String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMP_LYRICS_PROPID_LYRICIST, value);
}

String^ AimpLyrics::Title::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_LYRICS_PROPID_TITLE);
}

void AimpLyrics::Title::set(String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMP_LYRICS_PROPID_TITLE, value);
}

String^ AimpLyrics::Album::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_LYRICS_PROPID_ALBUM);
}

void AimpLyrics::Album::set(String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMP_LYRICS_PROPID_ALBUM, value);
}

String^ AimpLyrics::Creator::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_LYRICS_PROPID_CREATOR);
}

void AimpLyrics::Creator::set(String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMP_LYRICS_PROPID_CREATOR, value);
}

String^ AimpLyrics::Application::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_LYRICS_PROPID_APP);
}

void AimpLyrics::Application::set(String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMP_LYRICS_PROPID_APP, value);
}

String^ AimpLyrics::ApplicationVersion::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_LYRICS_PROPID_APPVER);
}

void AimpLyrics::ApplicationVersion::set(String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMP_LYRICS_PROPID_APPVER, value);
}

LyricsType AimpLyrics::Type::get()
{
    int val = 0;
    PropertyListExtension::GetInt32(InternalAimpObject, AIMP_LYRICS_PROPID_TYPE, val);
    return static_cast<LyricsType>(val);
}

void AimpLyrics::Type::set(LyricsType value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMP_LYRICS_PROPID_TYPE, static_cast<int>(value));
}

int AimpLyrics::Offset::get()
{
    return PropertyListExtension::GetInt32(InternalAimpObject, AIMP_LYRICS_PROPID_OFFSET);
}

void AimpLyrics::Offset::set(int value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMP_LYRICS_PROPID_TYPE, value);
}
