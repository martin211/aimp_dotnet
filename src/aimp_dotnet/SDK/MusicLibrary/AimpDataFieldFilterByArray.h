/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 */
 
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
