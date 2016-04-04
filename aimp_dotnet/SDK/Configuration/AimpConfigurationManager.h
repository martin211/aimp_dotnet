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
            explicit AimpConfigurationManager(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceConfig>(core)
            {
                IAIMPServiceConfig* service;
                core->GetService(IID_IAIMPServiceConfig, (void**)&service);
                _service = service;
            }

            ~AimpConfigurationManager()
            {
                _service->Release();
            }

            virtual void Delete(String^ key)
            {
                IAIMPString *s = AimpConverter::GetAimpString(key);
                _service->Delete(s);
                s->Release();
            }

            virtual void FlushCache()
            {
                CheckResult(_service->FlushCache());
            }

            virtual double GetValueAsFloat(String^ key)
            {
                double value;
                IAIMPString *s = AimpConverter::GetAimpString(key);
                CheckResult(_service->GetValueAsFloat(s, &value));
                s->Release();
                return value;
            }

            virtual int GetValueAsInt32(String^ key)
            {
                int value;
                IAIMPString *s = AimpConverter::GetAimpString(key);
                CheckResult(_service->GetValueAsInt32(s, &value));
                s->Release();
                return value;
            }

            virtual Int64 GetValueAsInt64(String^ key)
            {
                Int64 value;
                IAIMPString *s = AimpConverter::GetAimpString(key);
                CheckResult(_service->GetValueAsInt64(s, &value));
                s->Release();
                return value;
            }

            virtual System::IO::Stream^ GetValueAsStream(String^ key)
            {
                // TODO: Complete it. What it should be, some array of bytes?
                return nullptr;
            }

            virtual String^ GetValueAsString(String^ key)
            {
                IAIMPString* val = NULL;

                try
                {
                    IAIMPString *s = AimpConverter::GetAimpString(key);
                    CheckResult(_service->GetValueAsString(s, &val));
                    s->Release();
                    return gcnew String(val->GetData());
                }
                finally
                {
                    val->Release();
                    val = NULL;
                }

                return String::Empty;
            }

            virtual void SetValueAsFloat(String^ key, double value)
            {
                IAIMPString *s = AimpConverter::GetAimpString(key);
                CheckResult(_service->SetValueAsFloat(s, value));
                s->Release();
            }

            virtual void SetValueAsInt32(String^ key, int value)
            {
                IAIMPString *s = AimpConverter::GetAimpString(key);
                CheckResult(_service->SetValueAsInt32(s, value));
                s->Release();
            }

            virtual void SetValueAsInt64(String^ key, Int64 value)
            {
                IAIMPString *s = AimpConverter::GetAimpString(key);
                CheckResult(_service->SetValueAsInt64(s, value));
                s->Release();
            }

            virtual void SetValueAsStream(String^ key, System::IO::Stream^ value)
            {
                // TODO: Complete it. What it should be, some array of bytes?
                //_service->SetValueAsStream(key, value);
            }

            virtual void SetValueAsString(String^ key, String^ value)
            {
                IAIMPString *s = AimpConverter::GetAimpString(key);
                IAIMPString *sValue = AimpConverter::GetAimpString(value);
                CheckResult(_service->SetValueAsString(s, sValue));
                s->Release();
                sValue->Release();
            }

        private:
            IAIMPServiceConfig* _service;
        };
    }
}