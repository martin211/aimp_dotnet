// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace MusicLibrary::DataStorage;

        private ref class AimpDataField :
            public AimpObject<IAIMPMLDataField>,
            public IAimpDataField {
        public:
            explicit AimpDataField(IAIMPMLDataField* aimpObject);

            virtual property String^ Custom
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Name
            {
                String^ get();
                void set(String^ value);
            }

            virtual property AimpDataFieldType Type
            {
                AimpDataFieldType get();
                void set(AimpDataFieldType value);
            }

            virtual property AimpDataFieldFlagsType Flags
            {
                AimpDataFieldFlagsType get();
                void set(AimpDataFieldFlagsType value);
            }

            virtual property ImageType Image
            {
                ImageType get();
                void set(ImageType value);
            }

            virtual property String^ DisplayValue
            {
                String^ get();
                void set(String^ value);
            }
        };
    }
}
