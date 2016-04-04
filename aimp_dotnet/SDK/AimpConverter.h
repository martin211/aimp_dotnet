#pragma once
#include "guiddef.h"
#include "vcclr.h"

#include "..\AIMPSDK\AIMPSDK.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK;

        /// <summary>
        /// Aimp  Converter helper class.
        /// </summary>
        public ref class AimpConverter sealed
        {
        internal:
            /// <summary>
            /// Gets the AIMP native object.
            /// </summary>
            /// <param name="objectId">The object identifier.</param>
            template<typename TAimpNativeObject>
            static TAimpNativeObject* GetObject(REFIID objectId);

            static IAIMPString* GetAimpString(String^ value);

            static String^ GetString(IAIMPString* value);

            static IAIMPImage* GetImage(System::Drawing::Bitmap^ image);

            static AIMP::SDK::Visuals::AimpVisualData^ PAIMPVisualDataToManaged(PAIMPVisualData data);

            static System::Drawing::Bitmap^ GetBitmap(IAIMPImageContainer* imageContainer);

            static System::Drawing::Bitmap^ GetBitmap(IAIMPImage* image);

            static IAIMPImageContainer* ToContainer(System::Drawing::Bitmap ^image);

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
        };
    }
}