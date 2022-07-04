// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpFileList.h"


using namespace AIMP::SDK;

AimpFileList::AimpFileList(IAIMPMLFileList* aimpObject) : AimpObject(aimpObject) {
}

ActionResult AimpFileList::Add(Object^ id, String^ fileName) {
    IAIMPString* sFileName = AimpConverter::ToAimpString(fileName);
    ActionResultType result = ActionResultType::Fail;

    try {
        result = CheckResult(InternalAimpObject->Add(&AimpConverter::ToNativeVariant(id), sFileName));
    }
    finally {
        if (sFileName != nullptr) {
            sFileName->Release();
            sFileName = nullptr;
        }
    }

    return ACTION_RESULT(result);
}

ActionResult AimpFileList::Clear() {
    return ACTION_RESULT(CheckResult(InternalAimpObject->Clear()));
}

ActionResult AimpFileList::Delete(int index) {
    return ACTION_RESULT(CheckResult(InternalAimpObject->Delete(index)));
}

ActionResult AimpFileList::Insert(int index, Object^ id, String^ fileName) {
    IAIMPString* sFileName = AimpConverter::ToAimpString(fileName);
    ActionResultType result = ActionResultType::Fail;

    try {
        result = CheckResult(InternalAimpObject->Insert(index, &AimpConverter::ToNativeVariant(id), sFileName));
    }
    finally {
        if (sFileName != nullptr) {
            sFileName->Release();
            sFileName = nullptr;
        }
    }

    return ACTION_RESULT(result);
}

int AimpFileList::GetCount() {
    return InternalAimpObject->GetCount();
}

AimpActionResult<String^>^ AimpFileList::GetFileName(int index) {
    IAIMPString* str = nullptr;
    String^ fileName = nullptr;
    ActionResultType result = ActionResultType::Fail;

    try {
        result = CheckResult(InternalAimpObject->GetFileName(index, &str));

        if (result == ActionResultType::OK && str != nullptr) {
            fileName = AimpConverter::ToManagedString(str);
        }
    }
    finally {
        if (str != nullptr) {
            str->Release();
            str = nullptr;
        }
    }

    return gcnew AimpActionResult<String^>(result, fileName);
}

ActionResult AimpFileList::SetFileName(int index, String^ fileName) {
    IAIMPString* sFileName = AimpConverter::ToAimpString(fileName);
    ActionResultType result = ActionResultType::Fail;

    try {
        result = CheckResult(InternalAimpObject->SetFileName(index, sFileName));
    }
    finally {
        if (sFileName != nullptr) {
            sFileName->Release();
            sFileName = nullptr;
        }
    }

    return ACTION_RESULT(result);
}

AimpActionResult<Object^>^ AimpFileList::GetId(int index) {
    VARIANT* idVar;
    Object^ id = nullptr;
    ActionResultType result = ActionResultType::Fail;

    try {
        result = CheckResult(InternalAimpObject->GetID(index, &idVar));

        if (result == ActionResultType::OK) {
            id = AimpConverter::FromVariant(idVar);
        }
    }
    finally {
        idVar = nullptr;
    }

    return gcnew AimpActionResult<Object^>(result, id);
}

ActionResult AimpFileList::SetId(int index, Object^ id) {
    return ACTION_RESULT(CheckResult(InternalAimpObject->SetID(index, &AimpConverter::ToNativeVariant(id))));
}

AimpActionResult<IAimpFileList^>^ AimpFileList::Clone() {
    IAimpFileList^ list = nullptr;

    IAIMPMLFileList* cloneList = nullptr;
    ActionResultType res = ActionResultType::Fail;

    try {
        res = CheckResult(InternalAimpObject->Clone(reinterpret_cast<void**>(&cloneList)));

        if (res == ActionResultType::OK) {
            list = gcnew AimpFileList(cloneList);
        }
    }
    finally {
        if (cloneList != nullptr) {
            cloneList->Release();
            cloneList = nullptr;
        }
    }

    return gcnew AimpActionResult<IAimpFileList^>(res, list);
}
