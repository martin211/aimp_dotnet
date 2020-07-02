// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
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
            static void SetObject(IAIMPPropertyList* propertyList, int propertyId, IUnknown* value);

            static void SetString(IAIMPPropertyList* propertyList, int propertyId, String^ value);

            static void SetInt32(IAIMPPropertyList* propertyList, int propertyId, int value);

            static void SetInt64(IAIMPPropertyList* propertyList, int propertyId, Int64 value);

            static void SetFloat(IAIMPPropertyList* propertyList, int propertyId, double value);

            static void SetBool(IAIMPPropertyList* propertyList, int propertyId, bool value);

            static String^ GetString(IAIMPPropertyList* propertyList, int propertyId);

            static int GetInt32(IAIMPPropertyList* propertyList, int propertyId);

            static Int64 GetInt64(IAIMPPropertyList* propertyList, int propertyId);

            static double GetFloat(IAIMPPropertyList* propertyList, int propertyId);

            static bool GetBool(IAIMPPropertyList* propertyList, int propertyId);

            static void GetString(IAIMPPropertyList* propertyList, int propertyId, String^% value);

            static void GetString(IAIMPString* aimpString, String^% value);

            static ActionResultType GetObject(IAIMPPropertyList* propertyList, int propertyId, REFIID objectId,
                                              void** value);

            static ActionResultType GetInt32(IAIMPPropertyList* propertyList, int propertyId, int% value);

            static ActionResultType GetInt64(IAIMPPropertyList* propertyList, int propertyId, Int64% value);

            static ActionResultType GetFloat(IAIMPPropertyList* propertyList, int propertyId, double% value);

            static ActionResultType GetBool(IAIMPPropertyList* propertyList, int propertyId, bool% value);

            static ActionResultType GetVariant(IAIMPPropertyList2* propertyList, int propertyId,
                                               System::Object^% value);

            static ActionResultType SetVariant(IAIMPPropertyList2* propertyList, int propertyId,
                                               System::Object^% value);
        };
    }
}
