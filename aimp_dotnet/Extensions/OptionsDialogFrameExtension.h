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
    explicit OptionsDialogFrameExtension(IAIMPCore *aimpCore, gcroot<AIMP::SDK::Options::IAimpOptionsDialogFrame^> managedFrame)
        : AimpExtension(aimpCore)
    {
        _managedFrame = managedFrame;
    }

    GUID ExtensionId()
    {
        return IID_IAIMPServiceOptionsDialog;
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (!ppvObject) 
        {
            return E_POINTER;
        }

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

        return E_NOINTERFACE;
    }

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }

    virtual HRESULT WINAPI GetName(IAIMPString **S)
    {
        IAIMPString *strObject = NULL;
        System::String^ str = _managedFrame->GetName();
        pin_ptr<const WCHAR> strDate = PtrToStringChars(str);
        _aimpCore->CreateObject(IID_IAIMPString, (void**)&strObject);
        strObject->SetData((PWCHAR)strDate, str->Length);
        *S = strObject;
        //strObject->Release();
        return S_OK;
    }

    virtual HWND WINAPI CreateFrame(HWND ParentWnd)
    {
        System::IntPtr parentWindow(ParentWnd);
        System::IntPtr childWindow = _managedFrame->CreateFrame(parentWindow);
        return (HWND)childWindow.ToPointer();
    }

    virtual void WINAPI DestroyFrame()
    {
        _managedFrame->DestroyFrame();
    }

    virtual void WINAPI Notification(int ID)
    {
        _managedFrame->Notification(ID);
    }

    virtual BOOL WINAPI DialogChar(WCHAR CharCode, int Unused)
    {
        return true;
    }

    virtual BOOL WINAPI DialogKey(WORD CharCode, int Unused)
    {
        return true;
    }

    virtual BOOL WINAPI SelectFirstControl()
    {
        return true;
    }

    virtual BOOL WINAPI SelectNextControl(BOOL FindForward, BOOL CheckTabStop)
    {
        return true;
    }
};
