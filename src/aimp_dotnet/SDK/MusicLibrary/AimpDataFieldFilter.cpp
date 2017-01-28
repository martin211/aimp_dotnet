/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#include "Stdafx.h"
#include "AimpDataFieldFilter.h"

using namespace AIMP::SDK;

AimpDataFieldFilter::AimpDataFieldFilter(IAIMPMLDataFieldFilter *aimpDataFieldFilter) : AimpObject(aimpDataFieldFilter)
{
    _dataField = nullptr;
}

AimpDataFieldFilter::~AimpDataFieldFilter()
{
    this->!AimpDataFieldFilter();
}

AimpDataFieldFilter::!AimpDataFieldFilter()
{
    _aimpObject->Release();
}

String^ AimpDataFieldFilter::Field::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELDFILTER_FIELD);
}

void AimpDataFieldFilter::Field::set(String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELDFILTER_FIELD, value);
}

FieldFilterOperationType AimpDataFieldFilter::Operation::get()
{
    int str = PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FIELDFILTER_OPERATION);
    return (FieldFilterOperationType)str;
}

void AimpDataFieldFilter::Operation::set(FieldFilterOperationType value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FIELDFILTER_OPERATION, (int)value);
}

System::Object^ AimpDataFieldFilter::Value1::get()
{
    System::String^ v;
    PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELDFILTER_VALUE1, v);
    return v;
}

void AimpDataFieldFilter::Value1::set(System::Object^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELDFILTER_VALUE2, value->ToString());
}

System::Object^ AimpDataFieldFilter::Value2::get()
{
    System::String^ v;
    PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELDFILTER_VALUE2, v);
    return v;
}

void AimpDataFieldFilter::Value2::set(System::Object^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELDFILTER_VALUE2, value->ToString());
}
