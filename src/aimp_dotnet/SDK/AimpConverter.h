// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "AIMPSDK\AIMPSDK.h"
#include "Utils.h"

using namespace System;
using namespace Runtime;
using namespace Collections::Generic;
using namespace Drawing;
using namespace Imaging;
using namespace IO;
using namespace AIMP::SDK;
using namespace FileManager;
using namespace Primitives;

namespace AIMP {
    namespace SDK {
        /// <summary>
        /// Aimp Converter helper class.
        /// </summary>
        public ref class AimpConverter sealed {
        internal:
            /// <summary>
            /// Gets the AIMP native object.
            /// </summary>
            /// <param name="objectId">The object identifier.</param>
            //template<typename TAimpNativeObject>
            //static TAimpNativeObject* MakeObject(REFIID objectId);

            static IAIMPString* ToAimpString(String^ value);

            static String^ ToManagedString(IAIMPString* value);

            static IAIMPImage* ToAimpImage(Drawing::Bitmap^ image);

            static Visuals::AimpVisualData^ PAIMPVisualDataToManaged(PAIMPVisualData data);

            static Drawing::Bitmap^ ToManagedBitmap(IAIMPImageContainer* imageContainer);

            static Drawing::Bitmap^ ToManagedBitmap(IAIMPImage* image);

            static IAIMPImageContainer* ToAimpImageContainer(Drawing::Bitmap^ image);

            static IUnknown* MakeObject(REFIID objectId);

            template <typename TObject>
            static TObject* CreateAimpObject(REFIID objectId);

            static List<String^>^ ToStringCollection(IAIMPObjectList* aimpList) {
                int count = aimpList->GetCount();
                List<String^>^ result = gcnew List<String^>(count);
                for (int i = 0; i < count; i++) {
                    IAIMPString* str;
                    auto res = aimpList->GetObject(i, IID_IAIMPString, reinterpret_cast<void**>(&str));
                    if (Utils::CheckResult(res) == ActionResultType::OK) {
                        result->Add(ToManagedString(str));
                    }
                }

                return result;
            }

            static VARIANT ToNativeVariant(Object^ objectValue);

            static Object^ FromVaiant(VARIANT* variant);

            static IAIMPObjectList* GetAimpObjectList();

            static IAIMPMLDataField* GetAimpDataField();

            static IAIMPObjectList* ToManagedObjectList(List<Object^> collection) {
                IAIMPObjectList* list = GetAimpObjectList();
                return list;
            }

            static IAIMPObjectList* ToAimpObjectList(List<String^>^ collection);

            static IAIMPFileInfo* ToAimpObject(IAimpFileInfo^ managedObject);

            static IAIMPString* ToAimpString(IAimpString^ string);
        private:
            static IAIMPCore* GetCore();
        };
    }
}
