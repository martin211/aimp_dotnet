#pragma once

template<class TAimpObject>
public ref class AimpObject
{
protected:
	AimpObject() {}
	TAimpObject *_aimpObject;
public:
	AimpObject(TAimpObject *aimpObject) : _aimpObject(aimpObject)
	{
	}

	~AimpObject()
	{
		((IUnknown*)_aimpObject)->Release();
		delete _aimpObject;
	}
protected:
	AIMP::SDK::Services::AimpActionResult CheckResult(HRESULT result)
	{
		return Utils::CheckResult(result);
	}
internal:
	property TAimpObject *InternalAimpObject
	{
		TAimpObject *get()
		{
			return _aimpObject;
		}
	}
};