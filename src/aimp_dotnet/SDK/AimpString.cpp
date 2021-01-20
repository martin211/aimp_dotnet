// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpString.h"

using namespace AIMP::SDK;

AimpString::AimpString(IAIMPString* aimpObject) {
    _aimpObject = aimpObject;
}

ActionResultType AimpString::GetChar(int index, wchar_t% c) {
    WCHAR* chr = nullptr;
    ActionResultType result = CheckResult(InternalAimpObject->GetChar(index, chr));
    return result;
}

String^ AimpString::GetData() {
    return gcnew String(InternalAimpObject->GetData());
}

int AimpString::GetLength() {
    return InternalAimpObject->GetLength();
}

int AimpString::GetHashCode() {
    if (InternalAimpObject != NULL)
    {
        return InternalAimpObject->GetHashCode();
    }

    return 0;
}

ActionResultType AimpString::SetChar(int index, wchar_t c) {
    return CheckResult(InternalAimpObject->SetChar(index, c));
}

ActionResultType AimpString::SetData(String^ chars, int charsCount) {
    pin_ptr<const WCHAR> strData = PtrToStringChars(chars);
    return CheckResult(InternalAimpObject->SetData((PWCHAR)strData, charsCount));
}

ActionResultType AimpString::Add(IAimpString^ str) {
    return CheckResult(InternalAimpObject->Add(((AimpString^)str)->InternalAimpObject));
}

ActionResultType AimpString::Add(String^ chars, int charsCount) {
    pin_ptr<const WCHAR> strData = PtrToStringChars(chars);
    return CheckResult(InternalAimpObject->Add2((PWCHAR)strData, charsCount));
}

ActionResultType AimpString::ChangeCase(AimpStringCase mode) {
    return CheckResult(InternalAimpObject->ChangeCase((int)mode));
}

ActionResultType AimpString::Clone(IAimpString^% str) {
    IAIMPString* s = nullptr;
    ActionResultType result = CheckResult(InternalAimpObject->Clone(&s));
    if (result == ActionResultType::OK && s != nullptr) {
        str = gcnew AimpString(s);
    }

    return result;
}

ActionResultType AimpString::Compare(IAimpString^ str, int% compareResult, bool ignoreCase) {
    int res = 0;
    ActionResultType result = CheckResult(
        InternalAimpObject->Compare(((AimpString^)str)->InternalAimpObject, &res, ignoreCase));
    if (result == ActionResultType::OK) {
        compareResult = res;
    }

    return result;
}

ActionResultType AimpString::Compare(String^ chars, int charsCount, int% compareResult, bool ignoreCase) {
    int res = 0;
    pin_ptr<const WCHAR> strData = PtrToStringChars(chars);

    ActionResultType result = CheckResult(InternalAimpObject->Compare2((PWCHAR)strData, charsCount, &res, ignoreCase));
    if (result == ActionResultType::OK) {
        compareResult = res;
    }

    return result;
}

ActionResultType AimpString::Delete(int index, int count) {
    return CheckResult(InternalAimpObject->Delete(index, count));
}

ActionResultType AimpString::Find(IAimpString^ str, int% index, AimpStringFindFlags flags, int startFromIndex) {
    int i = 0;

    ActionResultType res = CheckResult(InternalAimpObject->Find(
        ((AimpString^)str)->InternalAimpObject,
        &i,
        (int)flags,
        startFromIndex));

    if (res == ActionResultType::OK) {
        index = i;
    }

    return res;
}

ActionResultType AimpString::Find(String^ chars, int charsCount, int% index, AimpStringFindFlags flags,
                                  int startFromIndex) {
    int i = 0;

    pin_ptr<const WCHAR> strData = PtrToStringChars(chars);

    ActionResultType res = CheckResult(InternalAimpObject->Find2(
        (PWCHAR)strData,
        charsCount,
        &i,
        (int)flags,
        startFromIndex));

    if (res == ActionResultType::OK) {
        index = i;
    }

    return res;
}

ActionResultType AimpString::Insert(int index, IAimpString^ str) {
    return CheckResult(InternalAimpObject->Insert(
        index,
        ((AimpString^)str)->InternalAimpObject));
}

ActionResultType AimpString::Insert(int index, String^ chars, int charsCount) {
    pin_ptr<const WCHAR> strData = PtrToStringChars(chars);

    return CheckResult(InternalAimpObject->Insert2(
        index,
        (PWCHAR)strData,
        charsCount));
}

ActionResultType AimpString::Replace(IAimpString^ oldPattern, IAimpString^ newPattern, int flags) {
    return CheckResult(InternalAimpObject->Replace(
        ((AimpString^)oldPattern)->InternalAimpObject,
        ((AimpString^)newPattern)->InternalAimpObject,
        flags));
}

ActionResultType AimpString::Replace(String^ oldPatternChars, int oldPatternCharsCount, String^ newPatternChars,
                                     int newPatternCharsCount, int flags) {
    pin_ptr<const WCHAR> oldPattern = PtrToStringChars(oldPatternChars);
    pin_ptr<const WCHAR> newPattern = PtrToStringChars(newPatternChars);

    return CheckResult(InternalAimpObject->Replace2(
        (PWCHAR)oldPattern,
        oldPatternCharsCount,
        (PWCHAR)newPattern,
        newPatternCharsCount,
        flags));

    return ActionResultType::OK;
}

ActionResultType AimpString::SubString(int index, int count, IAimpString^% str) {
    IAIMPString* subStr = nullptr;
    ActionResultType res = CheckResult(InternalAimpObject->SubString(index, count, &subStr));
    if (res == ActionResultType::OK) {
        str = gcnew AimpString(subStr);
    }

    return res;
}
