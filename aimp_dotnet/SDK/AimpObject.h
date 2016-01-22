﻿#pragma once

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
        //((IUnknown*)_aimpObject)->Release();
        //_aimpObject = nullptr;
        _aimpObject = NULL;
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
