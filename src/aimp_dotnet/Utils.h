// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once

public ref class Utils
{
internal:
	static AIMP::SDK::AimpActionResult CheckResult(HRESULT result)
	{
#ifdef _DEBUG
        if (result != S_OK)
            System::Diagnostics::Debugger::Break();
#endif

		switch (result)
		{
		case E_ACCESSDENIED:
			return AIMP::SDK::AimpActionResult::AccessDenied;
		case E_HANDLE:
			return AIMP::SDK::AimpActionResult::Handle;
		case E_INVALIDARG:
			return AIMP::SDK::AimpActionResult::InvalidArguments;
		case E_NOTIMPL:
			return AIMP::SDK::AimpActionResult::NotImplemented;
		case E_UNEXPECTED:
			return AIMP::SDK::AimpActionResult::Unexpected;
		case E_FAIL:
			return AIMP::SDK::AimpActionResult::Fail;
		}

		return AIMP::SDK::AimpActionResult::Ok;
	}
};
