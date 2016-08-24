#pragma once
#include "AimpDataField.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK;

        public ref class AimpDataFieldFilter :
            public AimpObject<IAIMPMLDataFieldFilter>,
            public IAimpDataFieldFilter
        {
        private:
            AIMP::SDK::AimpDataField^ _dataField;

        public:
            explicit AimpDataFieldFilter(IAIMPMLDataFieldFilter *aimpDataFieldFilter) : AimpObject(aimpDataFieldFilter)
            {
                _dataField = nullptr;
            }

            !AimpDataFieldFilter()
            {
                Release();
            }

            ~AimpDataFieldFilter()
            {
                this->!AimpDataFieldFilter();
            }

            virtual property String^ Field
            {
                String^ get()
                {
                    return PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELDFILTER_FIELD);
                }

                void set(String^ value)
                {
                    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELDFILTER_FIELD, value);
                }
            }

            virtual property FieldFilterOperationType Operation
            {
                FieldFilterOperationType get()
                {
                    int str = PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FIELDFILTER_OPERATION);
                    return (FieldFilterOperationType)str;
                    //return (FieldFilterOperationType)System::Enum::Parse(FieldFilterOperationType::typeid, str);
                }

                void set(FieldFilterOperationType value)
                {
                    PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FIELDFILTER_OPERATION, (int)value);
                }
            }

            virtual property System::Object^ Value1
            {
                System::Object^ get()
                {
                    System::String^ v;
                    PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELDFILTER_VALUE1, v);
                    return v;
                }

                void set(System::Object^ value)
                {
                    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELDFILTER_VALUE2, value->ToString());
                }
            }

            virtual property System::Object^ Value2
            {
                System::Object^ get()
                {
                    System::String^ v;
                    PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELDFILTER_VALUE2, v);
                    return v;
                }

                void set(System::Object^ value)
                {
                    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELDFILTER_VALUE2, value->ToString());
                }
            }

        private:
            void Release()
            {
                if (InternalAimpObject != NULL)
                {
                    _aimpObject->Release();
                    _aimpObject = NULL;
                }
            }
        };
    }
}
