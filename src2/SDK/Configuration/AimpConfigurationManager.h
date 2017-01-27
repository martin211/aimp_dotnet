/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 */
#pragma once

#include "..\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::ConfigurationManager;

        public ref class AimpConfigurationManager : public AimpBaseManager<IAIMPServiceConfig>, public IAimpConfigurationManager
        {
        public:
            explicit AimpConfigurationManager(ManagedAimpCore^ core);

            ~AimpConfigurationManager();

            virtual void Delete(String^ key);

            virtual void FlushCache();

            virtual double GetValueAsFloat(String^ key);

            virtual int GetValueAsInt32(String^ key);

            virtual Int64 GetValueAsInt64(String^ key);

            virtual System::IO::Stream^ GetValueAsStream(String^ key);

            virtual String^ GetValueAsString(String^ key);

            virtual void SetValueAsFloat(String^ key, double value);

            virtual void SetValueAsInt32(String^ key, int value);

            virtual void SetValueAsInt64(String^ key, Int64 value);

            virtual void SetValueAsStream(String^ key, System::IO::Stream^ value);

            virtual void SetValueAsString(String^ key, String^ value);
        };
    }
}
