#pragma once
#include "..\BaseManager.h"

#include ".\Controls\Form\AimpUIForm.h"
#include ".\Controls\Form\AimpUIFormEvents.h"
#include ".\Controls\AimpUIBaseEdit.h"


namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::UI;
        using namespace AIMP::SDK::GUI;
        using namespace AIMP::SDK::GUI::Controls;
        using namespace AIMP::SDK::GUI::Controls::Form;

        public ref class AimpServiceUI : public AimpBaseManager<IAIMPServiceUI>, public IAimpServiceUI
        {
        public:
            explicit AimpServiceUI(ManagedAimpCore ^core) : AimpBaseManager(core)
            {}

            virtual AimpActionResult CreateForm(IntPtr ownerWindow, CreateFormFlags flags, String ^name, IAimpUIForm ^%form)
            {
                IAIMPUIForm *frm = NULL;
                AimpUIFormEvents *formEvents = NULL;
                IAIMPServiceUI *service = NULL;
                IAIMPString *nameString = AimpConverter::MakeAimpString(_core->GetAimpCore(), name);
                try
                {
                    _core->GetService(IID_IAIMPServiceUI, (void**)&service);
                    formEvents = new AimpUIFormEvents();
                    AimpActionResult r = Utils::CheckResult(
                        service->CreateForm((HWND)ownerWindow.ToPointer(),
                            (DWORD)flags,
                            nameString,
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
                finally
                {
                    service->Release();
                    nameString->Release();
                    //((IUnknown*)frm)->Release();
                    //formEvents->Release();
                }
            }

            virtual AimpActionResult CreateObject(IAimpUIForm ^owner, AimpUIItem ^%item)
            {
                return AimpActionResult::Ok;
            }

            generic<typename TControl>
            virtual AimpActionResult CreateControl(IAimpUIForm ^owner, IAimpUIWinControl ^parent, String ^name, TControl %item)
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