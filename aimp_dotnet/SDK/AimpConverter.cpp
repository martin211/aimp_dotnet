#include "..\Stdafx.h"

#include "AimpConverter.h"
#include "..\Utils.h"
#include "ManagedAimpCore.h"

namespace AIMP
{
    namespace SDK
    {
        template<typename TAimpNativeObject>
        TAimpNativeObject AimpConverter::GetObject(REFIID objectId)
        {
            TAimpNativeObject object = NULL;

            if (GetCore()->CreateObject(objectId, (void**)&object) == S_OK)
            {
                return object;
            }

            return NULL;
        }

        IAIMPString* AimpConverter::GetAimpString(String ^value)
        {
            IAIMPString *strObject = GetObject<IAIMPString*>(IID_IAIMPString);
            pin_ptr<const WCHAR> strDate = PtrToStringChars(value);
            
            //if (core->CreateObject(IID_IAIMPString, (void**)&strObject) == S_OK)
            //{
            //    return NULL;
            //}

            strObject->SetData((PWCHAR)strDate, value->Length);
            return strObject;
        }

        IAIMPImage* AimpConverter::GetImage(System::Drawing::Bitmap^ image)
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

        IAIMPCore* AimpConverter::GetCore()
        {
            return AIMP::SDK::ManagedAimpCore::GetAimpCore();
        }

        AimpActionResult PropertyListExtension::SetObject(IAIMPPropertyList *propertyList, int propertyId, IUnknown *value)
        {
            return Utils::CheckResult(propertyList->SetValueAsObject(propertyId, value));
        }

        AimpActionResult PropertyListExtension::SetString(IAIMPPropertyList *propertyList, int propertyId, String ^value)
        {
            // No need to process empty value
            if (String::IsNullOrWhiteSpace(value))
            {
                return AimpActionResult::InvalidArguments;
            }

            IAIMPString *str = NULL;
            try
            {
                str = AimpConverter::GetAimpString(value);
                return SetObject(propertyList, propertyId, str);
            }
            finally
            {
                str->Release();
                str = NULL;
            }

            return AimpActionResult::Unexpected;
        }

        AimpActionResult PropertyListExtension::SetInt32(IAIMPPropertyList *propertyList, int propertyId, int value)
        {
            return Utils::CheckResult(propertyList->SetValueAsInt32(propertyId, value));
        }

        AimpActionResult PropertyListExtension::SetInt64(IAIMPPropertyList *propertyList, int propertyId, Int64 value)
        {
            return Utils::CheckResult(propertyList->SetValueAsInt64(propertyId, value));
        }

        AimpActionResult PropertyListExtension::SetFloat(IAIMPPropertyList *propertyList, int propertyId, double value)
        {
            return Utils::CheckResult(propertyList->SetValueAsFloat(propertyId, value));
        }

        AimpActionResult PropertyListExtension::SetBool(IAIMPPropertyList *propertyList, int propertyId, bool value)
        {
            return SetInt32(propertyList, propertyId, value ? 1 : 0);
        }

        AimpActionResult PropertyListExtension::GetString(IAIMPPropertyList *propertyList, int propertyId, String^% value)
        {
            IAIMPString* str = nullptr;
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
                str->Release();
                str = NULL;
            }

            return AimpActionResult::Unexpected;
        }

        AimpActionResult PropertyListExtension::GetString(IAIMPString *aimpString, String^% value)
        {
            value = gcnew String(aimpString->GetData());
            return AimpActionResult::Ok;
        }

        AimpActionResult PropertyListExtension::GetObject(IAIMPPropertyList *propertyList, int propertyId, REFIID objectId, void **value)
        {
            propertyList->GetValueAsObject(propertyId, objectId, (void**)&value);
            return AimpActionResult::Ok;
        }

        AimpActionResult PropertyListExtension::GetInt32(IAIMPPropertyList *propertyList, int propertyId, int %value)
        {
            int val = 0;
            AimpActionResult result = Utils::CheckResult(propertyList->GetValueAsInt32(propertyId, &val));
            value = val;
            return result;
        }

        AimpActionResult PropertyListExtension::GetInt64(IAIMPPropertyList *propertyList, int propertyId, Int64 %value)
        {
            Int64 val = 0;
            AimpActionResult result = Utils::CheckResult(propertyList->GetValueAsInt64(propertyId, &val));
            value = val;
            return result;
        }

        AimpActionResult PropertyListExtension::GetFloat(IAIMPPropertyList *propertyList, int propertyId, double %value)
        {
            double val = 0;
            AimpActionResult result = Utils::CheckResult(propertyList->GetValueAsFloat(propertyId, &val));
            value = val;
            return result;
        }

        AimpActionResult PropertyListExtension::GetBool(IAIMPPropertyList *propertyList, int propertyId, bool %value)
        {
            int *val;
            AimpActionResult result = GetInt32(propertyList, propertyId, *val);
            value = val > 0;
            return result;
        }
    }
}
