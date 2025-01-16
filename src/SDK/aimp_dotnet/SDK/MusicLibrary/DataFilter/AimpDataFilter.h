//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "AimpDataFilterGroup.h"
using namespace System::Collections::Generic;

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace MusicLibrary;

        public ref class AimpDataFilter :
            public AimpDataFilterGroup,
            public IAimpDataFilter {
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

            virtual ActionResult Assign(IAimpDataFilter^ source);

            virtual TYPED_RESULT(IAimpDataFilter) Clone();
            
            virtual property List<IAimpSortItem^>^ SortByList
            {
                List<IAimpSortItem^>^ get();
                void set(List<IAimpSortItem^>^ sort_by_list);
            }
        };
    }
}
