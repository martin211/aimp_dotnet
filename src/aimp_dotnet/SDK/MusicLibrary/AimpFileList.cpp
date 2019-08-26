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

#include "Stdafx.h"
#include "AimpFileList.h"


using namespace AIMP::SDK;

AimpFileList::AimpFileList(IAIMPMLFileList* aimpObject) : AimpObject(aimpObject)
{
}

AimpActionResult AimpFileList::Add(Object^ id, String^ fileName)
{
    IAIMPString* sFileName = AimpConverter::ToAimpString(fileName);
    AimpActionResult result = AimpActionResult::Fail;

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

AimpActionResult AimpFileList::Clear()
{
    return CheckResult(InternalAimpObject->Clear());
}

AimpActionResult AimpFileList::Delete(int index)
{
    return CheckResult(InternalAimpObject->Delete(index));
}

AimpActionResult AimpFileList::Insert(int index, Object^ id, String^ fileName)
{
    IAIMPString* sFileName = AimpConverter::ToAimpString(fileName);
    AimpActionResult result = AimpActionResult::Fail;

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

AimpActionResult AimpFileList::GetFileName(int index, String^% fileName)
{
    IAIMPString* str = nullptr;
    fileName = nullptr;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        result = CheckResult(InternalAimpObject->GetFileName(index, &str));

        if (result == AimpActionResult::OK && str != nullptr)
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

AimpActionResult AimpFileList::SetFileName(int index, String^ fileName)
{
    IAIMPString* sFileName = AimpConverter::ToAimpString(fileName);
    AimpActionResult result = AimpActionResult::Fail;

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

AimpActionResult AimpFileList::GetId(int index, Object^% id)
{
    VARIANT* idVar;
    id = nullptr;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        result = CheckResult(InternalAimpObject->GetID(index, &idVar));

        if (result == AimpActionResult::OK)
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

AimpActionResult AimpFileList::SetId(int index, Object^ id)
{
    return CheckResult(InternalAimpObject->SetID(index, &AimpConverter::ToNativeVariant(id)));
}

AimpActionResult AimpFileList::Clone(IAimpFileList^% list)
{
    list = nullptr;

    IAIMPMLFileList* cloneList = nullptr;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = CheckResult(InternalAimpObject->Clone(reinterpret_cast<void**>(&cloneList)));

        if (res == AimpActionResult::OK)
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
