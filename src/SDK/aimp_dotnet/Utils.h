//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

public ref class Utils
{
internal:
    static ActionResultType CheckResult(HRESULT result)
    {
        switch (result)
        {
        case S_OK:
            return ActionResultType::OK;
        case E_ACCESSDENIED:
            return ActionResultType::AccessDenied;
        case E_HANDLE:
            return ActionResultType::Handle;
        case E_INVALIDARG:
            return ActionResultType::InvalidArguments;
        case E_NOTIMPL:
            return ActionResultType::NotImplemented;
        case E_UNEXPECTED:
            return ActionResultType::Unexpected;
        case E_FAIL:
            return ActionResultType::Fail;
        case E_NOINTERFACE:
            return ActionResultType::NoInterface;
        default:
            return ActionResultType::Unexpected;
        }
    }
};

private ref class Assert
{
internal:
    static void NotNull(System::String^ value, System::String^ field)
    {
        if (System::String::IsNullOrEmpty(value))
        {
            ARGUMENT_NULL(field, field)
        }
    }

    static void NotNull(System::Collections::IEnumerable^ value, System::String^ field)
    {
        if (value == nullptr || !value->GetEnumerator()->MoveNext())
        {
            ARGUMENT_NULL(field, field)
        }
    }

    static void NotNull(System::Object^ object, System::String^ field)
    {
        if (object == nullptr)
        {
            ARGUMENT_NULL(field, field)
        }
    }
};
