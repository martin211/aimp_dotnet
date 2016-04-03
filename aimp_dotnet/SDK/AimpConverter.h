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
            static TAimpNativeObject GetObject(REFIID objectId);

            static IAIMPString* GetAimpString(String^ value);

            static IAIMPImage* GetImage(System::Drawing::Bitmap^ image);

        private:
            static IAIMPCore* GetCore();
        };

        public ref class PropertyListExtension sealed
        {
            static AimpActionResult SetObject(IAIMPPropertyList *propertyList, int propertyId, IUnknown *value);

            static AimpActionResult SetString(IAIMPPropertyList *propertyList, int propertyId, String ^value);

            static AimpActionResult SetInt32(IAIMPPropertyList *propertyList, int propertyId, int value);

            static AimpActionResult SetInt64(IAIMPPropertyList *propertyList, int propertyId, Int64 value);

            static AimpActionResult SetFloat(IAIMPPropertyList *propertyList, int propertyId, double value);

            static AimpActionResult SetBool(IAIMPPropertyList *propertyList, int propertyId, bool value);

            static AimpActionResult GetString(IAIMPPropertyList *propertyList, int propertyId, String^% value);

            static AimpActionResult GetString(IAIMPString *aimpString, String^% value);

            static AimpActionResult GetObject(IAIMPPropertyList *propertyList, int propertyId, REFIID objectId, void **value);

            static AimpActionResult GetInt32(IAIMPPropertyList *propertyList, int propertyId, int %value);

            static AimpActionResult GetInt64(IAIMPPropertyList *propertyList, int propertyId, Int64 %value);

            static AimpActionResult GetFloat(IAIMPPropertyList *propertyList, int propertyId, double %value);

            static AimpActionResult GetBool(IAIMPPropertyList *propertyList, int propertyId, bool %value);
        };
    }
}