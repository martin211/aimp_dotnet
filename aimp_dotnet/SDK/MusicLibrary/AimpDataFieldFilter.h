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
        public:
            explicit AimpDataFieldFilter(IAIMPMLDataFieldFilter *aimpDataFieldFilter) : AimpObject(aimpDataFieldFilter)
            {}

            !AimpDataFieldFilter()
            {
                Release();
            }

            ~AimpDataFieldFilter()
            {
                this->!AimpDataFieldFilter();
            }

            virtual property IAimpDataField^ Field
            {
                IAimpDataField^ get()
                {
                    IAIMPMLDataField* dataField;
                    if (PropertyListExtension::GetObject(InternalAimpObject, AIMPML_FIELDFILTER_FIELD, IID_IAIMPMLDataField, (void**)&dataField) == AimpActionResult::Ok)
                    {
                        return gcnew AIMP::SDK::AimpDataField(dataField);
                    }

                    return nullptr;
                }

                void set(IAimpDataField^ value)
                {
                    //todo complete it.
                    //PropertyListExtension::SetObject(properties, AIMPML_FIELDFILTER_FIELD, value);
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
                    System::Object^ v;
                    PropertyListExtension::GetVariant(InternalAimpObject, AIMPML_FIELDFILTER_VALUE1, v);
                    return v;
                }

                void set(System::Object^ value)
                {}
            }

            virtual property System::Object^ Value2
            {
                System::Object^ get()
                {
                    System::Object^ v;
                    PropertyListExtension::GetVariant(InternalAimpObject, AIMPML_FIELDFILTER_VALUE2, v);
                    return v;
                }

                void set(System::Object^ value)
                {}
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
