//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "stdafx.h"
#include "AimpAction.h"
#include "AimpServiceActionManager.h"

AimpServiceActionManager::AimpServiceActionManager(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceActionManager>(
    core) {
}

AimpActionResult<IAimpAction^>^ AimpServiceActionManager::GetById(String^ id) {
    auto res = ActionResultType::Fail;
    IAIMPServiceActionManager* service = GetAimpService();
    IAimpAction^ action = nullptr;
    AimpActionResult<IAimpAction^>^ result = nullptr;

    try {
        if (service != nullptr) {
            IAIMPAction* resAction = nullptr;
            IAIMPString* strId = AimpConverter::ToAimpString(id);
            res = CheckResult(service->GetByID(strId, &resAction));
            if (res == ActionResultType::OK) {
                action = gcnew AimpAction(resAction);
            }

            strId->Release();
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<IAimpAction^>(res, action);
}

int AimpServiceActionManager::MakeHotkey(ModifierKeys modifiers, unsigned int key) {
    IAIMPServiceActionManager* service = GetAimpService();

    try {
        //if (modifiers == ModifierKeys::Alt) {
        //    modifiers = ModifierKeys::Control;
        //}
        //else if (modifiers == ModifierKeys::Control) {
        //    modifiers = ModifierKeys::Alt;
        //}

        if (service != nullptr) {
            return service->MakeHotkey(DWORD(modifiers), key);
        }
    }
    finally {
        ReleaseObject(service);
    }

    return 0;
}

AimpActionResult^ AimpServiceActionManager::Register(IAimpAction^ action) {
    if (String::IsNullOrEmpty(action->Name)) {
        ARGUMENT_NULL("Name", "Action name cannot be empty")
    }

    if (String::IsNullOrEmpty(action->Id)) {
        ARGUMENT_NULL("Id", "Action id cannot be empty")
    }

    return GetResult(_core->GetAimpCore()->RegisterExtension(IID_IAIMPServiceActionManager,
                                                             static_cast<AimpAction^>(action)->InternalAimpObject));
}

AimpActionResult^ AimpServiceActionManager::Register(Generic::ICollection<IAimpAction^>^ actions) {
    ActionResultType result = ActionResultType::Fail;

    for each (IAimpAction^ item in actions) {
        const auto res = Register(item);

        if (res->ResultType != ActionResultType::OK) {
            return GetResult(result);
        }
    }

    return GetResult(result);
}

IAimpAction^ AimpServiceActionManager::CreateAction() {
    return nullptr;
}

IAIMPServiceActionManager* AimpServiceActionManager::GetAimpService() {
    IAIMPServiceActionManager* service = nullptr;
    GetService(IID_IAIMPServiceActionManager, &service);
    return service;
}
