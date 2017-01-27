/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 */
#pragma once

class AimpServiceVisualizations : public IUnknownInterfaceImpl<IAIMPServiceVisualizations>
{
public:
    typedef IUnknownInterfaceImpl<IAIMPServiceVisualizations> Base;

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};
