#pragma once
#include "..\..\AimpSdk.h"
#include "AimpServiceSynchronizer.h"
#include "AimpTaskOwner.h"

class InternalAimpTask : public IUnknownInterfaceImpl<IAIMPTask>
{
private:
    gcroot<AIMP::SDK::Threading::IAimpTask^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPTask> Base;

    InternalAimpTask(gcroot<AIMP::SDK::Threading::IAimpTask^> instance)
    {
        _instance = instance;
    }

    virtual void WINAPI Execute(IAIMPTaskOwner* Owner)
    {
        AimpTaskOwner ^owner = gcnew AimpTaskOwner(Owner);
        _instance->Execute(owner);
    }

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (riid == IID_IAIMPTask)
        {
            *ppvObject = this;
            return S_OK;
        }

        return E_NOTIMPL;
    }
};
