#pragma once
#include "..\AimpObject.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::MusicLibrary::DataFilter;

        public ref class AimpDataFilterGroup :
            public AimpObject<IAIMPMLDataFilterGroup>,
            public IAimpDataFilterGroup
        {
        public:
            explicit AimpDataFilterGroup(IAIMPMLDataFilterGroup *filterGroup);

            virtual property FilterGroupOperationType Operation
            {
                FilterGroupOperationType get();
                void set(FilterGroupOperationType value);
            }

            virtual AimpActionResult Add(String^ field, Variant value1, Variant value2, FilterGroupOperationType operation, IAimpDataFieldFilter^% filter);

            virtual AimpActionResult Add(String^ field, array<Variant>^ values, int count, IAimpDataFieldFilterByArray^% filter);

            virtual AimpActionResult AddGroup(IAimpDataFilterGroup^% group);

            virtual AimpActionResult Clear();

            virtual AimpActionResult Delete(int index);

            virtual int GetChildCount();
        };
    }
}
