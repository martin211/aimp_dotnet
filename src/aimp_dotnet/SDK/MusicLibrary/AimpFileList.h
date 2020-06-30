// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace MusicLibrary;

        public ref class AimpFileList :
            public AimpObject<IAIMPMLFileList>,
            public IAimpFileList
        {
        public:
            explicit AimpFileList(IAIMPMLFileList* aimpObject);

            virtual ActionResultType Add(Object^ id, String^ fileName);

            virtual ActionResultType Clear();

            virtual ActionResultType Delete(int index);

            virtual ActionResultType Insert(int index, Object^ id, String^ fileName);

            virtual int GetCount();

            virtual ActionResultType GetFileName(int index, String^% fileName);

            virtual ActionResultType SetFileName(int index, String^ fileName);

            virtual ActionResultType GetId(int index, Object^% id);

            virtual ActionResultType SetId(int index, Object^ id);

            virtual ActionResultType Clone(IAimpFileList^% list);
        };
    }
}
