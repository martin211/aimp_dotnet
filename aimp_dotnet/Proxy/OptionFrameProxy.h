#pragma once


#include "AIMP_SDK/IUnknownInterfaceImpl.h"


class OptionFrameProxy : public IUnknownInterfaceImpl<IAIMPOptionsDialogFrame>
{
private:
    //gcroot<AIMP::SDK::Services::Options::IAimpOptionsDialogFrame^> _managedFrame;
    IUnknown* _proxyPlugin;

public:
    OptionFrameProxy(IUnknown* proxyPlugin
        //, gcroot<AIMP::SDK::Services::Options::IAimpOptionsDialogFrame^> optionFrame
        )
    {
        _proxyPlugin = proxyPlugin;
        //_managedFrame = optionFrame;
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
        String ^name = _managedFrame->GetName();
        //IAIMPString *Str = AIMP::ObjectHelper::MakeAimpString(_core->GetAimpCore(), name);
        return S_OK;
    }

    virtual HWND WINAPI CreateFrame(HWND ParentWnd)
    {
        //IntPtr parent(ParentWnd);
        //IntPtr framePtr = _managedFrame->CreateFrame(parent);
        //return (HWND)framePtr.ToPointer();
        return 0;
    }

    virtual void WINAPI DestroyFrame()
    {
        //_managedFrame->DestroyFrame();
    }

    virtual void WINAPI Notification(int ID)
    {

    }

    void NotifyPlayer()
    {

    }
};
