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

public ref class Utils
{
internal:
    static AIMP::SDK::ActionResultType CheckResult(HRESULT result)
    {
        switch (result)
        {
        case E_ACCESSDENIED:
            return AIMP::SDK::ActionResultType::AccessDenied;
        case E_HANDLE:
            return AIMP::SDK::ActionResultType::Handle;
        case E_INVALIDARG:
            return AIMP::SDK::ActionResultType::InvalidArguments;
        case E_NOTIMPL:
            return AIMP::SDK::ActionResultType::NotImplemented;
        case E_UNEXPECTED:
            return AIMP::SDK::ActionResultType::Unexpected;
        case E_FAIL:
            return AIMP::SDK::ActionResultType::Fail;
        }

        return AIMP::SDK::ActionResultType::OK;
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
};
