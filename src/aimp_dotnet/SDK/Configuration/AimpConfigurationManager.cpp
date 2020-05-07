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

#include "Stdafx.h"
#include "AimpConfigurationManager.h"

AimpServiceConfig::AimpServiceConfig(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceConfig>(core)
{
}

AimpServiceConfig::~AimpServiceConfig()
{
}

ActionResultType AimpServiceConfig::FlushCache()
{
    IAIMPServiceConfig* service = GetAimpService();

    try
    {
        if (service != nullptr)
        {
            return CheckResult(service->FlushCache());
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return ActionResultType::Fail;
}

ActionResultType AimpServiceConfig::Delete(String^ keyPath)
{
    IAIMPString* str = nullptr;
    IAIMPServiceConfig* service = GetAimpService();
    auto result = ActionResultType::Fail;

    try
    {
        if (service != nullptr)
        {
            str = AimpConverter::ToAimpString(keyPath);
            result = CheckResult(service->Delete(str));
        }
    }
    finally
    {
        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }

        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return result;
}

float AimpServiceConfig::GetValueAsFloat(String^ keyPath)
{
    IAIMPString* str = nullptr;
    IAIMPServiceConfig* service = GetAimpService();
    double val = 0;

    try
    {
        str = AimpConverter::ToAimpString(keyPath);
        if (service != nullptr)
        {
            service->GetValueAsFloat(str, &val);
        }
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return val;
}

int AimpServiceConfig::GetValueAsInt32(String^ keyPath)
{
    IAIMPString* str = nullptr;
    IAIMPServiceConfig* service = GetAimpService();
    int val = 0;

    try
    {
        if (service != nullptr)
        {
            str = AimpConverter::ToAimpString(keyPath);
            service->GetValueAsInt32(str, &val);
        }
    }
    finally
    {
        ReleaseObject(str);
        ReleaseObject(service);
    }

    return val;
}

Int64 AimpServiceConfig::GetValueAsInt64(String^ keyPath)
{
    IAIMPString* str = nullptr;
    IAIMPServiceConfig* service = GetAimpService();
    Int64 val = 0;

    try
    {
        if (service != nullptr)
        {
            str = AimpConverter::ToAimpString(keyPath);
            service->GetValueAsInt64(str, &val);
        }
    }
    finally
    {
        ReleaseObject(str);
        ReleaseObject(service);
    }

    return val;
}

IAimpStream^ AimpServiceConfig::GetValueAsStream(String^ keyPath)
{
    IAIMPString* str = nullptr;
    IAIMPStream* stream = nullptr;
    IAIMPServiceConfig* service = GetAimpService();

    try
    {
        if (service != nullptr)
        {
            str = AimpConverter::ToAimpString(keyPath);
            if (CheckResult(service->GetValueAsStream(str, &stream)) == ActionResultType::OK && stream != nullptr)
            {
                return gcnew AimpStream(stream);
            }
        }
    }
    finally
    {
        ReleaseObject(str);
        ReleaseObject(service);
    }

    return nullptr;
}

String^ AimpServiceConfig::GetValueAsString(String^ keyPath)
{
    IAIMPString* str = nullptr;
    IAIMPString* val = nullptr;
    IAIMPServiceConfig* service = GetAimpService();

    try
    {
        if (service != nullptr)
        {
            str = AimpConverter::ToAimpString(keyPath);
            if (CheckResult(service->GetValueAsString(str, &val)) == ActionResultType::OK && val != nullptr)
            {
                return gcnew String(val->GetData());
            }
        }
    }
    finally
    {
        // TODO Release val?
        ReleaseObject(str);
        ReleaseObject(service);
    }

    return String::Empty;
}

ActionResultType AimpServiceConfig::SetValueAsFloat(String^ keyPath, float value)
{
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;
    IAIMPServiceConfig* service = GetAimpService();

    try
    {
        if (service != nullptr)
        {
            str = AimpConverter::ToAimpString(keyPath);
            result = CheckResult(service->SetValueAsFloat(str, value));
        }
    }
    finally
    {
        ReleaseObject(str);
        ReleaseObject(service);
    }

    return result;
}

ActionResultType AimpServiceConfig::SetValueAsInt32(String^ keyPath, int value)
{
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;
    IAIMPServiceConfig* service = GetAimpService();

    try
    {
        if (service != nullptr)
        {
            str = AimpConverter::ToAimpString(keyPath);
            result = CheckResult(service->SetValueAsInt32(str, value));
        }
    }
    finally
    {
        ReleaseObject(str);
        ReleaseObject(service);
    }

    return result;
}

ActionResultType AimpServiceConfig::SetValueAsInt64(String^ keyPath, Int64 value)
{
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;
    IAIMPServiceConfig* service = GetAimpService();

    try
    {
        if (service != nullptr)
        {
            str = AimpConverter::ToAimpString(keyPath);
            result = CheckResult(service->SetValueAsInt64(str, value));
        }
    }
    finally
    {
        ReleaseObject(str);
        ReleaseObject(service);
    }

    return result;
}

ActionResultType AimpServiceConfig::SetValueAsStream(String^ keyPath, IAimpStream^ stream)
{
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;
    IAIMPServiceConfig* service = GetAimpService();

    try
    {
        if (service != nullptr)
        {
            str = AimpConverter::ToAimpString(keyPath);
            result = CheckResult(service->SetValueAsStream(str, static_cast<AimpStream^>(stream)->InternalAimpObject));
        }
    }
    finally
    {
        ReleaseObject(str);
        ReleaseObject(service);
    }

    return result;
}

ActionResultType AimpServiceConfig::SetValueAsString(String^ keyPath, String^ value)
{
    IAIMPString* str = nullptr;
    IAIMPString* val = nullptr;
    auto result = ActionResultType::Fail;
    IAIMPServiceConfig* service = GetAimpService();

    try
    {
        if (service != nullptr)
        {
            str = AimpConverter::ToAimpString(keyPath);
            val = AimpConverter::ToAimpString(value);
            result = CheckResult(service->SetValueAsString(str, val));
        }
    }
    finally
    {
        ReleaseObject(str);
        ReleaseObject(val);
        ReleaseObject(service);
    }

    return result;
}

IAIMPServiceConfig* AimpServiceConfig::GetAimpService()
{
    IAIMPServiceConfig* service = nullptr;
    GetService(IID_IAIMPServiceConfig, &service);
    return service;
}
