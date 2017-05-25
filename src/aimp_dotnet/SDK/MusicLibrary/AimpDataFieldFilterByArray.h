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

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::Collections::Generic;
        using namespace AIMP::SDK::MusicLibrary::DataFilter;

        public ref class AimpDataFieldFilterByArray : public IAimpDataFieldFilterByArray, public AimpObject<IAIMPMLDataFieldFilterByArray>
        {
        public:
            explicit AimpDataFieldFilterByArray(IAIMPMLDataFieldFilterByArray *aimpObject);

            virtual property String^ Field
            {
                String^ get();
                void set(String^ value);
            }

            virtual AimpActionResult GetData(IList<Object^>^ values);

            virtual AimpActionResult SetData(IList<Object^>^ values);
        };
    }
}
