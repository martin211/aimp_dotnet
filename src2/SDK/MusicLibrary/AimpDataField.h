/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 */
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
