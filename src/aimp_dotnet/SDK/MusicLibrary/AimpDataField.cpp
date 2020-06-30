// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpDataField.h"

using namespace AIMP::SDK;

AIMP::SDK::AimpDataField::AimpDataField(IAIMPMLDataField* aimpObject) : AimpObject(aimpObject)
{
}

String^ AIMP::SDK::AimpDataField::Custom::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELD_PROPID_CUSTOM);
}

void AIMP::SDK::AimpDataField::Custom::set(String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELD_PROPID_CUSTOM, value);
}

String^ AIMP::SDK::AimpDataField::Name::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELD_PROPID_NAME);
}

void AIMP::SDK::AimpDataField::Name::set(String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELD_PROPID_NAME, value);
}

AimpDataFieldType AIMP::SDK::AimpDataField::Type::get()
{
    return static_cast<AimpDataFieldType>(PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FIELD_PROPID_TYPE)
    );
}

void AIMP::SDK::AimpDataField::Type::set(AimpDataFieldType value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FIELD_PROPID_TYPE, int(value));
}

AimpDataFieldFlagsType AIMP::SDK::AimpDataField::Flags::get()
{
    return static_cast<AimpDataFieldFlagsType>(PropertyListExtension::GetInt32(
        InternalAimpObject, AIMPML_FIELD_PROPID_FLAGS));
}

void AIMP::SDK::AimpDataField::Flags::set(AimpDataFieldFlagsType value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FIELD_PROPID_FLAGS, int(value));
}

ImageType AIMP::SDK::AimpDataField::Image::get()
{
    return static_cast<ImageType>(PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FIELD_PROPID_IMAGE));
}

void AIMP::SDK::AimpDataField::Image::set(ImageType value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FIELD_PROPID_IMAGE, int(value));
}

String^ AIMP::SDK::AimpDataField::DisplayValue::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELD_PROPID_DISPLAYVALUE);
}

void AIMP::SDK::AimpDataField::DisplayValue::set(String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELD_PROPID_DISPLAYVALUE, value);
}
