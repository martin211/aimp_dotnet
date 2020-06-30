// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpLyrics.h"

using namespace AIMP::SDK;

void AimpLyrics::RegisterAtMemoryManager()
{
}

void AimpLyrics::ReleaseFromMemoryManager()
{
}

AimpLyrics::AimpLyrics(IAIMPLyrics* lyrics) : AimpObject(lyrics)
{
}

VoidResult AimpLyrics::Assign(IAimpLyrics^ source)
{
    //TODO Complete it
    return ACTION_RESULT(ActionResultType::NotImplemented); // CheckResult(InternalAimpObject->Assign());
}

AimpActionResult<IAimpLyrics^>^ AimpLyrics::Clone()
{
    IAIMPLyrics** target = nullptr;
    IAimpLyrics^ lyrics = nullptr;
    const auto result = Utils::CheckResult(InternalAimpObject->Clone(target));

    if (result == ActionResultType::OK)
    {
        lyrics = gcnew AimpLyrics(*target);
    }

    return gcnew AimpActionResult<IAimpLyrics^>(result, lyrics);
}

VoidResult AimpLyrics::Add(int timeStart, int timeFinish, String^ text)
{
    auto str = AimpConverter::ToAimpString(text);
    const auto result = Utils::CheckResult(InternalAimpObject->Add(timeStart, timeFinish, str));
    str->Release();
    str = nullptr;

    return ACTION_RESULT(result);
}

VoidResult AimpLyrics::Delete(int index)
{
    return ACTION_RESULT(Utils::CheckResult(InternalAimpObject->Delete(index)));
}

AimpActionResult<String^>^ AimpLyrics::Find(int time, int index)
{
    IAIMPString* str = nullptr;
    String^ text = "";
    const auto result = Utils::CheckResult(InternalAimpObject->Find(time, &index, &str));

    if (result == ActionResultType::OK)
    {
        text = AimpConverter::ToManagedString(str);
        str->Release();
        str = nullptr;
    }

    return gcnew AimpActionResult<String^>(result, text);
}

AimpActionResult<String^>^ AimpLyrics::Get(int index, int timeStart, int timeFinish)
{
    IAIMPString* str = nullptr;
    String^ text = "";

    const auto result = Utils::CheckResult(InternalAimpObject->Get(index, &timeStart, &timeFinish, &str));
    if (result == ActionResultType::OK)
    {
        text = AimpConverter::ToManagedString(str);
        str->Release();
        str = nullptr;
    }

    return gcnew AimpActionResult<String^>(result, text);
}

ActionResultType AimpLyrics::GetCount(int% value)
{
    return ActionResultType::Fail;
}

VoidResult AimpLyrics::LoadFromFile(String^ virtualFileName)
{
    IAIMPString* str = AimpConverter::ToAimpString(virtualFileName);
    const auto res = CheckResult(InternalAimpObject->LoadFromFile(str));
    str->Release();
    str = nullptr;
    return ACTION_RESULT(res);
}

VoidResult AimpLyrics::LoadFromStream(IAimpStream^ stream, LyricsFormat format)
{
    return ACTION_RESULT(ActionResultType::NotImplemented);
}

VoidResult AimpLyrics::LoadFromString(String^ lyrics, LyricsFormat format)
{
    IAIMPString* str = AimpConverter::ToAimpString(lyrics);
    const auto res = CheckResult(InternalAimpObject->LoadFromString(str, static_cast<int>(format)));
    str->Release();
    str = nullptr;
    return ACTION_RESULT(res);
}

VoidResult AimpLyrics::SaveToFile(String^ fileUri)
{
    auto str = AimpConverter::ToAimpString(fileUri);
    const auto result = Utils::CheckResult(InternalAimpObject->SaveToFile(str));
    str->Release();
    str = nullptr;
    return ACTION_RESULT(result);
}

VoidResult AimpLyrics::SaveToStream(IAimpStream^ stream, LyricsFormat format)
{
    return ACTION_RESULT(ActionResultType::NotImplemented);
}

AimpActionResult<String^>^ AimpLyrics::SaveToString(LyricsFormat format)
{
    String^ lyrics = "";
    IAIMPString* str = AimpConverter::ToAimpString(lyrics);
    const auto result = Utils::CheckResult(InternalAimpObject->SaveToString(&str, static_cast<int>(format)));

    if (result == ActionResultType::OK)
    {
        lyrics = AimpConverter::ToManagedString(str);
    }

    str->Release();
    str = nullptr;

    return gcnew AimpActionResult<String^>(result, lyrics);
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
