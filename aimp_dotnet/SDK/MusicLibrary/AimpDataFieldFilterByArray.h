#pragma once

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::Collections::Generic;
        using namespace AIMP::SDK::MusicLibrary;

        public ref class AimpDataFieldFilterByArray : public IAimpDataFieldFilterByArray, public AimpObject<IAIMPMLDataFieldFilterByArray>
        {
        public:
            explicit AimpDataFieldFilterByArray(IAIMPMLDataFieldFilterByArray *aimpObject) : AimpObject(aimpObject)
            { }

            virtual property String^ Field
            {
                String^ get()
                {
                    return PropertyListExtension::GetString(InternalAimpObject, AIMPML_FIELDFILTERBYARRAY_FIELD);
                }

                void set(String^ value)
                {
                    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FIELDFILTERBYARRAY_FIELD, value);
                }
            }

            virtual AimpActionResult GetData(IList<Object^>^ values)
            {
                values = nullptr;
                return AimpActionResult::NotImplemented;
            }

            virtual AimpActionResult SetData(IList<Object^>^ values)
            {
                return AimpActionResult::NotImplemented;
            }
        };
    }
}
