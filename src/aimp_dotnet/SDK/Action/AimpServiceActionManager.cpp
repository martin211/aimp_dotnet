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

ActionResultType AimpServiceActionManager::GetById(String^ id, IAimpAction^% action)
{
    auto result = ActionResultType::Fail;
    IAIMPServiceActionManager* service = GetAimpService();
    action = nullptr;

    try
    {
        if (service != nullptr)
        {
            IAIMPAction* resAction = nullptr;
            IAIMPString* strId = AimpConverter::ToAimpString(id);
            result = CheckResult(service->GetByID(strId, &resAction));
            if (result == ActionResultType::OK)
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

int AimpServiceActionManager::MakeHotkey(ModifierKeys modifiers, unsigned int key)
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

ActionResultType AimpServiceActionManager::Register(IAimpAction^ action)
{
    return CheckResult(_core->GetAimpCore()->RegisterExtension(IID_IAIMPServiceActionManager,
                                                               static_cast<AimpAction^>(action)->InternalAimpObject));
}

ActionResultType AimpServiceActionManager::Register(Generic::ICollection<IAimpAction^>^ actions)
{
    ActionResultType result = ActionResultType::Fail;

    for each (IAimpAction^ item in actions)
    {
        result = Register(item);

        if (result != ActionResultType::OK)
        {
            return result;
        }
    }

    return result;
}

IAimpAction^ AimpServiceActionManager::CreateAction()
{
    IAIMPAction* action = nullptr;
    if (_core->CreateAction(&action) == ActionResultType::OK && action != nullptr)
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
