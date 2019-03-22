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

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK;

        public ref class AimpConfig :
            public AimpObject<IAIMPConfig>,
            public IAimpConfig
        {
        public:
            explicit AimpConfig(IAIMPConfig* aimpObject);

            virtual AimpActionResult Delete(String^ keyPath);

            virtual float GetValueAsFloat(String^ keyPath);

            virtual int GetValueAsInt32(String^ keyPath);

            virtual Int64 GetValueAsInt64(String^ keyPath);

            virtual IAimpStream^ GetValueAsStream(String^ keyPath);

            virtual String^ GetValueAsString(String^ keyPath);

            virtual AimpActionResult SetValueAsFloat(String^ keyPath, float value);

            virtual AimpActionResult SetValueAsInt32(String^ keyPath, int value);

            virtual AimpActionResult SetValueAsInt64(String^ keyPath, Int64 value);

            virtual AimpActionResult SetValueAsStream(String^ keyPath, IAimpStream^ stream);

            virtual AimpActionResult SetValueAsString(String^ keyPath, String^ value);
        };
    }
}
