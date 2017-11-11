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

#include "Stdafx.h"
#include "AimpFileList.h"


using namespace AIMP::SDK;

AimpFileList::AimpFileList(IAIMPMLFileList* aimpObject) : AimpObject(aimpObject)
{

}

AimpActionResult AimpFileList::Add(Object^ id, String^ fileName)
{
    IAIMPString *sFileName = AimpConverter::ToAimpString(fileName);
    try
    {
        return CheckResult(InternalAimpObject->Add(&AimpConverter::ToNativeVariant(id), sFileName));
    }
    finally
    {
        if (sFileName != NULL)
        {
            sFileName->Release();
            sFileName = NULL;
        }
    }
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
    IAIMPString *sFileName = AimpConverter::ToAimpString(fileName);

    try
    {
        return CheckResult(InternalAimpObject->Insert(index, &AimpConverter::ToNativeVariant(id), sFileName));
    }
    finally
    {
        if (sFileName != NULL)
        {
            sFileName->Release();
            sFileName = NULL;
        }
    }
}

int AimpFileList::GetCount()
{
    return InternalAimpObject->GetCount();
}

AimpActionResult AimpFileList::GetFileName(int index, String^% fileName)
{
    IAIMPString* str = NULL;
    fileName = nullptr;

    try
    {
        AimpActionResult res = CheckResult(InternalAimpObject->GetFileName(index, &str));

        if (res == AimpActionResult::Ok && str != NULL)
        {
            fileName = AimpConverter::ToManagedString(str);
        }

        return res;
    }
    finally
    {
        if (str != NULL)
        {
            str->Release();
            str = NULL;
        }
    }
}

AimpActionResult AimpFileList::SetFileName(int index, String^ fileName)
{
    IAIMPString *sFileName = AimpConverter::ToAimpString(fileName);

    try
    {
        return CheckResult(InternalAimpObject->SetFileName(index, sFileName));
    }
    finally
    {
        if (sFileName != NULL)
        {
            sFileName->Release();
            sFileName = NULL;
        }
    }
}

AimpActionResult AimpFileList::GetId(int index, Object^% id)
{
    VARIANT* idVar;
    id = nullptr;

    try
    {
        AimpActionResult res = CheckResult(InternalAimpObject->GetID(index, &idVar));

        if (res == AimpActionResult::Ok)
        {
            id = AimpConverter::FromVaiant(idVar);
        }

        return res;
    }
    finally
    {
        idVar = NULL;
    }
}

AimpActionResult AimpFileList::SetId(int index, Object^ id)
{
    return CheckResult(InternalAimpObject->SetID(index, &AimpConverter::ToNativeVariant(id)));
}

AimpActionResult AimpFileList::Clone(IAimpFileList^% list)
{
    list = nullptr;

    IAIMPMLFileList* cloneList = NULL;
    AimpActionResult res = AimpActionResult::Fail;

    try
    {
        res = CheckResult(InternalAimpObject->Clone((void**)&cloneList));

        if (res == AimpActionResult::Ok)
        {
            list = gcnew AimpFileList(cloneList);
        }
    }
    finally
    {
        if (cloneList != NULL)
        {
            cloneList->Release();
            cloneList = NULL;
        }
    }

    return res;
}
