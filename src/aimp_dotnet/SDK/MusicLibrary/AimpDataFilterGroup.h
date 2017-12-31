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
#include "SDK\AimpObject.h"

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

            ~AimpDataFilterGroup()
            {
                this->!AimpDataFilterGroup();
            }

            !AimpDataFilterGroup()
            {
                //_aimpObject->Release();
            }

            virtual property FilterGroupOperationType Operation
            {
                FilterGroupOperationType get();
                void set(FilterGroupOperationType value);
            }

            virtual AimpActionResult Add(String^ field, Object^ value1, Object^ value2, FieldFilterOperationType operation, IAimpDataFieldFilter^% filter);

            virtual AimpActionResult Add(String^ field, array<Object^>^ values, int count, IAimpDataFieldFilterByArray^% filter);

            virtual AimpActionResult AddGroup(IAimpDataFilterGroup^% group);

            virtual AimpActionResult Clear();

            virtual AimpActionResult Delete(int index);

            virtual AimpActionResult GetChild(int index, IAimpDataFilterGroup^% group);

            virtual AimpActionResult GetChild(int index, IAimpDataFieldFilter^% fieldFilter);

            virtual int GetChildCount();

            virtual void BeginUpdate();

            virtual void EndUpdate();
        };
    }
}
