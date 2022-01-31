// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "SDK\AimpObject.h"

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace MusicLibrary::DataFilter;

        public ref class AimpDataFilterGroup :
            public AimpObject<IAIMPMLDataFilterGroup>,
            public IAimpDataFilterGroup {
        public:
            explicit AimpDataFilterGroup(IAIMPMLDataFilterGroup* filterGroup);

            virtual property FilterGroupOperationType Operation
            {
                FilterGroupOperationType get();
                void set(FilterGroupOperationType value);
            }

            virtual TYPED_RESULT(IAimpDataFieldFilter) Add(String^ field, Object^ value1, Object^ value2,
                                                           FieldFilterOperationType operation);

            virtual TYPED_RESULT(IAimpDataFieldFilterByArray) Add(String^ field, array<Object^>^ values, int count);

            virtual TYPED_RESULT(IAimpDataFilterGroup) AddGroup();

            virtual ActionResult Clear();

            virtual ActionResult Delete(int index);

            virtual TYPED_RESULT(IAimpDataFilterGroup) GetFilterGroup(int index);

            virtual TYPED_RESULT(IAimpDataFieldFilter) GetFieldFilter(int index);

            virtual int GetChildCount();

            virtual void BeginUpdate();

            virtual void EndUpdate();
        };
    }
}
