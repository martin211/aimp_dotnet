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
        System::Diagnostics::Debug::WriteLineIf(result != S_OK, "CheckResult: " + result);

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
