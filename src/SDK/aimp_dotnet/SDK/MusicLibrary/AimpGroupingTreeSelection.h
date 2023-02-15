//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

namespace AIMP {
    namespace SDK {
        using namespace SDK;
        using namespace MusicLibrary::DataFilter;
        using namespace MusicLibrary::DataStorage;

        public ref class AimpGroupingTreeSelection :
            public AimpObject<IAIMPMLGroupingTreeSelection>,
            public IAimpGroupingTreeSelection {
        public:
            explicit AimpGroupingTreeSelection(IAIMPMLGroupingTreeSelection* aimpObject);

            virtual int GetCount();

            virtual TYPED_RESULT_2(String, Object) GetValue(int index);
        };
    }
}
