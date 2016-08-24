#include "..\Stdafx.h"

#include "AimpExtension.h"
#include "..\Utils.h"
#include "ManagedAimpCore.h"

namespace AIMP
{
    namespace SDK
    {
        //template<typename TAimpNativeObject>
        //TAimpNativeObject* AimpExtension::MakeObject(REFIID objectId)
        //{
        //    TAimpNativeObject* object = NULL;

        //    if (GetCore()->CreateObject(objectId, (void**)&object) == S_OK)
        //    {
        //        return object;
        //    }

        //    return NULL;
        //}

        IAIMPString* AimpExtension::GetAimpString(String ^value)
        {
            IAIMPString *strObject = MakeObject<IAIMPString>(IID_IAIMPString);
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
                array<Byte> ^buffer = gcnew array<byte>((int)stream->Length);
                buffer = stream->ToArray();

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

        AimpActionResult PropertyListExtension::SetObject(IAIMPPropertyList* propertyList, int propertyId, IUnknown *value)
        {
            return Utils::CheckResult(propertyList->SetValueAsObject(propertyId, value));
        }

        AimpActionResult PropertyListExtension::SetString(IAIMPPropertyList* propertyList, int propertyId, String ^value)
        {
            // No need to process empty value
            if (String::IsNullOrWhiteSpace(value))
            {
                return AimpActionResult::InvalidArguments;
            }

            IAIMPString *str = NULL;
            try
            {
                str = AimpExtension::GetAimpString(value);
                return SetObject(propertyList, propertyId, str);
            }
            finally
            {
                str->Release();
                str = NULL;
            }

            return AimpActionResult::Unexpected;
        }

        AimpActionResult PropertyListExtension::SetInt32(IAIMPPropertyList* propertyList, int propertyId, int value)
        {
            return Utils::CheckResult(propertyList->SetValueAsInt32(propertyId, value));
        }

        AimpActionResult PropertyListExtension::SetInt64(IAIMPPropertyList* propertyList, int propertyId, Int64 value)
        {
            return Utils::CheckResult(propertyList->SetValueAsInt64(propertyId, value));
        }

        AimpActionResult PropertyListExtension::SetFloat(IAIMPPropertyList* propertyList, int propertyId, double value)
        {
            return Utils::CheckResult(propertyList->SetValueAsFloat(propertyId, value));
        }

        AimpActionResult PropertyListExtension::SetBool(IAIMPPropertyList* propertyList, int propertyId, bool value)
        {
            return SetInt32(propertyList, propertyId, value ? 1 : 0);
        }

        AimpActionResult PropertyListExtension::GetString(IAIMPPropertyList* propertyList, int propertyId, String^% value)
        {
            IAIMPString* str = NULL;
            String ^val = String::Empty;

            try
            {
                AimpActionResult result = Utils::CheckResult(propertyList->GetValueAsObject(propertyId, IID_IAIMPString, (void**)&str));
                if (result != AimpActionResult::Ok)
                {
                    value = String::Empty;
                    return result;
                }

                if (str != NULL)
                {
                    result = GetString(str, val);
                    value = val;
                    return result;
                }
            }
            catch (System::Exception ^ex)
            {
                return AimpActionResult::Fail;
            }
            finally
            {
                if (str != NULL)
                {
                    str->Release();
                    str = NULL;
                }
            }

            return AimpActionResult::Unexpected;
        }

        AimpActionResult PropertyListExtension::GetString(IAIMPString* aimpString, String^% value)
        {
            value = gcnew String(aimpString->GetData());
            return AimpActionResult::Ok;
        }

        AimpActionResult PropertyListExtension::GetObject(IAIMPPropertyList* propertyList, int propertyId, REFIID objectId, void** value)
        {
            AimpActionResult result = Utils::CheckResult(propertyList->GetValueAsObject(propertyId, objectId, (void**)&value));
            return result;
        }

        AimpActionResult PropertyListExtension::GetInt32(IAIMPPropertyList* propertyList, int propertyId, int %value)
        {
            int val = 0;
            AimpActionResult result = Utils::CheckResult(propertyList->GetValueAsInt32(propertyId, &val));
            value = val;
            return result;
        }

        AimpActionResult PropertyListExtension::GetInt64(IAIMPPropertyList* propertyList, int propertyId, Int64 %value)
        {
            Int64 val = 0;
            AimpActionResult result = Utils::CheckResult(propertyList->GetValueAsInt64(propertyId, &val));
            value = val;
            return result;
        }

        AimpActionResult PropertyListExtension::GetFloat(IAIMPPropertyList* propertyList, int propertyId, double %value)
        {
            double val = 0;
            AimpActionResult result = Utils::CheckResult(propertyList->GetValueAsFloat(propertyId, &val));
            value = val;
            return result;
        }

        AimpActionResult PropertyListExtension::GetBool(IAIMPPropertyList* propertyList, int propertyId, bool %value)
        {
            int *val = 0;
            AimpActionResult result = GetInt32(propertyList, propertyId, *val);
            value = val > 0;
            return result;
        }

        String^ PropertyListExtension::GetString(IAIMPPropertyList *propertyList, int propertyId)
        {
            String^ val = String::Empty;
            if (GetString(propertyList, propertyId, *&val) == AimpActionResult::Ok)
            {
                return val;
            }

            return val;
        }

        int PropertyListExtension::GetInt32(IAIMPPropertyList *propertyList, int propertyId)
        {
            int val = 0;
            if (GetInt32(propertyList, propertyId, val) == AimpActionResult::Ok)
            {
                return val;
            }

            return 0;
        }

        Int64 PropertyListExtension::GetInt64(IAIMPPropertyList *propertyList, int propertyId)
        {
            Int64 val;
            if (GetInt64(propertyList, propertyId, val) == AimpActionResult::Ok)
            {
                return val;
            }

            return 0;
        }

        double PropertyListExtension::GetFloat(IAIMPPropertyList *propertyList, int propertyId)
        {
            double val;
            if (GetFloat(propertyList, propertyId, val) == AimpActionResult::Ok)
            {
                return val;
            }

            return 0;
        }

        bool PropertyListExtension::GetBool(IAIMPPropertyList *propertyList, int propertyId)
        {
            bool val;
            if (GetBool(propertyList, propertyId, val) == AimpActionResult::Ok)
            {
                return val;
            }

            return false;
        }

        AimpActionResult PropertyListExtension::GetVariant(IAIMPPropertyList2 *propertyList, int propertyId, Object^% value)
        {
            VARIANT val;
            AimpActionResult result = Utils::CheckResult(propertyList->GetValueAsVariant(propertyId, &val));
            //value = AimpExtension::ToManaged(val);
            //value = val->cVal;
            //value = AIMP::SDK::Variant();
            return result;
        }

        AimpActionResult PropertyListExtension::SetVariant(IAIMPPropertyList2 *propertyList, int propertyId, Object^% val)
        {
            return AimpActionResult::NotImplemented;
        }
    }
}
