#pragma once
#include "..\..\Stdafx.h"
#include "AimpServiceUI.h"


namespace AIMP
{
    namespace SDK
    {
        AimpActionResult AimpServiceUI::CreateForm(IntPtr ownerWindow, CreateFormFlags flags, String ^name, AIMP::SDK::GUI::Controls::Form::IAimpUIForm ^%form)
        {
            IAIMPUIForm *frm;

            AimpActionResult r = Utils::CheckResult(_service->CreateForm((HWND)ownerWindow.ToPointer(), (DWORD)flags, AimpConverter::MakeAimpString(_core->GetAimpCore(), name), NULL, &frm));
            if (r != AimpActionResult::Ok)
            {
                return r;
            }

            form = gcnew AimpUIForm(frm);
            return r;
        }

        AimpActionResult AimpServiceUI::CreateControl(AIMP::SDK::GUI::Controls::Form::IAimpUIForm ^owner, IAimpUIWinControl ^parent, String ^name, AimpUIItem ^%item)
        {
            return AimpActionResult::Ok;
        }

        AimpActionResult AimpServiceUI::CreateObject(AIMP::SDK::GUI::Controls::Form::IAimpUIForm ^owner, AimpUIItem ^%item)
        {
            return AimpActionResult::Ok;
        }
    }
}
