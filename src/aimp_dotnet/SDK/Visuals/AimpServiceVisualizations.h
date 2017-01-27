#pragma once

class AimpServiceVisualizations : public IUnknownInterfaceImpl<IAIMPServiceVisualizations>
{
public:
    typedef IUnknownInterfaceImpl<IAIMPServiceVisualizations> Base;

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
