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
#include "AimpDataFilterGroup.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace MusicLibrary;

        public ref class AimpDataFilter :
            public AimpDataFilterGroup,
            public IAimpDataFilter
        {
        internal:
            IAIMPMLDataFilter* InternalDataFilter;
        public:
            explicit AimpDataFilter(IAIMPMLDataFilter* native);

            virtual property int Offset
            {
                int get();
                void set(int value);
            }

            virtual property int Limit
            {
                int get();
                void set(int value);
            }

            virtual property String^ SortBy
            {
                String^ get();
                void set(String^ value);
            }

            virtual property SortDirectionType SortDirection
            {
                SortDirectionType get();
                void set(SortDirectionType value);
            }

            virtual property String^ SearchString
            {
                String^ get();
                void set(String^ value);
            }

            virtual property int AlphaBeticIndex
            {
                int get();
                void set(int value);
            }

            virtual AimpActionResult Assign(IAimpDataFilter^ source);

            virtual AimpActionResult Clone(IAimpDataFilter^% source);
        };
    }
}
