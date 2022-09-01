//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpDataFieldFilter.h"

using namespace AIMP::SDK;

// TODO: #18
AimpDataFieldFilter::AimpDataFieldFilter(IAIMPMLDataFieldFilter* aimpDataFieldFilter) : AimpObject(aimpDataFieldFilter, false) {
    _dataField = nullptr;
}

String^ AimpDataFieldFilter::Field::get() {
    return PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELDFILTER_FIELD);
}

void AimpDataFieldFilter::Field::set(String^ value) {
    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELDFILTER_FIELD, value);
}

FieldFilterOperationType AimpDataFieldFilter::Operation::get() {
    int str = PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FIELDFILTER_OPERATION);
    return FieldFilterOperationType(str);
}

void AimpDataFieldFilter::Operation::set(FieldFilterOperationType value) {
    PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FIELDFILTER_OPERATION, int(value));
}

Object^ AimpDataFieldFilter::Value1::get() {
    String^ v;
    PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELDFILTER_VALUE1, v);
    return v;
}

void AimpDataFieldFilter::Value1::set(Object^ value) {
    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELDFILTER_VALUE2, value->ToString());
}

Object^ AimpDataFieldFilter::Value2::get() {
    String^ v;
    PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELDFILTER_VALUE2, v);
    return v;
}

void AimpDataFieldFilter::Value2::set(Object^ value) {
    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELDFILTER_VALUE2, value->ToString());
}
