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
            explicit AimpGroupingTreeDataProviderSelection(IAIMPMLGroupingTreeDataProviderSelection* aimpObject) : AimpObject(aimpObject)
            {}

            virtual AimpActionResult GetDisplayValue(System::String^% displayValue)
            {
                return AimpActionResult::NotImplemented;
            }

            virtual GroupingTreeNodeFlags GetFlags()
            {
                return GroupingTreeNodeFlags::AIMPML_GROUPINGTREENODE_FLAG_HASCHILDREN;
            }

            virtual AimpActionResult GetImageIndex(FieldImageIndex% imageIndex)
            {
                return AimpActionResult::NotImplemented;
            }

            virtual AimpActionResult GetValue(System::String^% fieldName, System::Object^% value)
            {
                return AimpActionResult::NotImplemented;
            }

            virtual bool NextRecord()
            {
                return false;
            }
        };
    }
}
