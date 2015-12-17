#pragma once

#include <Unknwn.h>

//! Helper implements IUnknown interface.
template <typename T>
class IUnknownInterfaceImpl : public T
{
public:

    IUnknownInterfaceImpl()        
    {
		_LinkCounter = 1;
	}

    virtual ~IUnknownInterfaceImpl() {}

	virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject) 
	{
		if (riid == IID_IUnknown)
		{
			return S_OK;
		}
		return E_NOTIMPL;
    }

    virtual ULONG WINAPI AddRef(void)
    { 
		_LinkCounter++;
		return _LinkCounter;
	}

    virtual ULONG WINAPI Release(void) {
		_LinkCounter--;

		if (_LinkCounter == 0) {
            delete this;
			return 0;
        }

		return _LinkCounter;
    }

private:

	ULONG _LinkCounter;
};