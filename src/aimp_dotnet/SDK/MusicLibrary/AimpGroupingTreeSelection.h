// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
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
        using namespace SDK;
        using namespace MusicLibrary::DataFilter;
        using namespace MusicLibrary::DataStorage;

        public ref class AimpGroupingTreeSelection :
            public AimpObject<IAIMPMLGroupingTreeSelection>,
            public IAimpGroupingTreeSelection
        {
        public:
            explicit AimpGroupingTreeSelection(IAIMPMLGroupingTreeSelection* aimpObject);

            ~AimpGroupingTreeSelection();

            !AimpGroupingTreeSelection();

            virtual int GetCount();

            virtual AimpActionResult GetValue(int index, String^% fieldName, Object^% value);
        };
    }
}
