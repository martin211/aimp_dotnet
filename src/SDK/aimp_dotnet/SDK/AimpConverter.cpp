// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpConverter.h"
#include "ManagedAimpCore.h"
#include "FileManager\AimpFileInfo.h"

IUnknown* AimpConverter::MakeObject(REFIID objectId) {
    IUnknown* obj = nullptr;
    HRESULT r = ManagedAimpCore::GetAimpCore()->CreateObject(objectId, reinterpret_cast<void**>(&obj));
    return obj;
}

IAIMPString* AimpConverter::ToAimpString(String^ value) {
    IAIMPString* strObject = CreateAimpObject<IAIMPString>(IID_IAIMPString);
    pin_ptr<const WCHAR> strDate = PtrToStringChars(value);
    strObject->SetData((PWCHAR)strDate, value->Length);
    return strObject;
}

IAIMPImage* AimpConverter::ToAimpImage(Bitmap^ image) {
    MemoryStream^ stream = nullptr;
    IAIMPStream* aimpStream = nullptr;
    IAIMPImage* img = nullptr;

    try {
        stream = gcnew MemoryStream();
        image->Save(stream, ImageFormat::Png);
        array<Byte>^ buffer = stream->ToArray();

        if (Utils::CheckResult(GetCore()->CreateObject(IID_IAIMPMemoryStream, (void**)&aimpStream)) == ActionResultType::OK
            && Utils::CheckResult(GetCore()->CreateObject(IID_IAIMPImage, (void**)&img)) == ActionResultType::OK) {
            aimpStream->SetSize(stream->Length);
            pin_ptr<System::Byte> p = &buffer[0];
            unsigned char* pby = p;
            if (Utils::CheckResult(aimpStream->Write(pby, (int)stream->Length, nullptr)) == ActionResultType::OK) {
                img->LoadFromStream(aimpStream);
            }

            return img;
        }
    }
    finally {
        if (stream != nullptr) {
            stream->Close();
        }
        aimpStream->Release();
        aimpStream = nullptr;
    }

    return nullptr;
}

IAIMPCore* AimpConverter::GetCore() {
    return ManagedAimpCore::GetAimpCore();
}

Visuals::AimpVisualData^ AimpConverter::PAIMPVisualDataToManaged(PAIMPVisualData data) {
    auto result = gcnew Visuals::AimpVisualData();
    result->Peaks = gcnew array<float>(2);
    result->Spectrum = gcnew array<array<float>^>(3);
    result->WaveForm = gcnew array<array<float>^>(2);

    result->Peaks[0] = data->Peaks[0];
    result->Peaks[1] = data->Peaks[1];

    for (int i = 0; i < 3; i++) {
        array<float>^ arr = gcnew array<float>(AIMP_VISUAL_SPECTRUM_MAX);
        for (int j = 0; j < AIMP_VISUAL_SPECTRUM_MAX; j++) {
            arr[j] = data->Spectrum[i][j];
        }
        result->Spectrum[i] = arr;
    }

    for (int i = 0; i < 2; i++) {
        array<float>^ arr = gcnew array<float>(AIMP_VISUAL_WAVEFORM_MAX);
        for (int j = 0; j < AIMP_VISUAL_WAVEFORM_MAX; j++) {
            arr[j] = data->WaveForm[i][j];
        }
        result->WaveForm[i] = arr;
    }

    return result;
}

Bitmap^ AimpConverter::ToManagedBitmap(IAIMPImageContainer* imageContainer) {
    IAIMPImage* image = nullptr;
    try {
        if (Utils::CheckResult(ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPImage, reinterpret_cast<void**>(&image))) != ActionResultType::OK) {
            return nullptr;
        }

        if (Utils::CheckResult(imageContainer->CreateImage(&image)) != ActionResultType::OK || image == nullptr) {
            return nullptr;
        }

        return ToManagedBitmap(image);
    }
    finally {
        if (image != nullptr) {
            image->Release();
            image = nullptr;
        }
    }

    return nullptr;
}

Bitmap^ AimpConverter::ToManagedBitmap(IAIMPImage* image) {
    SIZE size;
    if (Utils::CheckResult(image->GetSize(&size)) == ActionResultType::OK) {
        if (size.cx == 0 || size.cy == 0) {
            return nullptr;
        }

        auto bmp = gcnew Bitmap(size.cx, size.cy);

        IAIMPStream* stream = nullptr;
        ActionResultType res = Utils::CheckResult(
            ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPMemoryStream, (void**)&stream));

        if (res != ActionResultType::OK || stream == nullptr) {
            return nullptr;
        }

        image->SaveToStream(stream, AIMP_IMAGE_FORMAT_PNG);
        if (stream->GetSize() > 0) {
            Int64 size = stream->GetSize();
            unsigned char* buf = new unsigned char[(int)size];
            HRESULT r = stream->Seek(0, AIMP_STREAM_SEEKMODE_FROM_BEGINNING);
            r = stream->Read(buf, (int)size);

            auto strm = gcnew MemoryStream();
            try {
                for (int i = 0; i < size; i++) {
                    strm->WriteByte(buf[i]);
                }
                bmp = gcnew Bitmap(strm);
            }
            finally {
                strm->Close();
                strm = nullptr;

                delete[] buf;
                stream->Release();
                stream = nullptr;
            }
        }

        return bmp;
    }

    return nullptr;
}

IAIMPImageContainer* AimpConverter::ToAimpImageContainer(Bitmap^ image) {
    IAIMPImageContainer* container;
    if (Utils::CheckResult(ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPImageContainer, (void**)&container)) ==
        ActionResultType::OK) {
        Stream^ stream = nullptr;
        try {
            stream = gcnew MemoryStream();
            image->Save(stream, ImageFormat::Jpeg);
            stream->Seek(0, SeekOrigin::Begin);
            if (Utils::CheckResult(container->SetDataSize((DWORD)stream->Length)) != ActionResultType::OK) {
                return nullptr;
            }

            byte* b = container->GetData();
            for (int i = 0; i < stream->Length - 1; i++) {
                b[i] = stream->ReadByte();
            }

            return container;
        }
        finally {
            if (stream != nullptr) {
                stream->Close();
            }
        }
    }

    return nullptr;
}

String^ AimpConverter::ToManagedString(IAIMPString* value) {
    return gcnew String(value->GetData());
}

VARIANT AimpConverter::ToNativeVariant(Object^ objectValue) {
    VARIANT varTag;
    VariantInit(&varTag);
    IntPtr h = IntPtr(&varTag);
    InteropServices::Marshal::GetNativeVariantForObject(objectValue, h);
    return varTag;
}

Object^ AimpConverter::FromVaiant(VARIANT* variant) {
    void* p = variant;
    return InteropServices::Marshal::GetObjectForNativeVariant(IntPtr(p));
}

IAIMPObjectList* AimpConverter::GetAimpObjectList() {
    IAIMPObjectList* res = CreateAimpObject<IAIMPObjectList>(IID_IAIMPObjectList);
    return res;
}

IAIMPMLDataField* AimpConverter::GetAimpDataField() {
    IAIMPMLDataField* res = CreateAimpObject<IAIMPMLDataField>(IID_IAIMPMLDataField);
    return res;
}

template <typename TObject>
TObject* AimpConverter::CreateAimpObject(REFIID objectId) {
    TObject* obj = nullptr;
    HRESULT r = ManagedAimpCore::GetAimpCore()->CreateObject(objectId, reinterpret_cast<void**>(&obj));
    return obj;
}

IAIMPFileInfo* AimpConverter::ToAimpObject(IAimpFileInfo^ managedObject) {
    AimpFileInfo^ result = gcnew AimpFileInfo();
    result->Album = managedObject->Album;
    result->AlbumArt = managedObject->AlbumArt;
    result->AlbumArtist = managedObject->AlbumArtist;
    result->Artist = managedObject->Artist;
    result->BitDepth = managedObject->BitDepth;
    result->BitRate = managedObject->BitRate;
    result->BPM = managedObject->BPM;
    result->Channels = managedObject->Channels;
    result->Codec = managedObject->Codec;
    result->Comment = managedObject->Comment;
    result->Composer = managedObject->Composer;
    result->CopyRight = managedObject->CopyRight;
    result->CUESheet = managedObject->CUESheet;
    result->CustomData = managedObject->CustomData;
    result->Date = managedObject->Date;
    result->DiskNumber = managedObject->DiskNumber;
    result->DiskTotal = managedObject->DiskTotal;
    result->Duration = managedObject->Duration;
    result->FileName = managedObject->FileName;
    result->FileSize = managedObject->FileSize;
    result->AlbumGain = managedObject->AlbumGain;
    result->Genre = managedObject->Genre;
    //result->LastPlayedDate = fi->LastPlayedDate;
    result->Lyrics = managedObject->Lyrics;
    result->StatMark = managedObject->StatMark;
    result->AlbumPeak = managedObject->AlbumPeak;
    //result->PlayCount = fi->PlayCount;
    result->Publisher = managedObject->Publisher;
    result->SampleRate = managedObject->SampleRate;
    result->StatMark = managedObject->StatMark;
    result->Title = managedObject->Title;
    result->TrackGain = managedObject->TrackGain;
    result->TrackNumber = managedObject->TrackNumber;
    result->TrackPeak = managedObject->TrackPeak;
    result->TrackTotal = managedObject->TrackTotal;
    return result->InternalAimpObject;
}

IAIMPObjectList* AimpConverter::ToAimpObjectList(List<String^>^ collection) {
    IAIMPObjectList* list = GetAimpObjectList();

    for (int i = 0; i < collection->Count; i++) {
        list->Add(ToAimpString(collection[i]));
    }

    return list;
}

IAIMPString* AimpConverter::ToAimpString(IAimpString^ string) {
    IAIMPString* strObject = CreateAimpObject<IAIMPString>(IID_IAIMPString);
    const pin_ptr<const WCHAR> strDate = PtrToStringChars(string->GetData());
    strObject->SetData(PWCHAR(strDate), string->GetLength());
    return strObject;
}
