// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

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

ActionResult AimpDataFieldFilterByArray::GetData(IList<Object^>^ values) {
    // TODO: Complete it
    values = nullptr;
    return ACTION_RESULT(ActionResultType::NotImplemented);
}

ActionResult AimpDataFieldFilterByArray::SetData(IList<Object^>^ values) {
    // TODO: Complete it
    return ACTION_RESULT(ActionResultType::NotImplemented);
}
