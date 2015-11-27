#pragma once

#include <msclr/marshal.h>

namespace AIMPSDK
{
    #include "aimp3_60_sdk.h"

    #include "IUnknownInterfaceImpl.h"
    #include "Utils.h"
    #include "AimpObject.h"


    using namespace AIMPSDK36;

    typedef boost::intrusive_ptr<IAIMPString> IAIMPString_ptr;

    class IAimpDotNetProxy : public IUnknown
    {
        public:
            virtual void RegisterOptionsFrameExtension(IAIMPOptionsDialogFrame *frame) = 0;
    };

    class AimpExtension
    {
        protected:
            IUnknown *_mainPlugin;
            IAIMPCore *_aimpCore;
        public:
            AimpExtension(IUnknown *mainPlugin, IAIMPCore *aimpCore)
            {
                _mainPlugin = mainPlugin;
                _aimpCore = aimpCore;
            }
    };

    class OptionsDialogFrameProxy : public IUnknownInterfaceImpl<IAIMPOptionsDialogFrame>, public IAIMPOptionsDialogFrameKeyboardHelper, public AimpExtension
    {
        public:
            typedef IUnknownInterfaceImpl<IAIMPOptionsDialogFrame> Base;

        private:
            gcroot<AIMP::SDK::Services::Options::IAimpOptionsDialogFrame^> _managedFrame;
        public:
            explicit OptionsDialogFrameProxy(IUnknown *mainPlugin, IAIMPCore *aimpCore, gcroot<AIMP::SDK::Services::Options::IAimpOptionsDialogFrame^> managedFrame) 
                : AimpExtension(mainPlugin, aimpCore)
            {
                _managedFrame = managedFrame;
            }

            GUID ExtensionId()
            {
                return IID_IAIMPServiceOptionsDialog;
            }

            virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
            {
                //return _mainPlugin->QueryInterface(riid, ppvObject);
                if (!ppvObject) return E_POINTER;

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
                return _mainPlugin->AddRef();
            }

            virtual ULONG WINAPI Release(void)
            {
                return _mainPlugin->Release();
            }

            virtual HRESULT WINAPI GetName(IAIMPString **S)
            {
                IAIMPString *strObject = NULL;
                System::String^ str = _managedFrame->GetName();
                pin_ptr<const WCHAR> strDate = PtrToStringChars(str);
                _aimpCore->CreateObject(IID_IAIMPString, (void**)&strObject);
                strObject->SetData((PWCHAR)strDate, str->Length);
                *S = strObject;
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
}