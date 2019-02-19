// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once

class AimpExtension
{
protected:
    IAIMPCore *_aimpCore;
public:
    AimpExtension(IAIMPCore* aimpCore)
    {
        _aimpCore = aimpCore;
    }
};

class OptionsDialogFrameExtension :
    public IUnknownInterfaceImpl<IAIMPOptionsDialogFrame>, 
    public IAIMPOptionsDialogFrameKeyboardHelper, 
    public AimpExtension
{
public:
    typedef IUnknownInterfaceImpl<IAIMPOptionsDialogFrame> Base;

private:
    gcroot<AIMP::SDK::Options::IAimpOptionsDialogFrame^> _managedFrame;
public:
    explicit OptionsDialogFrameExtension(IAIMPCore* aimpCore, gcroot<AIMP::SDK::Options::IAimpOptionsDialogFrame^> managedFrame);

    GUID ExtensionId();

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI GetName(IAIMPString** S);

    virtual HWND WINAPI CreateFrame(HWND ParentWnd);

    virtual void WINAPI DestroyFrame();

    virtual void WINAPI Notification(int ID);

    virtual BOOL WINAPI DialogChar(WCHAR CharCode, int Unused);

    virtual BOOL WINAPI DialogKey(WORD CharCode, int Unused);

    virtual BOOL WINAPI SelectFirstControl();

    virtual BOOL WINAPI SelectNextControl(BOOL FindForward, BOOL CheckTabStop);
};
