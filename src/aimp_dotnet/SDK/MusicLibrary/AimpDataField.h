#pragma once

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::MusicLibrary::DataStorage;

        public ref class AimpDataField :
            public AimpObject<IAIMPMLDataField>,
            public IAimpDataField
        {
        public:
            explicit AimpDataField(IAIMPMLDataField* aimpObject) : AimpObject(aimpObject)
            {}

            virtual property String^ Custom
            {
                String^ get()
                {
                    return AIMP::SDK::PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELD_PROPID_CUSTOM);
                }

                void set(String^ value)
                {
                    AIMP::SDK::PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELD_PROPID_CUSTOM, value);
                }
            }

            virtual property String^ Name
            {
                String^ get()
                {
                    return AIMP::SDK::PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELD_PROPID_NAME);
                }

                void set(String^ value)
                {
                    AIMP::SDK::PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELD_PROPID_NAME, value);
                }
            }

            virtual property AimpDataFieldType Type
            {
                AimpDataFieldType get()
                {
                    return (AimpDataFieldType)AIMP::SDK::PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FIELD_PROPID_TYPE);
                }

                void set(AimpDataFieldType value)
                {
                    AIMP::SDK::PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FIELD_PROPID_TYPE, (int)value);
                }
            }

            virtual property AimpDataFieldFlagsType Flags
            {
                AimpDataFieldFlagsType get()
                {
                    return (AimpDataFieldFlagsType)AIMP::SDK::PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FIELD_PROPID_FLAGS);
                }

                void set(AimpDataFieldFlagsType value)
                {
                    AIMP::SDK::PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FIELD_PROPID_FLAGS, (int)value);
                }
            }

            virtual property ImageType Image
            {
                ImageType get()
                {
                    return (ImageType)AIMP::SDK::PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FIELD_PROPID_IMAGE);
                }

                void set(ImageType value)
                {
                    AIMP::SDK::PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FIELD_PROPID_IMAGE, (int)value);
                }
            }

            virtual property String^ DisplayValue
            {
                String^ get()
                {
                    return AIMP::SDK::PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELD_PROPID_DISPLAYVALUE);
                }

                void set(String^ value)
                {
                    AIMP::SDK::PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELD_PROPID_DISPLAYVALUE, value);
                }
            }
        };
    }
}
