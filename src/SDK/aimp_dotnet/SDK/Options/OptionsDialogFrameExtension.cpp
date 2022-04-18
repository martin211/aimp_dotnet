// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "OptionsDialogFrameExtension.h"

using namespace AIMP::SDK;

OptionsDialogFrameExtension::OptionsDialogFrameExtension(IAIMPCore* aimpCore,
                                                         gcroot<Options::IAimpOptionsDialogFrame^> managedFrame) :
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
        *ppvObject = static_cast<IAIMPOptionsDialogFrameKeyboardHelper*>(this);
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
    IAIMPString* strObject = nullptr;
    String^ str = _managedFrame->GetName();
    pin_ptr<const WCHAR> strDate = PtrToStringChars(str);
    _aimpCore->CreateObject(IID_IAIMPString, reinterpret_cast<void**>(&strObject));
    strObject->SetData(PWCHAR(strDate), str->Length);
    *S = strObject;
    //strObject->Release();
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

BOOL WINAPI OptionsDialogFrameExtension::DialogChar(WCHAR CharCode, int Unused) {
    return true;
}

BOOL WINAPI OptionsDialogFrameExtension::DialogKey(WORD CharCode, int Unused) {
    return true;
}

BOOL WINAPI OptionsDialogFrameExtension::SelectFirstControl() {
    return true;
}

BOOL WINAPI OptionsDialogFrameExtension::SelectNextControl(BOOL FindForward, BOOL CheckTabStop) {
    return true;
}
