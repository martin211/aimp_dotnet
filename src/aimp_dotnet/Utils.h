/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 */
 
#pragma once

public ref class Utils
{
internal:
	static AIMP::SDK::AimpActionResult CheckResult(HRESULT result)
	{
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
