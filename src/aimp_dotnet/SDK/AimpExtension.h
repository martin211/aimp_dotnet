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

            static IUnknown* MakeObject(REFIID objectId);

            template<typename TObject>
            static TObject* MakeObject2(REFIID objectId);

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
    }
}