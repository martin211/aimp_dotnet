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
#include "AimpConfig.h"

using namespace AIMP::SDK;

AimpConfig::AimpConfig(IAIMPConfig* aimpPlayList) : AimpObject(aimpPlayList)
{
}

ActionResultType AimpConfig::Delete(String^ keyPath)
{
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;

    try
    {
        str = AimpConverter::ToAimpString(keyPath);
        result = CheckResult(InternalAimpObject->Delete(str));
    }
    finally
    {
        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return result;
}

float AimpConfig::GetValueAsFloat(String^ keyPath)
{
    IAIMPString* str = nullptr;
    double val = 0;

    try
    {
        str = AimpConverter::ToAimpString(keyPath);
        InternalAimpObject->GetValueAsFloat(str, &val);
    }
    finally
    {
        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return val;
}

int AimpConfig::GetValueAsInt32(String^ keyPath)
{
    IAIMPString* str = nullptr;
    int val = 0;

    try
    {
        str = AimpConverter::ToAimpString(keyPath);
        InternalAimpObject->GetValueAsInt32(str, &val);
    }
    finally
    {
        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return val;
}

Int64 AimpConfig::GetValueAsInt64(String^ keyPath)
{
    IAIMPString* str = nullptr;
    Int64 val = 0;

    try
    {
        str = AimpConverter::ToAimpString(keyPath);
        InternalAimpObject->GetValueAsInt64(str, &val);
    }
    finally
    {
        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return val;
}

IAimpStream^ AimpConfig::GetValueAsStream(String^ keyPath)
{
    IAIMPString* str = nullptr;
    IAIMPStream* stream = nullptr;
    try
    {
        str = AimpConverter::ToAimpString(keyPath);
        if (CheckResult(InternalAimpObject->GetValueAsStream(str, &stream)) == ActionResultType::OK && stream != nullptr
        )
        {
            return gcnew AimpStream(stream);
        }
    }
    finally
    {
        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return nullptr;
}

String^ AimpConfig::GetValueAsString(String^ keyPath)
{
    IAIMPString* str = nullptr;
    IAIMPString* val = nullptr;

    try
    {
        str = AimpConverter::ToAimpString(keyPath);
        if (CheckResult(InternalAimpObject->GetValueAsString(str, &val)) == ActionResultType::OK && val != nullptr)
        {
            return gcnew String(val->GetData());
        }
    }
    finally
    {
        // TODO Release val?
        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return String::Empty;
}

ActionResultType AimpConfig::SetValueAsFloat(String^ keyPath, float value)
{
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;

    try
    {
        str = AimpConverter::ToAimpString(keyPath);
        result = CheckResult(InternalAimpObject->SetValueAsFloat(str, value));
    }
    finally
    {
        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return result;
}

ActionResultType AimpConfig::SetValueAsInt32(String^ keyPath, int value)
{
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;

    try
    {
        str = AimpConverter::ToAimpString(keyPath);
        result = CheckResult(InternalAimpObject->SetValueAsInt32(str, value));
    }
    finally
    {
        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return result;
}

ActionResultType AimpConfig::SetValueAsInt64(String^ keyPath, Int64 value)
{
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;

    try
    {
        str = AimpConverter::ToAimpString(keyPath);
        result = CheckResult(InternalAimpObject->SetValueAsInt64(str, value));
    }
    finally
    {
        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return result;
}

ActionResultType AimpConfig::SetValueAsStream(String^ keyPath, IAimpStream^ stream)
{
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;

    try
    {
        str = AimpConverter::ToAimpString(keyPath);
        result = CheckResult(
            InternalAimpObject->SetValueAsStream(str, static_cast<AimpStream^>(stream)->InternalAimpObject));
    }
    finally
    {
        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return result;
}

ActionResultType AimpConfig::SetValueAsString(String^ keyPath, String^ value)
{
    IAIMPString* str = nullptr;
    IAIMPString* val = nullptr;
    auto result = ActionResultType::Fail;

    try
    {
        str = AimpConverter::ToAimpString(keyPath);
        val = AimpConverter::ToAimpString(value);
        result = CheckResult(InternalAimpObject->SetValueAsString(str, val));
    }
    finally
    {
        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }

        if (val != nullptr)
        {
            val->Release();
            val = nullptr;
        }
    }

    return result;
}
