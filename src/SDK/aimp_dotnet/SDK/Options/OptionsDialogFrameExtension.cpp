//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "OptionsDialogFrameExtension.h"

using namespace AIMP::SDK;

OptionsDialogFrameExtension::OptionsDialogFrameExtension(IAIMPCore* aimpCore, gcroot<Options::IAimpOptionsDialogFrame^> managedFrame) :
    AimpExtension(aimpCore) {
    _managedFrame = managedFrame;
}

GUID OptionsDialogFrameExtension::ExtensionId() {
    return IID_IAIMPServiceOptionsDialog;
}

HRESULT WINAPI OptionsDialogFrameExtension::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPOptionsDialogFrame) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPOptionsDialogFrameKeyboardHelper) {
        *ppvObject = dynamic_cast<IAIMPOptionsDialogFrameKeyboardHelper*>(this);
        AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPOptionsDialogFrameKeyboardHelper2) {
        *ppvObject = static_cast<IAIMPOptionsDialogFrameKeyboardHelper2*>(this);
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}

ULONG WINAPI OptionsDialogFrameExtension::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI OptionsDialogFrameExtension::Release(void) {
    return Base::Release();
}

HRESULT WINAPI OptionsDialogFrameExtension::GetName(IAIMPString** S) {
    String^ str = _managedFrame->GetName();
    *S = AimpConverter::ToAimpString(str);
    return S_OK;
}

HWND WINAPI OptionsDialogFrameExtension::CreateFrame(HWND ParentWnd) {
    IntPtr parentWindow(ParentWnd);
    auto childWindow = _managedFrame->CreateFrame(parentWindow);
    return HWND(childWindow.ToPointer());
}

void WINAPI OptionsDialogFrameExtension::DestroyFrame() {
    _managedFrame->DestroyFrame();
}

void WINAPI OptionsDialogFrameExtension::Notification(int ID) {
    _managedFrame->Notification(static_cast<Options::OptionsDialogFrameNotificationType>(ID));
}

BOOL WINAPI OptionsDialogFrameExtension::DialogKey(WORD charCode, int unused) {
    Object^ obj = _managedFrame;
    Options::IAimpOptionsDialogFrameKeyboardHelper2^ helper = dynamic_cast<Options::IAimpOptionsDialogFrameKeyboardHelper2^>(obj);
    if (helper != nullptr) {
        return helper->DialogKey(charCode);
    }

    return false;
}

BOOL WINAPI OptionsDialogFrameExtension::SelectFirstControl() {
    Object^ obj = _managedFrame;
    Options::IAimpOptionsDialogFrameKeyboardHelper2^ helper = dynamic_cast<Options::IAimpOptionsDialogFrameKeyboardHelper2^>(obj);
    if (helper != nullptr) {
        return helper->SelectFirstControl();
    }

    return false;
}

BOOL WINAPI OptionsDialogFrameExtension::SelectNextControl(BOOL findForward, BOOL checkTabStop) {
    Object^ obj = _managedFrame;
    Options::IAimpOptionsDialogFrameKeyboardHelper2^ helper = dynamic_cast<Options::IAimpOptionsDialogFrameKeyboardHelper2^>(obj);

    if (helper != nullptr) {
        return helper->SelectNextControl(findForward, checkTabStop);
    }

    return false;
}

BOOL OptionsDialogFrameExtension::SelectLastControl() {
    Object^ obj = _managedFrame;
    Options::IAimpOptionsDialogFrameKeyboardHelper2^ helper = dynamic_cast<Options::IAimpOptionsDialogFrameKeyboardHelper2^>(obj);

    if (helper != nullptr) {
        return helper->SelectLastControl();
    }

    return false;
}
