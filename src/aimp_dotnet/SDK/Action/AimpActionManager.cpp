// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "stdafx.h"
#include "AimpActionManager.h"
#include "AimpAction.h"

AimpActionManager::AimpActionManager(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceActionManager>(core)
{ }

AimpActionResult AimpActionManager::GetById(String^ id, IAimpAction^% action)
{
    auto result = AimpActionResult::Fail;
    IAIMPServiceActionManager* service = nullptr;
    action = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceActionManager, &service) == AimpActionResult::OK && service != nullptr)
        {
            IAIMPAction* resAction = nullptr;
            IAIMPString* strId = AimpConverter::ToAimpString(id);
            result = CheckResult(service->GetByID(strId, &resAction));
            if (result == AimpActionResult::OK)
            {
                action = gcnew AimpAction(resAction);
            }

            strId->Release();
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return result;
}

int AimpActionManager::MakeHotkey(ModifierKeys modifiers, unsigned int key)
{
    IAIMPServiceActionManager* service = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceActionManager, &service) == AimpActionResult::OK && service != nullptr)
        {
            return service->MakeHotkey(DWORD(modifiers), key);
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return 0;
}

AimpActionResult AimpActionManager::Register(IAimpAction^ action)
{
    return CheckResult(_core->GetAimpCore()->RegisterExtension(IID_IAIMPServiceActionManager, static_cast<AimpAction^>(action)->InternalAimpObject));
}

AimpActionResult AimpActionManager::Register(Generic::ICollection<IAimpAction^>^ actions)
{
    AimpActionResult result = AimpActionResult::Fail;

    for each(IAimpAction^ item in actions)
    {
        result = Register(item);

        if (result != AimpActionResult::OK)
        {
            return result;
        }
    }

    return result;
}

IAimpAction ^AimpActionManager::CreateAction()
{
    IAIMPAction* action = nullptr;
    if (_core->CreateAction(&action) == AimpActionResult::OK && action != nullptr)
    {
        return gcnew AimpAction(action);
    }

    return nullptr;
}
