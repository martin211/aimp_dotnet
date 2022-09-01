//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

template <typename T>
class IUnknownInterfaceImpl : public T
{
public:

    IUnknownInterfaceImpl()
    {
        _LinkCounter = 1;
    }

    virtual ~IUnknownInterfaceImpl()
    {
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
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

        if (_LinkCounter == 0)
        {
            delete this;
            return 0;
        }

        return _LinkCounter;
    }

private:
    ULONG _LinkCounter;
};
