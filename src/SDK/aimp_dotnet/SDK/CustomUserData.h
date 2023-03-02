//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

public class CustomUserData : IUnknownInterfaceImpl<IUnknown> {
private:
    gcroot<Object^> _customObjectHandle;
public:
    gcroot<Object^> CustomObject() {
        return _customObjectHandle;
    }

    explicit CustomUserData(gcroot<Object^> data)
        : _customObjectHandle(data) {
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject) {
        return IUnknownInterfaceImpl::QueryInterface(riid, ppvObject);
    }

    virtual ULONG WINAPI AddRef(void) {
        return IUnknownInterfaceImpl::AddRef();
    }

    virtual ULONG WINAPI Release(void) {
        return IUnknownInterfaceImpl::Release();
    }
};