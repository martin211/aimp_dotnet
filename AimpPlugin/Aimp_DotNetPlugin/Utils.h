#pragma once

public ref class Utils
{
internal:
	static AIMP::SDK::Services::AimpActionResult CheckResult(HRESULT result)
	{
		switch (result)
		{
		case E_ACCESSDENIED:
			return AIMP::SDK::Services::AimpActionResult::AccessDenied;
		case E_HANDLE:
			return AIMP::SDK::Services::AimpActionResult::Handle;
		case E_INVALIDARG:
			return AIMP::SDK::Services::AimpActionResult::InvalidArguments;
		case E_NOTIMPL:
			return AIMP::SDK::Services::AimpActionResult::NotImplemented;
		case E_UNEXPECTED:
			return AIMP::SDK::Services::AimpActionResult::Unexpected;
		case E_FAIL:
			return AIMP::SDK::Services::AimpActionResult::Fail;
		}

		return AIMP::SDK::Services::AimpActionResult::Ok;
	}
};
