#pragma once
#include "guiddef.h"
#include "vcclr.h"
#include "..\AIMPSDK\AIMPSDK.h"
#include "..\Utils.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK;

        /// <summary>
        /// Aimp  Converter helper class.
        /// </summary>
        public ref class AimpExtension sealed
        {
        internal:
            /// <summary>
            /// Gets the AIMP native object.
            /// </summary>
            /// <param name="objectId">The object identifier.</param>
            //template<typename TAimpNativeObject>
            //static TAimpNativeObject* MakeObject(REFIID objectId);

            static IAIMPString* GetAimpString(String^ value);

            static String^ GetString(IAIMPString* value);

            static IAIMPImage* GetImage(System::Drawing::Bitmap^ image);

            static AIMP::SDK::Visuals::AimpVisualData^ PAIMPVisualDataToManaged(PAIMPVisualData data);

            static System::Drawing::Bitmap^ GetBitmap(IAIMPImageContainer* imageContainer);

            static System::Drawing::Bitmap^ GetBitmap(IAIMPImage* image);

            static IAIMPImageContainer* ToContainer(System::Drawing::Bitmap ^image);

            template<typename TObject>
            static TObject* MakeObject(REFIID objectId)
            {
                TObject *obj = NULL;
                HRESULT r = ManagedAimpCore::GetAimpCore()->CreateObject(objectId, (void**)&obj);
                return obj;
            }

            static System::Collections::Generic::IList<String^>^ ToStringCollection(IAIMPObjectList* aimpList)
            {
                int count = aimpList->GetCount();
                System::Collections::Generic::List<String^>^ result = gcnew System::Collections::Generic::List<String^>(count);
                for (int i = 0; i < count; i++)
                {
                    IAIMPString* str;
                    HRESULT res = aimpList->GetObject(i, IID_IAIMPString, (void**)&str);
                    if (Utils::CheckResult(res) == AimpActionResult::Ok)
                    {
                        result->Add(AimpExtension::GetString(str));
                    }
                }

                return result;
            }

            static VARIANT ToVariant(System::Object^ objectValue);

            static System::Object^ FromVaiant(VARIANT* variant);

            static IAIMPObjectList* GetAimpObjectList();

            static IAIMPMLDataField* GetAimpDataField();
        private:
            static IAIMPCore* GetCore();
        };

        public ref class PropertyListExtension sealed
        {
        public:
            static AimpActionResult SetObject(IAIMPPropertyList *propertyList, int propertyId, IUnknown *value);

            static AimpActionResult SetString(IAIMPPropertyList *propertyList, int propertyId, String ^value);

            static AimpActionResult SetInt32(IAIMPPropertyList *propertyList, int propertyId, int value);

            static AimpActionResult SetInt64(IAIMPPropertyList *propertyList, int propertyId, Int64 value);

            static AimpActionResult SetFloat(IAIMPPropertyList *propertyList, int propertyId, double value);

            static AimpActionResult SetBool(IAIMPPropertyList *propertyList, int propertyId, bool value);

            static String^ GetString(IAIMPPropertyList *propertyList, int propertyId);

            static int GetInt32(IAIMPPropertyList *propertyList, int propertyId);

            static Int64 GetInt64(IAIMPPropertyList *propertyList, int propertyId);

            static double GetFloat(IAIMPPropertyList *propertyList, int propertyId);

            static bool GetBool(IAIMPPropertyList *propertyList, int propertyId);

            static AimpActionResult GetString(IAIMPPropertyList *propertyList, int propertyId, String^% value);

            static AimpActionResult GetString(IAIMPString *aimpString, String^% value);

            static AimpActionResult GetObject(IAIMPPropertyList *propertyList, int propertyId, REFIID objectId, void** value);

            static AimpActionResult GetInt32(IAIMPPropertyList *propertyList, int propertyId, int %value);

            static AimpActionResult GetInt64(IAIMPPropertyList *propertyList, int propertyId, Int64 %value);

            static AimpActionResult GetFloat(IAIMPPropertyList *propertyList, int propertyId, double %value);

            static AimpActionResult GetBool(IAIMPPropertyList *propertyList, int propertyId, bool %value);

            static AimpActionResult GetVariant(IAIMPPropertyList2 *propertyList, int propertyId, System::Object^% value);

            static AimpActionResult SetVariant(IAIMPPropertyList2 *propertyList, int propertyId, System::Object^% value);
        };
    }
}