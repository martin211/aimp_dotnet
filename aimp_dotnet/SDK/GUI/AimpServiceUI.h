#pragma once
#include "..\BaseManager.h"

#include ".\Controls\Form\AimpUIForm.h"
#include ".\Controls\Form\AimpUIFormEvents.h"
//#include ".\Controls\AimpUIBaseEdit.h"


namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::UI;
        using namespace AIMP::SDK::GUI;
        using namespace AIMP::SDK::GUI::Controls;
        using namespace AIMP::SDK::GUI::Controls::Form;

        public ref class AimpServiceUI : public AimpBaseManager, public IAimpServiceUI
        {
        private:
            IAIMPServiceUI *_service;

        public:
            explicit AimpServiceUI(ManagedAimpCore ^core) : AimpBaseManager(core)
            {
                IAIMPServiceUI *service;
                core->GetService(IID_IAIMPServiceUI, (void**)&service);
                _service = service;
            }

            virtual AimpActionResult CreateForm(IntPtr ownerWindow, CreateFormFlags flags, String ^name, IAimpUIForm ^%form)
            {
                IAIMPUIForm *frm;
                AimpUIFormEvents *formEvents = new AimpUIFormEvents();

                AimpActionResult r = Utils::CheckResult(
                    _service->CreateForm((HWND)ownerWindow.ToPointer(),
                        (DWORD)flags, 
                        AimpConverter::MakeAimpString(_core->GetAimpCore(), name),
                        static_cast<AimpUIFormEvents::Base*>(formEvents),
                        &frm));

                if (r != AimpActionResult::Ok)
                {
                    return r;
                }

                AimpUIForm ^aimpForm = gcnew AimpUIForm(frm, this);
                formEvents->SetFormControl(aimpForm);
                form = aimpForm;
                return r;
            }

            virtual AimpActionResult CreateObject(IAimpUIForm ^owner, AimpUIItem ^%item)
            {
                return AimpActionResult::Ok;
            }

            generic<typename TControl>
            virtual AimpActionResult CreateControl(IAimpUIForm ^owner, IAimpUIWinControl ^parent, String ^name, TControl %item) override
            {
                //if (static_cast<AIMP::SDK::GUI::Controls::AimpUIControlPlacement>(item) != nullptr)
                //{
                //    _service->CreateControl(
                //        ((AimpUIForm^)owner)->InternalAimpControl, 
                //        ((AimpUIWinControl^)parent)->InternalAimpControl, 
                //        AimpConverter::MakeAimpString(_core->GetAimpCore(), name),
                //        nullptr,
                //        IID_TAIMPUIControlPlacement
                //        )
                //}

                return AimpActionResult::Ok;
            }
        };
    }
}