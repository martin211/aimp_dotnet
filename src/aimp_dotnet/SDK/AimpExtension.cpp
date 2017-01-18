#include "Stdafx.h"

#include "AimpExtension.h"
#include "..\Utils.h"
#include "ManagedAimpCore.h"

namespace AIMP
{
    namespace SDK
    {
        IUnknown* AimpExtension::MakeObject(REFIID objectId)
        {
            IUnknown *obj = NULL;
            HRESULT r = ManagedAimpCore::GetAimpCore()->CreateObject(objectId, (void**)&obj);
            return obj;
        }


        IAIMPString* AimpExtension::GetAimpString(String ^value)
        {
            IAIMPString *strObject = MakeObject2<IAIMPString>(IID_IAIMPString);
            pin_ptr<const WCHAR> strDate = PtrToStringChars(value);
            strObject->SetData((PWCHAR)strDate, value->Length);
            return strObject;
        }

        IAIMPImage* AimpExtension::GetImage(System::Drawing::Bitmap^ image)
        {
            System::IO::MemoryStream ^stream;
            IAIMPStream *aimpStream = NULL;
            IAIMPImage *img = NULL;

            try
            {
                stream = gcnew System::IO::MemoryStream();
                image->Save(stream, System::Drawing::Imaging::ImageFormat::Png);
                array<Byte>^ buffer = stream->ToArray();

                if (Utils::CheckResult(GetCore()->CreateObject(IID_IAIMPMemoryStream, (void**)&aimpStream)) == AIMP::SDK::AimpActionResult::Ok
                    && Utils::CheckResult(GetCore()->CreateObject(IID_IAIMPImage, (void**)&img)) == AIMP::SDK::AimpActionResult::Ok)
                {
                    aimpStream->SetSize(stream->Length);
                    pin_ptr<System::Byte> p = &buffer[0];
                    unsigned char* pby = p;
                    if (Utils::CheckResult(aimpStream->Write(pby, (int)stream->Length, nullptr)) == AIMP::SDK::AimpActionResult::Ok)
                    {
                        img->LoadFromStream(aimpStream);
                    }

                    return img;
                }
            }
            finally
            {
                if (stream != nullptr)
                {
                    stream->Close();
                }
                aimpStream->Release();
                aimpStream = NULL;
            }

            return NULL;
        }

        IAIMPCore* AimpExtension::GetCore()
        {
            return AIMP::SDK::ManagedAimpCore::GetAimpCore();
        }

        AIMP::SDK::Visuals::AimpVisualData^ AimpExtension::PAIMPVisualDataToManaged(PAIMPVisualData data)
        {
            AIMP::SDK::Visuals::AimpVisualData ^result = gcnew AIMP::SDK::Visuals::AimpVisualData();
            result->Peaks = gcnew array<float>(2);
            result->Spectrum = gcnew array<array<float>^>(3);
            result->WaveForm = gcnew array<array<float>^>(2);

            result->Peaks[0] = data->Peaks[0];
            result->Peaks[1] = data->Peaks[1];

            for (int i = 0; i < 3; i++)
            {
                array<float> ^arr = gcnew array<float>(AIMP_VISUAL_SPECTRUM_MAX);
                for (int j = 0; j < AIMP_VISUAL_SPECTRUM_MAX; j++)
                {
                    arr[j] = data->Spectrum[i][j];
                }
                result->Spectrum[i] = arr;
            }

            for (int i = 0; i < 2; i++)
            {
                array<float> ^arr = gcnew array<float>(AIMP_VISUAL_WAVEFORM_MAX);
                for (int j = 0; j < AIMP_VISUAL_WAVEFORM_MAX; j++)
                {
                    arr[j] = data->WaveForm[i][j];
                }
                result->WaveForm[i] = arr;
            }

            return result;
        }

        System::Drawing::Bitmap^ AimpExtension::GetBitmap(IAIMPImageContainer* imageContainer)
        {
            IAIMPImage* image = NULL;
            try
            {
                if (Utils::CheckResult(ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPImage, (void**)&image)) == AimpActionResult::Ok)
                {
                    return nullptr;
                }

                imageContainer->CreateImage(&image);

                if (image == NULL)
                {
                    return nullptr;
                }
                return GetBitmap(image);
            }
            finally
            {
                image->Release();
                image = NULL;
            }

            return nullptr;
        }

        System::Drawing::Bitmap^ AimpExtension::GetBitmap(IAIMPImage* image)
        {
            SIZE size;
            if (Utils::CheckResult(image->GetSize(&size)) == AimpActionResult::Ok)
            {
                if (size.cx == 0 || size.cy == 0)
                {
                    return nullptr;
                }

                System::Drawing::Bitmap^ bmp = gcnew System::Drawing::Bitmap(size.cx, size.cy);

                IAIMPStream *stream;
                AIMP::SDK::ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPMemoryStream, (void**)&stream);
                image->SaveToStream(stream, AIMP_IMAGE_FORMAT_PNG);
                if (stream->GetSize() > 0)
                {
                    Int64 size = stream->GetSize();
                    unsigned char *buf = new unsigned char[(int)size];
                    HRESULT r = stream->Seek(0, AIMP_STREAM_SEEKMODE_FROM_BEGINNING);
                    r = stream->Read(buf, (int)size);

                    System::IO::MemoryStream^ strm = gcnew System::IO::MemoryStream();
                    try
                    {
                        for (int i = 0; i < size; i++)
                        {
                            strm->WriteByte(buf[i]);
                        }
                        bmp = gcnew System::Drawing::Bitmap(strm);
                    }
                    finally
                    {
                        strm->Close();
                        strm = nullptr;

                        delete[] buf;
                        stream->Release();
                        image->Release();
                        stream = NULL;
                        image = NULL;
                    }
                }

                return bmp;
            }

            return nullptr;
        }

        IAIMPImageContainer* AimpExtension::ToContainer(System::Drawing::Bitmap ^image)
        {
            IAIMPImageContainer *container;
            if (Utils::CheckResult(ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPImageContainer, (void**)&container)) == AimpActionResult::Ok)
            {
                System::IO::Stream ^stream = nullptr;
                try
                {
                    stream = gcnew System::IO::MemoryStream();
                    image->Save(stream, System::Drawing::Imaging::ImageFormat::Jpeg);
                    stream->Seek(0, System::IO::SeekOrigin::Begin);
                    if (Utils::CheckResult(container->SetDataSize((DWORD)stream->Length)) != AimpActionResult::Ok)
                    {
                        return NULL;
                    }

                    byte *b = container->GetData();
                    for (int i = 0; i < stream->Length - 1; i++)
                    {
                        b[i] = stream->ReadByte();
                    }

                    return container;
                }
                finally
                {
                    if (stream != nullptr)
                    {
                        stream->Close();
                    }
                }
            }

            return NULL;
        }

        String^ AimpExtension::GetString(IAIMPString* value)
        {
            return gcnew String(value->GetData());
        }



        VARIANT AimpExtension::ToVariant(System::Object^ objectValue)
        {
            VARIANT varTag;
            VariantInit(&varTag);
            IntPtr h = IntPtr(&varTag);
            System::Runtime::InteropServices::Marshal::GetNativeVariantForObject(objectValue, h);
            return varTag;
        }

        System::Object^ AimpExtension::FromVaiant(VARIANT* variant)
        {
            void *p = variant;
            return System::Runtime::InteropServices::Marshal::GetObjectForNativeVariant(IntPtr(p));
        }

        IAIMPObjectList* AimpExtension::GetAimpObjectList()
        {
            IAIMPObjectList* res = (IAIMPObjectList*)MakeObject(IID_IAIMPObjectList);
            return res;
        }

        IAIMPMLDataField* AimpExtension::GetAimpDataField()
        {
            IAIMPMLDataField* res = (IAIMPMLDataField*)MakeObject(IID_IAIMPMLDataField);
            return res;
        }


        template<typename TObject>
        TObject* AIMP::SDK::AimpExtension::MakeObject2(REFIID objectId)
        {
            TObject *obj = NULL;
            HRESULT r = ManagedAimpCore::GetAimpCore()->CreateObject(objectId, (void**)&obj);
            return obj;
        }

    }
}
