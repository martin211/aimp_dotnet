// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace AIMP::SDK;

        public ref class AimpConfig :
            public AimpObject<IAIMPConfig>,
            public IAimpConfig {
        public:
            explicit AimpConfig(IAIMPConfig* aimpObject);

            virtual ActionResult Delete(String^ keyPath);

            virtual FloatResult GetValueAsFloat(String^ keyPath);

            virtual IntResult GetValueAsInt32(String^ keyPath);

            virtual Int64Result GetValueAsInt64(String^ keyPath);

            virtual StreamResult GetValueAsStream(String^ keyPath);

            virtual StringResult GetValueAsString(String^ keyPath);

            virtual ActionResult SetValueAsFloat(String^ keyPath, float value);

            virtual ActionResult SetValueAsInt32(String^ keyPath, int value);

            virtual ActionResult SetValueAsInt64(String^ keyPath, Int64 value);

            virtual ActionResult SetValueAsStream(String^ keyPath, IAimpStream^ stream);

            virtual ActionResult SetValueAsString(String^ keyPath, String^ value);
        };
    }
}
