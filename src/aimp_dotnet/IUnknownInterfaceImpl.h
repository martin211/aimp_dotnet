/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#pragma once

#include <Unknwn.h>
#ifdef _DEBUG
#include <atlbase.h>
#endif

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
#ifdef _DEBUG
        CComBSTR guidBstr(riid);
        System::Diagnostics::Debug::WriteLine("QueryInterface: " + gcnew System::String(guidBstr));
#endif

        return E_NOTIMPL;
    }

    virtual ULONG WINAPI AddRef(void)
    {
        _LinkCounter++;
        return _LinkCounter;
    }

    virtual ULONG WINAPI Release(void) 
    {
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
