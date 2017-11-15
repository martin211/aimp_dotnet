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

#pragma once
#include "guiddef.h"
#include "vcclr.h"
#include "AIMPSDK\AIMPSDK.h"
#include "Utils.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::Collections::Generic;
        using namespace AIMP::SDK;

        /// <summary>
        /// Aimp Converter helper class.
        /// </summary>
        public ref class AimpConverter sealed
        {
        internal:
            /// <summary>
            /// Gets the AIMP native object.
            /// </summary>
            /// <param name="objectId">The object identifier.</param>
            //template<typename TAimpNativeObject>
            //static TAimpNativeObject* MakeObject(REFIID objectId);

            static IAIMPString* ToAimpString(String^ value);

            static String^ ToManagedString(IAIMPString* value);

            static IAIMPImage* ToAimpImage(System::Drawing::Bitmap^ image);

            static AIMP::SDK::Visuals::AimpVisualData^ PAIMPVisualDataToManaged(PAIMPVisualData data);

            static System::Drawing::Bitmap^ ToManagedBitmap(IAIMPImageContainer* imageContainer);

            static System::Drawing::Bitmap^ ToManagedBitmap(IAIMPImage* image);

            static IAIMPImageContainer* ToAimpImageContainer(System::Drawing::Bitmap ^image);

            static IUnknown* MakeObject(REFIID objectId);

            template<typename TObject>
            static TObject* CreateAimpObject(REFIID objectId);

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
                        result->Add(AimpConverter::ToManagedString(str));
                    }
                }

                return result;
            }

            static VARIANT ToNativeVariant(System::Object^ objectValue);

            static System::Object^ FromVaiant(VARIANT* variant);

            static IAIMPObjectList* GetAimpObjectList();

            static IAIMPMLDataField* GetAimpDataField();

            static IAIMPObjectList* ToManagedObjectList(List<Object^> collection)
            {
                IAIMPObjectList* list = GetAimpObjectList();
                return list;
            }
        private:
            static IAIMPCore* GetCore();
        };
    }
}
