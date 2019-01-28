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
#include "AIMPSDK\AIMPSDK.h"
#include "Utils.h"
#include <combaseapi.h>

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::Drawing;
        using namespace Collections::Generic;
        using namespace SDK;
        using namespace FileManager;

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

            static IAIMPImage* ToAimpImage(Bitmap^ image);

            static Visuals::AimpVisualData^ PAIMPVisualDataToManaged(PAIMPVisualData data);

            static Bitmap^ ToManagedBitmap(IAIMPImageContainer* imageContainer);

            static Bitmap^ ToManagedBitmap(IAIMPImage* image);

            static IAIMPImageContainer* ToAimpImageContainer(Bitmap ^image);

            static IUnknown* MakeObject(REFIID objectId);

            template<typename TObject>
            static TObject* CreateAimpObject(REFIID objectId);

            static IList<String^>^ ToStringCollection(IAIMPObjectList* aimpList)
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

            static VARIANT ToNativeVariant(Object^ objectValue);

            static System::Object^ FromVaiant(VARIANT* variant);

            static IAIMPObjectList* GetAimpObjectList();

            static IAIMPMLDataField* GetAimpDataField();

            static IAIMPObjectList* ToManagedObjectList(List<Object^> collection)
            {
                IAIMPObjectList* list = GetAimpObjectList();
                return list;
            }

            static IAIMPFileInfo* ToAimpObject(IAimpFileInfo^ managedObject);
        private:
            static IAIMPCore* GetCore();
        };
    }
}
