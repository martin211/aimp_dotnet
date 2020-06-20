// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

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
        RegisterAtMemoryManager();
    }

    !AimpObject()
    {
        FreeResources();
        ReleaseFromMemoryManager();
    }

    ~AimpObject()
    {
        this->!AimpObject();
    }
protected:
    ActionResultType CheckResult(HRESULT result)
    {
        return Utils::CheckResult(result);
    }

    virtual void FreeResources()
    {
        
    }

    virtual void RegisterAtMemoryManager()
    {
        AimpMemoryManager::getInstance().AddObject(this->GetHashCode(), InternalAimpObject);
    }

    virtual void ReleaseFromMemoryManager()
    {
        AimpMemoryManager::getInstance().Release(this->GetHashCode());
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
