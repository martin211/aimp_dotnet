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
                    IAIMPPropertyList2 *properties = NULL;
                    try
                    {
                        if (GetProperties(&properties) == AimpActionResult::Ok)
                        {
                            IAIMPMLDataField* dataField;
                            if (PropertyListExtension::GetObject(properties, AIMPML_FIELDFILTER_FIELD, IID_IAIMPMLDataField, (void**)&dataField) == AimpActionResult::Ok)
                            {
                                return gcnew AIMP::SDK::AimpDataField(dataField);
                            }

                            return nullptr;
                        }
                    }
                    finally
                    {
                        if (properties != NULL)
                        {
                            properties->Release();
                            properties = NULL;
                        }
                    }
                }

                void set(IAimpDataField^ value)
                {
                    IAIMPPropertyList2 *properties = NULL;
                    try
                    {
                        if (GetProperties(&properties) == AimpActionResult::Ok)
                        {
                            //todo complete it.
                            //PropertyListExtension::SetObject(properties, AIMPML_FIELDFILTER_FIELD, value);
                        }
                    }
                    finally
                    {
                        if (properties != NULL)
                        {
                            properties->Release();
                            properties = NULL;
                        }
                    }
                }
            }

            virtual property FieldFilterOperationType Operation
            {
                FieldFilterOperationType get()
                {
                    IAIMPPropertyList2 *properties = NULL;
                    try
                    {
                        if (GetProperties(&properties) == AimpActionResult::Ok)
                        {
                            String^ str = PropertyListExtension::GetString(properties, AIMPML_FIELDFILTER_OPERATION);
                            return (FieldFilterOperationType)System::Enum::Parse(FieldFilterOperationType::typeid, str);
                        }
                    }
                    finally
                    {
                        if (properties != NULL)
                        {
                            properties->Release();
                            properties = NULL;
                        }
                    }
                }

                void set(FieldFilterOperationType value)
                {
                    IAIMPPropertyList2 *properties = NULL;
                    try
                    {
                        if (GetProperties(&properties) == AimpActionResult::Ok)
                        {
                            PropertyListExtension::SetString(properties, AIMPML_FIELDFILTER_OPERATION, value.ToString());
                        }
                    }
                    finally
                    {
                        if (properties != NULL)
                        {
                            properties->Release();
                            properties = NULL;
                        }
                    }
                }
            }

            virtual property Variant Value1
            {
                Variant get()
                {
                    return Variant();
                }

                void set(Variant value)
                {}
            }

            virtual property Variant Value2
            {
                Variant get()
                {
                    return Variant();
                }

                void set(Variant value)
                {}
            }

        private:
            AimpActionResult GetProperties(IAIMPPropertyList2** properties)
            {
                IAIMPPropertyList2 *prop = NULL;
                AimpActionResult result = CheckResult(InternalAimpObject->QueryInterface(IID_IAIMPPropertyList2, (void**)&prop));
                *properties = prop;
                return result;
            }

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
