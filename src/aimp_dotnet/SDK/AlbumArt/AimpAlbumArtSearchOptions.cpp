// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpAlbumArtSearchOptions.h"

using namespace AIMP::SDK;

AimpAlbumArtSearchOptions::AimpAlbumArtSearchOptions(IAIMPPropertyList* properties, IAIMPCore* core)
{
    _properties = properties;
    _core = core;
    _findInFiles = false;
}

bool AimpAlbumArtSearchOptions::FindInFiles::get()
{
    int val = 0;
    _properties->GetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES, &val);
    return val != 0;
}

void AimpAlbumArtSearchOptions::FindInFiles::set(bool value)
{
    _properties->SetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES, value ? 1 : 0);
}

bool AimpAlbumArtSearchOptions::FindInInternet::get()
{
    int val = 0;
    _properties->GetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_INTERNET, &val);
    return val != 0;
}

void AimpAlbumArtSearchOptions::FindInInternet::set(bool value)
{
    _properties->SetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_INTERNET, value ? 1 : 0);
}

array<String^>^ AimpAlbumArtSearchOptions::FileMasks::get()
{
    IAIMPString* str;
    _properties->GetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_MASKS, IID_IAIMPString,
                                  reinterpret_cast<void**>(&str));
    String^ result = gcnew String(str->GetData());
    str->Release();
    return result->Split(gcnew array<WCHAR>{';'}, StringSplitOptions::RemoveEmptyEntries);
}

void AimpAlbumArtSearchOptions::FileMasks::set(array<String^>^ value)
{
    auto str = String::Empty;
    for (int i = 0; i < value->Length; i++)
    {
        str += value[i] + ";";
    }
    _properties->SetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_MASKS, AimpConverter::ToAimpString(str));
}

array<String^>^ AimpAlbumArtSearchOptions::FileExtensions::get()
{
    IAIMPString* str;
    _properties->GetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_EXTS, IID_IAIMPString,
                                  reinterpret_cast<void**>(&str));
    auto result = gcnew String(str->GetData());
    str->Release();
    str = nullptr;
    return result->Split(gcnew array<WCHAR>{';'}, StringSplitOptions::RemoveEmptyEntries);
}

void AimpAlbumArtSearchOptions::FileExtensions::set(array<String^>^ value)
{
    auto str = String::Empty;
    for (int i = 0; i < value->Length; i++)
    {
        str += value[i] + ";";
    }
    auto s = AimpConverter::ToAimpString(str);
    _properties->SetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_EXTS, s);
    s->Release();
    s = nullptr;
}

int AimpAlbumArtSearchOptions::MaxFileSize::get()
{
    int val = 0;
    _properties->GetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES, &val);
    return val;
}

void AimpAlbumArtSearchOptions::MaxFileSize::set(int value)
{
    _properties->SetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES, value);
}
