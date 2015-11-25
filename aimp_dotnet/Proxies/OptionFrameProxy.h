#pragma once
#include <gcroot.h>
#include "AimpPlayer.h"
#include "ObjectHelper.h"
#include "InternalLogger.h"

class OptionFrameProxy : public IUnknownInterfaceImpl<IAIMPOptionsDialogFrame>
{
private:    
    gcroot<AimpOptionsDialogFrame^> _optionsDialogFrame;
    IUnknown* _proxyPlugin;
public:
    OptionFrameProxy(IUnknown* proxyPlugin)
    {
        _proxyPlugin = proxyPlugin;
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        return _proxyPlugin->QueryInterface(riid, ppvObject);
    }

    virtual ULONG WINAPI AddRef(void)
    {
        return _proxyPlugin->AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return _proxyPlugin->Release();
    }

    virtual HRESULT WINAPI GetName(IAIMPString **S)
    {
        return S_OK;
    }

    virtual HWND WINAPI CreateFrame(HWND ParentWnd)
    {

        return 0;
    }

    virtual void WINAPI DestroyFrame()
    {
    }

    virtual void WINAPI Notification(int ID)
    {
    }

    void NotifyPlayer()
    {

    }
};

