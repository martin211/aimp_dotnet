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
#include "AimpFileInfo.h"

using namespace AIMP::SDK;

String^ AimpFileInfo::CustomData::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_CUSTOM);
}

void AimpFileInfo::CustomData::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_CUSTOM, value);
}


Drawing::Bitmap^ AimpFileInfo::AlbumArt::get()
{
    Drawing::Bitmap^ bmp = nullptr;

    IAIMPImageContainer* container = nullptr;
    AimpActionResult res = Utils::CheckResult(_aimpObject->GetValueAsObject(AIMP_FILEINFO_PROPID_ALBUMART, IID_IAIMPImageContainer, reinterpret_cast<void**>(&container)));

    if (res == AimpActionResult::OK && container != nullptr)
    {
        bmp = AimpConverter::ToManagedBitmap(container);
        container->Release();
    }
    else
    {
        IAIMPImage* image = nullptr;
        res = Utils::CheckResult(_aimpObject->GetValueAsObject(AIMP_FILEINFO_PROPID_ALBUMART, IID_IAIMPImage, reinterpret_cast<void**>(&image)));
        if (res == AimpActionResult::OK && image != nullptr)
        {
            bmp = AimpConverter::ToManagedBitmap(image);
            image->Release();
            image = nullptr;
        }
    }

    return bmp;
}

void AimpFileInfo::AlbumArt::set(Drawing::Bitmap^ value)
{
    const auto img = AimpConverter::ToAimpImage(value);
    if (img != nullptr)
    {
        PropertyListExtension::SetObject(_aimpObject, AIMP_FILEINFO_PROPID_ALBUMART, img);
    }
}


String^ AimpFileInfo::Album::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_ALBUM);
}

void AimpFileInfo::Album::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_ALBUM, value);
}

String^ AimpFileInfo::AlbumArtist::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_ALBUMARTIST);
}

void AimpFileInfo::AlbumArtist::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_ALBUMARTIST, value);
}


String^ AimpFileInfo::Artist::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_ARTIST);
}

void AimpFileInfo::Artist::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_ARTIST, value);
}


String^ AimpFileInfo::Codec::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_CODEC);
}

void AimpFileInfo::Codec::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_CODEC, value);
}


String^ AimpFileInfo::Comment::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_COMMENT);
}

void AimpFileInfo::Comment::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_COMMENT, value);
}


String^ AimpFileInfo::Composer::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_COMPOSER);
}

void AimpFileInfo::Composer::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_COMPOSER, value);
}


String^ AimpFileInfo::CopyRight::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_COPYRIGHT);
}

void AimpFileInfo::CopyRight::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_COPYRIGHT, value);
}


String^ AimpFileInfo::CUESheet::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_CUESHEET);
}

void AimpFileInfo::CUESheet::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_CUESHEET, value);
}


String^ AimpFileInfo::Date::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_DATE);
}

void AimpFileInfo::Date::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_DATE, value);
}


String^ AimpFileInfo::DiskNumber::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_DISKNUMBER);
}

void AimpFileInfo::DiskNumber::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_DISKNUMBER, value);
}


String^ AimpFileInfo::DiskTotal::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_DISKTOTAL);
}

void AimpFileInfo::DiskTotal::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_DISKTOTAL, value);
}


String^ AimpFileInfo::FileName::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_FILENAME);
}

void AimpFileInfo::FileName::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_FILENAME, value);
}


String^ AimpFileInfo::Genre::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_GENRE);
}

void AimpFileInfo::Genre::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_GENRE, value);
}


String^ AimpFileInfo::Lyrics::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_LYRICS);
}

void AimpFileInfo::Lyrics::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_LYRICS, value);
}


String^ AimpFileInfo::Publisher::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_PUBLISHER);
}

void AimpFileInfo::Publisher::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_PUBLISHER, value);
}


String^ AimpFileInfo::Title::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_TITLE);
}

void AimpFileInfo::Title::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_TITLE, value);
}


String^ AimpFileInfo::TrackTotal::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_TRACKTOTAL);
}

void AimpFileInfo::TrackTotal::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_TRACKTOTAL, value);
}


String^ AimpFileInfo::URL::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_URL);
}

void AimpFileInfo::URL::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_URL, value);
}


double AimpFileInfo::Mark::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_MARK);
}

void AimpFileInfo::Mark::set(double value)
{
    PropertyListExtension::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_MARK, value);
}


double AimpFileInfo::AddedDate::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_STAT_ADDINGDATE);
}


double AimpFileInfo::LastPlayedDate::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_STAT_LASTPLAYDATE);
}


double AimpFileInfo::StateRating::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_STAT_RATING);
}


double AimpFileInfo::StatMark::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_STAT_MARK);
}

void AimpFileInfo::StatMark::set(double value)
{
    PropertyListExtension::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_STAT_MARK, value);
}


double AimpFileInfo::TrackGain::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_TRACKGAIN);
}

void AimpFileInfo::TrackGain::set(double value)
{
    PropertyListExtension::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_TRACKGAIN, value);
}


String^ AimpFileInfo::TrackNumber::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_FILEINFO_PROPID_TRACKNUMBER);
}

void AimpFileInfo::TrackNumber::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_FILEINFO_PROPID_TRACKNUMBER, value);
}


double AimpFileInfo::TrackPeak::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_TRACKPEAK);
}

void AimpFileInfo::TrackPeak::set(double value)
{
    PropertyListExtension::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_TRACKPEAK, value);
}


double AimpFileInfo::Gain::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_ALBUMGAIN);
}

void AimpFileInfo::Gain::set(double value)
{
    PropertyListExtension::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_ALBUMGAIN, value);
}


double AimpFileInfo::Peak::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_ALBUMPEAK);
}

void AimpFileInfo::Peak::set(double value)
{
    PropertyListExtension::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_ALBUMPEAK, value);
}


double AimpFileInfo::Duration::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_DURATION);
}

void AimpFileInfo::Duration::set(double value)
{
    PropertyListExtension::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_DURATION, value);
}


int AimpFileInfo::BitRate::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_BITRATE);
}

void AimpFileInfo::BitRate::set(int value)
{
    PropertyListExtension::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_BITRATE, value);
}


int AimpFileInfo::BitDepth::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_BITDEPTH);
}

void AimpFileInfo::BitDepth::set(int value)
{
    PropertyListExtension::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_BITDEPTH, value);
}


int AimpFileInfo::BPM::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_BPM);
}

void AimpFileInfo::BPM::set(int value)
{
    PropertyListExtension::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_BPM, value);
}


int AimpFileInfo::Channels::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_CHANNELS);
}

void AimpFileInfo::Channels::set(int value)
{
    PropertyListExtension::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_CHANNELS, value);
}


int AimpFileInfo::SampleRate::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_SAMPLERATE);
}

void AimpFileInfo::SampleRate::set(int value)
{
    PropertyListExtension::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_SAMPLERATE, value);
}


int AimpFileInfo::PlayCount::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_STAT_PLAYCOUNT);
}


Int64 AimpFileInfo::FileSize::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_FILESIZE);
}

void AimpFileInfo::FileSize::set(Int64 value)
{
    PropertyListExtension::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_FILESIZE, value);
}


IAimpFileInfo^ AimpFileInfo::Clone()
{
    IAIMPFileInfo* clone;
    ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPFileInfo, reinterpret_cast<void**>(&clone));
    _aimpObject->Clone(&clone);
    return gcnew AimpFileInfo(clone);
}

void AimpFileInfo::Assign(IAimpFileInfo^ source)
{
    _aimpObject->Assign(static_cast<AimpFileInfo^>(source)->InternalAimpObject);
}

AimpFileInfo::AimpFileInfo(IAIMPFileInfo *aimpItem) : AimpObject(aimpItem)
{

}

AimpFileInfo::AimpFileInfo(IAimpFileInfo ^item)
{
    _aimpObject = static_cast<IAIMPFileInfo*>(AimpConverter::MakeObject(IID_IAIMPFileInfo));
    this->Album = item->Album;
    this->AlbumArt = item->AlbumArt;
    this->AlbumArtist = item->AlbumArtist;
    this->Artist = item->Artist;
    this->BitDepth = item->BitDepth;
    this->BitRate = item->BitRate;
    this->BPM = item->BPM;
    this->Channels = item->Channels;
    this->Codec = item->Codec;
    this->Comment = item->Comment;
    this->Composer = item->Composer;
    this->CopyRight = item->CopyRight;
    this->CUESheet = item->CUESheet;
    this->CustomData = item->CustomData;
    this->Date = item->Date;
    this->DiskNumber = item->DiskNumber;
    this->DiskTotal = item->DiskTotal;
    this->Duration = item->Duration;
    this->FileName = item->FileName;
    this->FileSize = item->FileSize;
    this->Gain = item->Gain;
    this->Genre = item->Genre;
    this->Lyrics = item->Lyrics;
    this->Mark = item->Mark;
    this->Peak = item->Peak;
    this->Publisher = item->Publisher;
    this->SampleRate = item->SampleRate;
    this->SampleRate = item->StateRating;
    this->StatMark = item->StatMark;
    this->Title = item->Title;
    this->TrackGain = item->TrackGain;
    this->TrackNumber = item->TrackNumber;
    this->TrackPeak = item->TrackPeak;
    this->TrackTotal = item->TrackTotal;
}

AimpFileInfo::AimpFileInfo()
{
    IAIMPFileInfo *fileInfo;
    ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPFileInfo, reinterpret_cast<void**>(&fileInfo));
    _aimpObject = fileInfo;
}
