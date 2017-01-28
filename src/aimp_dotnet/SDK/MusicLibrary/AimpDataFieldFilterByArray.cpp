/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#include "Stdafx.h"
#include "AimpDataFieldFilterByArray.h"

using namespace AIMP::SDK;

AimpDataFieldFilterByArray::AimpDataFieldFilterByArray(IAIMPMLDataFieldFilterByArray *aimpObject) : AimpObject(aimpObject)
{}

String^ AimpDataFieldFilterByArray::Field::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELDFILTERBYARRAY_FIELD);
}

void AimpDataFieldFilterByArray::Field::set(String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELDFILTERBYARRAY_FIELD, value);
}

AimpActionResult AimpDataFieldFilterByArray::GetData(IList<Object^>^ values)
{
    values = nullptr;
    return AimpActionResult::NotImplemented;
}

AimpActionResult AimpDataFieldFilterByArray::SetData(IList<Object^>^ values)
{
    return AimpActionResult::NotImplemented;
}
