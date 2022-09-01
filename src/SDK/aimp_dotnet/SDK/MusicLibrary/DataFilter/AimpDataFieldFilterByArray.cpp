//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpDataFieldFilterByArray.h"

using namespace AIMP::SDK;

AimpDataFieldFilterByArray::
AimpDataFieldFilterByArray(IAIMPMLDataFieldFilterByArray* aimpObject) : AimpObject(aimpObject) {
}

String^ AimpDataFieldFilterByArray::Field::get() {
    return PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELDFILTERBYARRAY_FIELD);
}

void AimpDataFieldFilterByArray::Field::set(String^ value) {
    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELDFILTERBYARRAY_FIELD, value);
}

AimpActionResult<IList<Object^>^>^ AimpDataFieldFilterByArray::GetData() {
    // TODO: Complete it
    int count = 0;
    auto res = CheckResult(InternalAimpObject->GetData(nullptr, &count));

    if (res == ActionResultType::OK && count > 0) {
        const auto result = gcnew List<Object^>(count);
        VARIANT* val = nullptr;
        res = CheckResult(InternalAimpObject->GetData(val, nullptr));
        if (res == ActionResultType::OK) {
            for (int i = 0; i < count-1; i++) {
                Object^ v = AimpConverter::FromVariant(&val[0]);
                result->Add(v);
            }
        }

        return gcnew AimpActionResult<IList<Object^>^>(result);
    }

    return gcnew AimpActionResult<IList<Object^>^>(res);
}

ActionResult AimpDataFieldFilterByArray::SetData(IList<Object^>^ values) {
    ActionResultType res = ActionResultType::Fail;
    if (values->Count > 0) {
        VARIANT* arr = new VARIANT[values->Count];
        for (int i = 0; i < values->Count; i++) {
            arr[i] = AimpConverter::ToNativeVariant(values[i]);
        }

        res = CheckResult(InternalAimpObject->SetData(arr, values->Count));
    }

    return ACTION_RESULT(res);
}
