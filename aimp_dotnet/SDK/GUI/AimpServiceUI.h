#pragma once
#include "..\BaseManager.h"

#include ".\Controls\Form\AimpUIForm.h"
#include ".\Controls\Form\AimpUIFormEvents.h"


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
                        (DWORD)flags, AimpConverter::MakeAimpString(_core->GetAimpCore(), name),
                        static_cast<AimpUIFormEvents::Base*>(formEvents),
                        &frm));
                if (r != AimpActionResult::Ok)
                {
                    return r;
                }

                form = gcnew AimpUIForm(frm, (IAIMPUIFormEvents*)formEvents);
                return r;
            }


            virtual AimpActionResult CreateControl(IAimpUIForm ^owner, IAimpUIWinControl ^parent, String ^name, AimpUIItem ^%item)
            {
                return AimpActionResult::Ok;
            }

            virtual AimpActionResult CreateObject(IAimpUIForm ^owner, AimpUIItem ^%item)
            {
                return AimpActionResult::Ok;
            }
        };
    }
}