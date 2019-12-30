// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "stdafx.h"
#include "AimpAction.h"
#include "AimpServiceActionManager.h"

AimpServiceActionManager::AimpServiceActionManager(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceActionManager>(core)
{
}

AimpActionResult AimpServiceActionManager::GetById(String^ id, IAimpAction^% action)
{
    auto result = AimpActionResult::Fail;
    IAIMPServiceActionManager* service = GetAimpService();
    action = nullptr;

    try
    {
        if (service != nullptr)
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
        ReleaseObject(service);
    }

    return result;
}

int AimpServiceActionManager::MakeHotkey(int modifiers, unsigned int key)
{
    IAIMPServiceActionManager* service = GetAimpService();

    try
    {
        if (service != nullptr)
        {
            return service->MakeHotkey(DWORD(modifiers), key);
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return 0;
}

AimpActionResult AimpServiceActionManager::Register(IAimpAction^ action)
{
    return CheckResult(_core->GetAimpCore()->RegisterExtension(IID_IAIMPServiceActionManager,
                                                               static_cast<AimpAction^>(action)->InternalAimpObject));
}

AimpActionResult AimpServiceActionManager::Register(Generic::ICollection<IAimpAction^>^ actions)
{
    AimpActionResult result = AimpActionResult::Fail;

    for each (IAimpAction^ item in actions)
    {
        result = Register(item);

        if (result != AimpActionResult::OK)
        {
            return result;
        }
    }

    return result;
}

IAimpAction^ AimpServiceActionManager::CreateAction()
{
    IAIMPAction* action = nullptr;
    if (_core->CreateAction(&action) == AimpActionResult::OK && action != nullptr)
    {
        return gcnew AimpAction(action);
    }

    return nullptr;
}

IAIMPServiceActionManager* AimpServiceActionManager::GetAimpService()
{
    IAIMPServiceActionManager* service = nullptr;
    GetService(IID_IAIMPServiceActionManager, &service);
    return service;
}
