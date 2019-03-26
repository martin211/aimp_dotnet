// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once
#include "AIMPSDK\AIMPSDK.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;

        public ref class PropertyListExtension sealed
        {
        public:
            static AimpActionResult SetObject(IAIMPPropertyList* propertyList, int propertyId, IUnknown* value);

            static AimpActionResult SetString(IAIMPPropertyList* propertyList, int propertyId, String^ value);

            static AimpActionResult SetInt32(IAIMPPropertyList* propertyList, int propertyId, int value);

            static AimpActionResult SetInt64(IAIMPPropertyList* propertyList, int propertyId, Int64 value);

            static AimpActionResult SetFloat(IAIMPPropertyList* propertyList, int propertyId, double value);

            static AimpActionResult SetBool(IAIMPPropertyList* propertyList, int propertyId, bool value);

            static String^ GetString(IAIMPPropertyList* propertyList, int propertyId);

            static int GetInt32(IAIMPPropertyList* propertyList, int propertyId);

            static Int64 GetInt64(IAIMPPropertyList* propertyList, int propertyId);

            static double GetFloat(IAIMPPropertyList* propertyList, int propertyId);

            static bool GetBool(IAIMPPropertyList* propertyList, int propertyId);

            static AimpActionResult GetString(IAIMPPropertyList* propertyList, int propertyId, String^% value);

            static AimpActionResult GetString(IAIMPString* aimpString, String^% value);

            static AimpActionResult GetObject(IAIMPPropertyList* propertyList, int propertyId, REFIID objectId,
                                              void** value);

            static AimpActionResult GetInt32(IAIMPPropertyList* propertyList, int propertyId, int% value);

            static AimpActionResult GetInt64(IAIMPPropertyList* propertyList, int propertyId, Int64% value);

            static AimpActionResult GetFloat(IAIMPPropertyList* propertyList, int propertyId, double% value);

            static AimpActionResult GetBool(IAIMPPropertyList* propertyList, int propertyId, bool% value);

            static AimpActionResult GetVariant(IAIMPPropertyList2* propertyList, int propertyId,
                                               System::Object^% value);

            static AimpActionResult SetVariant(IAIMPPropertyList2* propertyList, int propertyId,
                                               System::Object^% value);
        };
    }
}
