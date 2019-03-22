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
#include "AimpString.h"

using namespace AIMP::SDK;

AimpString::AimpString(IAIMPString* aimpObject)
{
    _aimpObject = aimpObject;
}

AimpActionResult AimpString::GetChar(int index, wchar_t% c)
{
    WCHAR* chr = nullptr;
    AimpActionResult result = CheckResult(_aimpObject->GetChar(index, chr));
    return result;
}

String^ AimpString::GetData()
{
    return gcnew String(_aimpObject->GetData());
}

int AimpString::GetLength()
{
    return _aimpObject->GetLength();
}

int AimpString::GetHashCode()
{
    return _aimpObject->GetHashCode();
}

AimpActionResult AimpString::SetChar(int index, wchar_t c)
{
    return CheckResult(_aimpObject->SetChar(index, c));
}

AimpActionResult AimpString::SetData(String^ chars, int charsCount)
{
    pin_ptr<const WCHAR> strData = PtrToStringChars(chars);
    return CheckResult(_aimpObject->SetData((PWCHAR)strData, charsCount));
}

AimpActionResult AimpString::Add(IAimpString^ str)
{
    return CheckResult(_aimpObject->Add(((AimpString^)str)->InternalAimpObject));
}

AimpActionResult AimpString::Add(String^ chars, int charsCount)
{
    pin_ptr<const WCHAR> strData = PtrToStringChars(chars);
    return CheckResult(_aimpObject->Add2((PWCHAR)strData, charsCount));
}

AimpActionResult AimpString::ChangeCase(AIMPStringCase mode)
{
    return CheckResult(_aimpObject->ChangeCase((int)mode));
}

AimpActionResult AimpString::Clone(IAimpString^% str)
{
    IAIMPString* s = nullptr;
    AimpActionResult result = CheckResult(_aimpObject->Clone(&s));
    if (result == AimpActionResult::OK && s != nullptr)
    {
        str = gcnew AimpString(s);
    }

    return result;
}

AimpActionResult AimpString::Compare(IAimpString^ str, int% compareResult, bool ignoreCase)
{
    int res = 0;
    AimpActionResult result = CheckResult(
        _aimpObject->Compare(((AimpString^)str)->InternalAimpObject, &res, ignoreCase));
    if (result == AimpActionResult::OK)
    {
        compareResult = res;
    }

    return result;
}

AimpActionResult AimpString::Compare(String^ chars, int charsCount, int% compareResult, bool ignoreCase)
{
    int res = 0;
    pin_ptr<const WCHAR> strData = PtrToStringChars(chars);

    AimpActionResult result = CheckResult(_aimpObject->Compare2((PWCHAR)strData, charsCount, &res, ignoreCase));
    if (result == AimpActionResult::OK)
    {
        compareResult = res;
    }

    return result;
}

AimpActionResult AimpString::Delete(int index, int count)
{
    return CheckResult(_aimpObject->Delete(index, count));
}

AimpActionResult AimpString::Find(IAimpString^ str, int% index, AIMPStringFindFlags flags, int startFromIndex)
{
    int i = 0;

    AimpActionResult res = CheckResult(_aimpObject->Find(
        ((AimpString^)str)->InternalAimpObject,
        &i,
        (int)flags,
        startFromIndex));

    if (res == AimpActionResult::OK)
    {
        index = i;
    }

    return res;
}

AimpActionResult AimpString::Find(String^ chars, int charsCount, int% index, AIMPStringFindFlags flags,
                                  int startFromIndex)
{
    int i = 0;

    pin_ptr<const WCHAR> strData = PtrToStringChars(chars);

    AimpActionResult res = CheckResult(_aimpObject->Find2(
        (PWCHAR)strData,
        charsCount,
        &i,
        (int)flags,
        startFromIndex));

    if (res == AimpActionResult::OK)
    {
        index = i;
    }

    return res;
}

AimpActionResult AimpString::Insert(int index, IAimpString^ str)
{
    return CheckResult(_aimpObject->Insert(
        index,
        ((AimpString^)str)->InternalAimpObject));
}

AimpActionResult AimpString::Insert(int index, String^ chars, int charsCount)
{
    pin_ptr<const WCHAR> strData = PtrToStringChars(chars);

    return CheckResult(_aimpObject->Insert2(
        index,
        (PWCHAR)strData,
        charsCount));
}

AimpActionResult AimpString::Replace(IAimpString^ oldPattern, IAimpString^ newPattern, int flags)
{
    return CheckResult(_aimpObject->Replace(
        ((AimpString^)oldPattern)->InternalAimpObject,
        ((AimpString^)newPattern)->InternalAimpObject,
        flags));
}

AimpActionResult AimpString::Replace(String^ oldPatternChars, int oldPatternCharsCount, String^ newPatternChars,
                                     int newPatternCharsCount, int flags)
{
    pin_ptr<const WCHAR> oldPattern = PtrToStringChars(oldPatternChars);
    pin_ptr<const WCHAR> newPattern = PtrToStringChars(newPatternChars);

    return CheckResult(_aimpObject->Replace2(
        (PWCHAR)oldPattern,
        oldPatternCharsCount,
        (PWCHAR)newPattern,
        newPatternCharsCount,
        flags));

    return AimpActionResult::OK;
}

AimpActionResult AimpString::SubString(int index, int count, IAimpString^% str)
{
    IAIMPString* subStr = nullptr;
    AimpActionResult res = CheckResult(_aimpObject->SubString(index, count, &subStr));
    if (res == AimpActionResult::OK)
    {
        str = gcnew AimpString(subStr);
    }

    return res;
}
