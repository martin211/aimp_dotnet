#include "Stdafx.h"
#include "AimpAlbumArtSearchOptions.h"

using namespace AIMP::SDK;

AimpAlbumArtSearchOptions::AimpAlbumArtSearchOptions(IAIMPPropertyList *properties, IAIMPCore* core)
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

array<System::String^>^ AimpAlbumArtSearchOptions::FileMasks::get()
{
    IAIMPString *str;
    _properties->GetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_MASKS, IID_IAIMPString, (void**)&str);
    String^ result = gcnew String(str->GetData());
    str->Release();
    return result->Split(gcnew array<WCHAR>{';'}, System::StringSplitOptions::RemoveEmptyEntries);
}

void AimpAlbumArtSearchOptions::FileMasks::set(array<System::String^>^ value)
{
    String^ str;
    for (int i = 0; i < value->Length; i++)
    {
        str += value[i] + ";";
    }
    _properties->SetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_MASKS, AimpExtension::GetAimpString(str));
}

array<System::String^>^ AimpAlbumArtSearchOptions::FileExtensions::get()
{
    IAIMPString *str;
    _properties->GetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_EXTS, IID_IAIMPString, (void**)&str);
    String^ result = gcnew String(str->GetData());
    str->Release();
    return result->Split(gcnew array<WCHAR>{';'}, System::StringSplitOptions::RemoveEmptyEntries);
}

void AimpAlbumArtSearchOptions::FileExtensions::set(array<System::String^>^ value)
{
    String^ str;
    for (int i = 0; i < value->Length; i++)
    {
        str += value[i] + ";";
    }
    IAIMPString *s = AimpExtension::GetAimpString(str);
    _properties->SetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_EXTS, s);
    s->Release();
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
