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

class AimpExtension
{
protected:
    IAIMPCore *_aimpCore;
public:
    AimpExtension(IAIMPCore *aimpCore)
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
    explicit OptionsDialogFrameExtension(IAIMPCore *aimpCore, gcroot<AIMP::SDK::Options::IAimpOptionsDialogFrame^> managedFrame);

    GUID ExtensionId();

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI GetName(IAIMPString **S);

    virtual HWND WINAPI CreateFrame(HWND ParentWnd);

    virtual void WINAPI DestroyFrame();

    virtual void WINAPI Notification(int ID);

    virtual BOOL WINAPI DialogChar(WCHAR CharCode, int Unused);

    virtual BOOL WINAPI DialogKey(WORD CharCode, int Unused);

    virtual BOOL WINAPI SelectFirstControl();

    virtual BOOL WINAPI SelectNextControl(BOOL FindForward, BOOL CheckTabStop);
};
