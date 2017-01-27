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
