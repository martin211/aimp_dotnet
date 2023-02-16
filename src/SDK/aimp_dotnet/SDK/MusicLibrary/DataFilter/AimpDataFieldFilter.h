//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "SDK/MusicLibrary/DataStorage/AimpDataField.h"

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace SDK;
        using namespace MusicLibrary::DataFilter;

        public ref class AimpDataFieldFilter :
            public AimpObject<IAIMPMLDataFieldFilter>,
            public IAimpDataFieldFilter {
        private:
            SDK::AimpDataField^ _dataField;

        public:
            explicit AimpDataFieldFilter(IAIMPMLDataFieldFilter* aimpDataFieldFilter);

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

            virtual property Object^ Value1
            {
                Object^ get();
                void set(Object^ value);
            }

            virtual property Object^ Value2
            {
                Object^ get();
                void set(Object^ value);
            }
        };
    }
}
