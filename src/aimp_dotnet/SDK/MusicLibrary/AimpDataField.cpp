/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#include "Stdafx.h"
#include "AimpDataField.h"

using namespace AIMP::SDK;

AIMP::SDK::AimpDataField::AimpDataField(IAIMPMLDataField* aimpObject) : AimpObject(aimpObject)
{}

String^ AIMP::SDK::AimpDataField::Custom::get()
{
    return AIMP::SDK::PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELD_PROPID_CUSTOM);
}

void AIMP::SDK::AimpDataField::Custom::set(String^ value)
{
    AIMP::SDK::PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELD_PROPID_CUSTOM, value);
}

String^ AIMP::SDK::AimpDataField::Name::get()
{
    return AIMP::SDK::PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELD_PROPID_NAME);
}

void AIMP::SDK::AimpDataField::Name::set(String^ value)
{
    AIMP::SDK::PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELD_PROPID_NAME, value);
}

AimpDataFieldType AIMP::SDK::AimpDataField::Type::get()
{
    return (AimpDataFieldType)AIMP::SDK::PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FIELD_PROPID_TYPE);
}

void AIMP::SDK::AimpDataField::Type::set(AimpDataFieldType value)
{
    AIMP::SDK::PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FIELD_PROPID_TYPE, (int)value);
}

AimpDataFieldFlagsType AIMP::SDK::AimpDataField::Flags::get()
{
    return (AimpDataFieldFlagsType)AIMP::SDK::PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FIELD_PROPID_FLAGS);
}

void AIMP::SDK::AimpDataField::Flags::set(AimpDataFieldFlagsType value)
{
    AIMP::SDK::PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FIELD_PROPID_FLAGS, (int)value);
}

ImageType AIMP::SDK::AimpDataField::Image::get()
{
    return (ImageType)AIMP::SDK::PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FIELD_PROPID_IMAGE);
}

void AIMP::SDK::AimpDataField::Image::set(ImageType value)
{
    AIMP::SDK::PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FIELD_PROPID_IMAGE, (int)value);
}

String^ AIMP::SDK::AimpDataField::DisplayValue::get()
{
    return AIMP::SDK::PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELD_PROPID_DISPLAYVALUE);
}

void AIMP::SDK::AimpDataField::DisplayValue::set(String^ value)
{
    AIMP::SDK::PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELD_PROPID_DISPLAYVALUE, value);
}
