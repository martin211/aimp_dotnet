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

#include "SDK\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace ConfigurationManager;

        public ref class AimpServiceConfig :
            public BaseAimpService<IAIMPServiceConfig>,
            public IAimpServiceConfig
        {
        public:
            explicit AimpServiceConfig(ManagedAimpCore^ core);

            ~AimpServiceConfig();

            virtual VoidResult FlushCache();

            virtual VoidResult Delete(String^ keyPath);

            virtual FloatResult GetValueAsFloat(String^ keyPath);

            virtual IntResult GetValueAsInt32(String^ keyPath);

            virtual Int64Result GetValueAsInt64(String^ keyPath);

            virtual StreamResult GetValueAsStream(String^ keyPath);

            virtual StringResult GetValueAsString(String^ keyPath);

            virtual VoidResult SetValueAsFloat(String^ keyPath, float value);

            virtual VoidResult SetValueAsInt32(String^ keyPath, int value);

            virtual VoidResult SetValueAsInt64(String^ keyPath, Int64 value);

            virtual VoidResult SetValueAsStream(String^ keyPath, IAimpStream^ stream);

            virtual VoidResult SetValueAsString(String^ keyPath, String^ value);
        protected:
            IAIMPServiceConfig* GetAimpService() override;
        };
    }
}
