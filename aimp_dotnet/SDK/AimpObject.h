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
	AIMP::SDK::AimpActionResult CheckResult(HRESULT result)
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

template <class TAimpObject>
public ref class AimpGuiObject : AimpObject<TAimpObject>
{
protected:
    TAimpObject *_aimpObject;
    IAIMPServiceUI *_service;
public:
    explicit AimpGuiObject(IAIMPServiceUI *service, TAimpObject *aimpObject) : AimpObject<TAimpObject>(aimpObject)
    {
        _service = service;
    }
    internal:
        property IAIMPServiceUI *AimpServiceUI
        {
            IAIMPServiceUI *get()
            {
                return _service;
            }
        }
};

template <class TAimpInterface>
interface class IAimpObject
{
    property TAimpInterface *AimpObject
    {
        TAimpInterface *get();
        void set(TAimpInterface *value);
    }
};
