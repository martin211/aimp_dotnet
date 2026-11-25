#pragma once

#include <apiTypes.h>

//! Helper implements IUnknown interface.
template <typename T>
class IUnknownImpl : public T
{
private:
    DWORD counter;
public:
    IUnknownImpl(): counter(0) {}

    virtual ~IUnknownImpl() {}

    virtual BOOL isOurRIID(REFIID riid) 
    {
        return false;        
    }

    virtual DWORD __unknwncall AddRef(void)
    { 
        return ++counter; 
    }

    virtual DWORD __unknwncall Release(void) 
    {
        DWORD reference_count = --counter;
        if (reference_count == 0)
            delete this;
        return reference_count;
    }

    virtual HRESULT __unknwncall QueryInterface(REFIID riid, LPVOID* ppvObj)
    {
        if (!ppvObj)
            return E_POINTER;

        if (EqualGUID(IID_IUnknown, riid) || isOurRIID(riid))
        {
            *ppvObj = this;
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }
};

template <typename Y, typename T>
class ISubInterfaceImpl : public T
{
protected:
    Y* owner;
public:
    ISubInterfaceImpl(Y* owner) : owner(owner) {}

    virtual DWORD __unknwncall AddRef()
    {
        return owner->AddRef();
    }

    virtual DWORD __unknwncall Release()
    {
        return owner->Release();
    }

    virtual HRESULT __unknwncall QueryInterface(REFIID riid, LPVOID* ppvObj)
    {
        return owner->QueryInterface(riid, ppvObj);
    }
};
