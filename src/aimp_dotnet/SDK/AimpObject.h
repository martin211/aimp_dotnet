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

template<class TAimpObject>
public interface class IAimpObject
{
    AIMP::SDK::AimpActionResult CheckResult(HRESULT result);

    [System::Diagnostics::DebuggerBrowsableAttribute(System::Diagnostics::DebuggerBrowsableState::Never)]
    property TAimpObject *InternalAimpObject
    {
        TAimpObject *get();
    }
};

template<class TAimpObject>
public ref class AimpObject 
{
protected:
    AimpObject() {}

    [System::Diagnostics::DebuggerBrowsableAttribute(System::Diagnostics::DebuggerBrowsableState::Never)]
    TAimpObject *_aimpObject;
public:
    AimpObject(TAimpObject *aimpObject) : _aimpObject(aimpObject)
    {
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
