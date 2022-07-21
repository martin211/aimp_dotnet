// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpString.h"

using namespace AIMP::SDK;

AimpString::AimpString(IAIMPString* aimpObject) : AimpObject<IAIMPString>(aimpObject, true) {
}

AimpActionResult<WCHAR>^ AimpString::GetChar(int index) {
    WCHAR* chr = nullptr;
    ActionResultType result = CheckResult(InternalAimpObject->GetChar(index, chr));
    return gcnew AimpActionResult<WCHAR>(result, *chr);
}

String^ AimpString::GetData() {
    return gcnew String(InternalAimpObject->GetData());
}

int AimpString::GetLength() {
    return InternalAimpObject->GetLength();
}

int AimpString::GetHashCode() {
    if (InternalAimpObject != nullptr)
    {
        return InternalAimpObject->GetHashCode();
    }

    return 0;
}

ActionResult AimpString::SetChar(int index, wchar_t c) {
    return gcnew AimpActionResult(CheckResult(InternalAimpObject->SetChar(index, c)));
}

ActionResult AimpString::SetData(String^ chars, int charsCount) {
    pin_ptr<const WCHAR> strData = PtrToStringChars(chars);
    return ACTION_RESULT(CheckResult(InternalAimpObject->SetData((PWCHAR)strData, charsCount)));
}

ActionResult AimpString::Add(IAimpString^ str) {
    return ACTION_RESULT(CheckResult(InternalAimpObject->Add(((AimpString^)str)->InternalAimpObject)));
}

ActionResult AimpString::Add(String^ chars, int charsCount) {
    pin_ptr<const WCHAR> strData = PtrToStringChars(chars);
    return ACTION_RESULT(CheckResult(InternalAimpObject->Add2((PWCHAR)strData, charsCount)));
}

ActionResult AimpString::ChangeCase(AimpStringCase mode) {
    return ACTION_RESULT(CheckResult(InternalAimpObject->ChangeCase((int)mode)));
}

AimpActionResult<IAimpString^>^ AimpString::Clone() {
    IAIMPString* s = nullptr;
    ActionResultType result = CheckResult(InternalAimpObject->Clone(&s));
    if (result == ActionResultType::OK && s != nullptr) {
        return gcnew AimpActionResult<IAimpString^>(result, gcnew AimpString(s));
    }

    return gcnew AimpActionResult<IAimpString^>(result);
}

IntResult AimpString::Compare(IAimpString^ str, bool ignoreCase) {
    int res = 0;
    ActionResultType result = CheckResult(
        InternalAimpObject->Compare(((AimpString^)str)->InternalAimpObject, &res, ignoreCase));
    if (result == ActionResultType::OK) {
        return INT_RESULT(result, res);
    }

    return INT_RESULT(result, -1);
}

IntResult AimpString::Compare(String^ chars, bool ignoreCase) {
    int res = 0;
    pin_ptr<const WCHAR> strData = PtrToStringChars(chars);

    ActionResultType result = CheckResult(InternalAimpObject->Compare2((PWCHAR)strData, chars->Length, &res, ignoreCase));
    if (result == ActionResultType::OK) {
        return INT_RESULT(result, res);
    }

    return INT_RESULT(result, -1);
}

ActionResult AimpString::Delete(int index, int count) {
    return ACTION_RESULT(CheckResult(InternalAimpObject->Delete(index, count)));
}

IntResult AimpString::Find(IAimpString^ str, AimpStringFindFlags flags, int startFromIndex) {
    int i = 0;

    ActionResultType res = CheckResult(InternalAimpObject->Find(
        ((AimpString^)str)->InternalAimpObject,
        &i,
        (int)flags,
        startFromIndex));

    if (res == ActionResultType::OK) {
        return INT_RESULT(res, i)
    }

    return INT_RESULT(res, -1);
}

IntResult AimpString::Find(String^ chars, AimpStringFindFlags flags, int startFromIndex) {
    int i = 0;

    pin_ptr<const WCHAR> strData = PtrToStringChars(chars);

    ActionResultType res = CheckResult(InternalAimpObject->Find2(
        (PWCHAR)strData,
        chars->Length,
        &i,
        (int)flags,
        startFromIndex));

    if (res == ActionResultType::OK) {
        return INT_RESULT(res, i)
    }

    return INT_RESULT(res, -1)
}

ActionResult AimpString::Insert(int index, IAimpString^ str) {
    return ACTION_RESULT(CheckResult(InternalAimpObject->Insert(
        index,
        ((AimpString^)str)->InternalAimpObject)));
}

ActionResult AimpString::Insert(int index, String^ chars) {
    pin_ptr<const WCHAR> strData = PtrToStringChars(chars);

    return ACTION_RESULT(CheckResult(InternalAimpObject->Insert2(
        index,
        (PWCHAR)strData,
        chars->Length)));
}

ActionResult AimpString::Replace(IAimpString^ oldPattern, IAimpString^ newPattern, AimpStringFindFlags flags) {
    return ACTION_RESULT(CheckResult(InternalAimpObject->Replace(
        ((AimpString^)oldPattern)->InternalAimpObject,
        ((AimpString^)newPattern)->InternalAimpObject,
        (int)flags)));
}

ActionResult AimpString::Replace(String^ oldPatternChars, String^ newPatternChars, AimpStringFindFlags flags) {
    pin_ptr<const WCHAR> oldPattern = PtrToStringChars(oldPatternChars);
    pin_ptr<const WCHAR> newPattern = PtrToStringChars(newPatternChars);

    return ACTION_RESULT(CheckResult(InternalAimpObject->Replace2(
        (PWCHAR)oldPattern,
        oldPatternChars->Length,
        (PWCHAR)newPattern,
        newPatternChars->Length,
        static_cast<int>(flags))));
}

AimpActionResult<IAimpString^>^ AimpString::SubString(int index, int count) {
    IAIMPString* subStr = nullptr;
    ActionResultType res = CheckResult(InternalAimpObject->SubString(index, count, &subStr));
    if (res == ActionResultType::OK) {
        return gcnew AimpActionResult<IAimpString^>(res, gcnew AimpString(subStr));
    }

    return gcnew AimpActionResult<IAimpString^>(res);
}

void AimpString::Release() {
    InternalAimpObject->Release();
}

int AimpString::GetAimpHashCode() {
    return reinterpret_cast<IAIMPHashCode*>(InternalAimpObject)->GetHashCode();
}

void AimpString::Recalculate() {
    return reinterpret_cast<IAIMPHashCode*>(InternalAimpObject)->Recalculate();
}
