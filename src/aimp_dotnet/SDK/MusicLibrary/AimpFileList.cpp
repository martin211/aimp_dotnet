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

z // ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------



#include "Stdafx.h"
#include "AimpFileList.h"


using namespace AIMP::SDK;

AimpFileList::AimpFileList(IAIMPMLFileList* aimpObject) : AimpObject(aimpObject)
{
}

ActionResultType AimpFileList::Add(Object^ id, String^ fileName)
{
    IAIMPString* sFileName = AimpConverter::ToAimpString(fileName);
    ActionResultType result = ActionResultType::Fail;

    try
    {
        result = CheckResult(InternalAimpObject->Add(&AimpConverter::ToNativeVariant(id), sFileName));
    }
    finally
    {
        if (sFileName != nullptr)
        {
            sFileName->Release();
            sFileName = nullptr;
        }
    }

    return result;
}

ActionResultType AimpFileList::Clear()
{
    return CheckResult(InternalAimpObject->Clear());
}

ActionResultType AimpFileList::Delete(int index)
{
    return CheckResult(InternalAimpObject->Delete(index));
}

ActionResultType AimpFileList::Insert(int index, Object^ id, String^ fileName)
{
    IAIMPString* sFileName = AimpConverter::ToAimpString(fileName);
    ActionResultType result = ActionResultType::Fail;

    try
    {
        result = CheckResult(InternalAimpObject->Insert(index, &AimpConverter::ToNativeVariant(id), sFileName));
    }
    finally
    {
        if (sFileName != nullptr)
        {
            sFileName->Release();
            sFileName = nullptr;
        }
    }

    return result;
}

int AimpFileList::GetCount()
{
    return InternalAimpObject->GetCount();
}

ActionResultType AimpFileList::GetFileName(int index, String^% fileName)
{
    IAIMPString* str = nullptr;
    fileName = nullptr;
    ActionResultType result = ActionResultType::Fail;

    try
    {
        result = CheckResult(InternalAimpObject->GetFileName(index, &str));

        if (result == ActionResultType::OK && str != nullptr)
        {
            fileName = AimpConverter::ToManagedString(str);
        }

        return result;
    }
    finally
    {
        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }
}

ActionResultType AimpFileList::SetFileName(int index, String^ fileName)
{
    IAIMPString* sFileName = AimpConverter::ToAimpString(fileName);
    ActionResultType result = ActionResultType::Fail;

    try
    {
        result = CheckResult(InternalAimpObject->SetFileName(index, sFileName));
    }
    finally
    {
        if (sFileName != nullptr)
        {
            sFileName->Release();
            sFileName = nullptr;
        }
    }

    return result;
}

ActionResultType AimpFileList::GetId(int index, Object^% id)
{
    VARIANT* idVar;
    id = nullptr;
    ActionResultType result = ActionResultType::Fail;

    try
    {
        result = CheckResult(InternalAimpObject->GetID(index, &idVar));

        if (result == ActionResultType::OK)
        {
            id = AimpConverter::FromVaiant(idVar);
        }
    }
    finally
    {
        idVar = nullptr;
    }

    return result;
}

ActionResultType AimpFileList::SetId(int index, Object^ id)
{
    return CheckResult(InternalAimpObject->SetID(index, &AimpConverter::ToNativeVariant(id)));
}

ActionResultType AimpFileList::Clone(IAimpFileList^% list)
{
    list = nullptr;

    IAIMPMLFileList* cloneList = nullptr;
    ActionResultType res = ActionResultType::Fail;

    try
    {
        res = CheckResult(InternalAimpObject->Clone(reinterpret_cast<void**>(&cloneList)));

        if (res == ActionResultType::OK)
        {
            list = gcnew AimpFileList(cloneList);
        }
    }
    finally
    {
        if (cloneList != nullptr)
        {
            cloneList->Release();
            cloneList = nullptr;
        }
    }

    return res;
}
