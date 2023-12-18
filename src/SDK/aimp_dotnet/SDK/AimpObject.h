//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include <msclr\marshal_cppstd.h>

#include "AimpLogger.h"
#include <windows.h>
#include <iostream>

template <class TAimpObject>
public ref class AimpObject : public IAimpObject {
private:
    bool _isDisposable;
protected:
    AimpObject() {
    }

    [System::Diagnostics::DebuggerBrowsableAttribute(System::Diagnostics::DebuggerBrowsableState::Never)]
    TAimpObject* _aimpObject;
public:
    AimpObject(TAimpObject* aimpObject, bool registerAtMemoryManager) : _aimpObject(aimpObject) {
        _isDisposable = registerAtMemoryManager;
        RegisterAtMemoryManager();
    }

    AimpObject(TAimpObject* aimpObject) : AimpObject(aimpObject, false) {
        RegisterAtMemoryManager();
    }

    !AimpObject() {
        FreeResources();
        ReleaseFromMemoryManager();
    }

    ~AimpObject() {
        this->!AimpObject();
    }

protected:
    ActionResultType CheckResult(HRESULT result) {
        return Utils::CheckResult(result);
    }

    virtual void FreeResources() {

    }

    virtual void RegisterAtMemoryManager() {
        if (ComObject == nullptr)
            return;

        ComObject->AddRef();
        if (_isDisposable && InternalAimpObject != nullptr) {
            AimpMemoryManager::getInstance().AddObject(this->GetHashCode(), InternalAimpObject, msclr::interop::marshal_as<std::string>(this->ToString()));
        }
        AimpLogger::Logger->Debug(String::Format("Register object: {0}. Type: {1}. Register at MM: {2}", this->GetHashCode(), this->ToString(), _isDisposable));
        AimpLogger::Logger->Verbose(System::Environment::StackTrace);
    }

    static int Filter(unsigned int code) {
        if (code == EXCEPTION_ACCESS_VIOLATION) {
            AimpLogger::Logger->Error("Access violation exception");
            AimpLogger::Logger->Error(System::Environment::StackTrace);
            return EXCEPTION_EXECUTE_HANDLER;
        }

        return EXCEPTION_CONTINUE_SEARCH;
    }

    virtual void ReleaseFromMemoryManager() {
        AimpLogger::Logger->Debug(String::Format("Release object: {0}", this->GetHashCode()));
        if (InternalAimpObject != nullptr) {
            ComObject->Release();
        }

        if (_isDisposable) {
            __try {
                AimpMemoryManager::getInstance().Release(this->GetHashCode());
            }
            __except (Filter(GetExceptionCode())) {
                AimpLogger::Logger->Error("Error to Release object " + this->GetHashCode());
                AimpLogger::Logger->Error(System::Environment::StackTrace);
            }
        }
        AimpLogger::Logger->Verbose(System::Environment::StackTrace);
    }

public:
    property IUnknown* ComObject {
        IUnknown* get() {
            return safe_cast<IUnknown*>(InternalAimpObject);
        }
    }

    property TAimpObject* InternalAimpObject
    {
        TAimpObject* get() {
            return _aimpObject;
        }
    }
};
