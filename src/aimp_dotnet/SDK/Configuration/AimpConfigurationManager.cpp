#include "Stdafx.h"
#include "AimpConfigurationManager.h"

AIMP::SDK::AimpConfigurationManager::AimpConfigurationManager(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceConfig>(core)
{
}

AIMP::SDK::AimpConfigurationManager::~AimpConfigurationManager()
{
}

void AIMP::SDK::AimpConfigurationManager::Delete(String^ key)
{
    IAIMPServiceConfig* service = NULL;
    IAIMPString *s = NULL;
    try
    {
        if (GetService(IID_IAIMPServiceConfig, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                s = AimpConverter::ToAimpString(key);
                service->Delete(s);
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }

        if (s != NULL)
        {
            s->Release();
            s = NULL;
        }
    }
}

void AIMP::SDK::AimpConfigurationManager::FlushCache()
{
    IAIMPServiceConfig* service = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceConfig, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                service->FlushCache();
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }
    }
}

double AIMP::SDK::AimpConfigurationManager::GetValueAsFloat(String^ key)
{
    IAIMPServiceConfig* service = NULL;
    IAIMPString *s = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceConfig, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                double value = 0;
                s = AimpConverter::ToAimpString(key);
                service->GetValueAsFloat(s, &value);
                return value;
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }

        if (s != NULL)
        {
            s->Release();
            s = NULL;
        }
    }

    return 0;
}

int AIMP::SDK::AimpConfigurationManager::GetValueAsInt32(String^ key)
{
    IAIMPServiceConfig* service = NULL;
    IAIMPString *s = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceConfig, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                int value = 0;
                s = AimpConverter::ToAimpString(key);
                service->GetValueAsInt32(s, &value);
                return value;
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }

        if (s != NULL)
        {
            s->Release();
            s = NULL;
        }
    }

    return 0;
}

System::Int64 AIMP::SDK::AimpConfigurationManager::GetValueAsInt64(String^ key)
{
    IAIMPServiceConfig* service = NULL;
    IAIMPString *s = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceConfig, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                Int64 value = 0;
                s = AimpConverter::ToAimpString(key);
                service->GetValueAsInt64(s, &value);
                return value;
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }

        if (s != NULL)
        {
            s->Release();
            s = NULL;
        }
    }

    return 0;
}

System::IO::Stream^ AIMP::SDK::AimpConfigurationManager::GetValueAsStream(String^ key)
{
    // TODO: Complete it. What it should be, some array of bytes?
    return nullptr;
}

System::String^ AIMP::SDK::AimpConfigurationManager::GetValueAsString(String^ key)
{
    IAIMPServiceConfig* service = NULL;
    IAIMPString *s = NULL;
    IAIMPString* val = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceConfig, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                s = AimpConverter::ToAimpString(key);
                service->GetValueAsString(s, &val);
                return gcnew String(val->GetData());
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }

        if (s != NULL)
        {
            s->Release();
            s = NULL;
        }

        if (val != NULL)
        {
            val->Release();
            val = NULL;
        }
    }

    return String::Empty;
}

void AIMP::SDK::AimpConfigurationManager::SetValueAsFloat(String^ key, double value)
{
    IAIMPServiceConfig* service = NULL;
    IAIMPString *s = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceConfig, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                s = AimpConverter::ToAimpString(key);
                service->SetValueAsFloat(s, value);
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }

        if (s != NULL)
        {
            s->Release();
            s = NULL;
        }
    }
}

void AIMP::SDK::AimpConfigurationManager::SetValueAsInt32(String^ key, int value)
{
    IAIMPServiceConfig* service = NULL;
    IAIMPString *s = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceConfig, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                s = AimpConverter::ToAimpString(key);
                service->SetValueAsInt32(s, value);
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }

        if (s != NULL)
        {
            s->Release();
            s = NULL;
        }
    }
}

void AIMP::SDK::AimpConfigurationManager::SetValueAsInt64(String^ key, Int64 value)
{
    IAIMPServiceConfig* service = NULL;
    IAIMPString *s = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceConfig, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                s = AimpConverter::ToAimpString(key);
                service->SetValueAsInt64(s, value);
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }

        if (s != NULL)
        {
            s->Release();
            s = NULL;
        }
    }
}

void AIMP::SDK::AimpConfigurationManager::SetValueAsStream(String^ key, System::IO::Stream^ value)
{
    // TODO: Complete it. What it should be, some array of bytes?
    //_service->SetValueAsStream(key, value);
}

void AIMP::SDK::AimpConfigurationManager::SetValueAsString(String^ key, String^ value)
{
    IAIMPServiceConfig* service = NULL;
    IAIMPString *s = NULL;
    IAIMPString *val = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceConfig, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                s = AimpConverter::ToAimpString(key);
                val = AimpConverter::ToAimpString(value);
                service->SetValueAsString(s, val);
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }

        if (s != NULL)
        {
            s->Release();
            s = NULL;
        }

        if (val != NULL)
        {
            val->Release();
            val = NULL;
        }
    }
}
