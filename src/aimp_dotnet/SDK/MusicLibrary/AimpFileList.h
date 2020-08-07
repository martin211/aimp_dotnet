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
        using namespace MusicLibrary;

        public ref class AimpFileList :
            public AimpObject<IAIMPMLFileList>,
            public IAimpFileList {
        public:
            explicit AimpFileList(IAIMPMLFileList* aimpObject);

            virtual ActionResult Add(Object^ id, String^ fileName);

            virtual ActionResult Clear();

            virtual ActionResult Delete(int index);

            virtual ActionResult Insert(int index, Object^ id, String^ fileName);

            virtual int GetCount();

            virtual TYPED_RESULT(String) GetFileName(int index);

            virtual ActionResult SetFileName(int index, String^ fileName);

            virtual TYPED_RESULT(Object) GetId(int index);

            virtual ActionResult SetId(int index, Object^ id);

            virtual TYPED_RESULT(IAimpFileList) Clone();
        };
    }
}
