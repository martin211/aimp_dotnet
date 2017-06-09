// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once
#include "AimpDataField.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::MusicLibrary::DataFilter;

        public ref class AimpDataFieldFilter :
            public AimpObject<IAIMPMLDataFieldFilter>,
            public IAimpDataFieldFilter
        {
        private:
            AIMP::SDK::AimpDataField^ _dataField;

        public:
            explicit AimpDataFieldFilter(IAIMPMLDataFieldFilter *aimpDataFieldFilter);

            ~AimpDataFieldFilter();

            !AimpDataFieldFilter();

            virtual property String^ Field
            {
                String^ get();
                void set(String^ value);
            }

            virtual property FieldFilterOperationType Operation
            {
                FieldFilterOperationType get();
                void set(FieldFilterOperationType value);
            }

            virtual property System::Object^ Value1
            {
                System::Object^ get();
                void set(System::Object^ value);
            }

            virtual property System::Object^ Value2
            {
                System::Object^ get();
                void set(System::Object^ value);
            }
        };
    }
}
