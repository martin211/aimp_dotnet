#pragma once

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::MusicLibrary::DataFilter;
        using namespace AIMP::SDK::MusicLibrary::DataStorage;

        public ref class AimpGroupingTreeDataProviderSelection :
            public AimpObject<IAIMPMLGroupingTreeDataProviderSelection>,
            public IAimpGroupingTreeDataProviderSelection
        {
        public:
            explicit AimpGroupingTreeDataProviderSelection(AimpGroupingTreeDataProviderSelection* aimpObject) : AimpObject(aimpObject)
            {}

            virtual AimpActionResult GetDisplayValue(System::String^% displayValue)
            {}

            virtual GroupingTreeNodeFlags GetFlags()
            {}

            virtual AimpActionResult GetImageIndex(FieldImageIndex imageIndex)
            {}

            virtual AimpActionResult GetValue(System::String^% fieldName, System::Object^% value)
            {}

            virtual bool NextRecord()
            {}
        };
    }
}
