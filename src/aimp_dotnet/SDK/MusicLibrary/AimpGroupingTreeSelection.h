#pragma once

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::MusicLibrary::DataFilter;
        using namespace AIMP::SDK::MusicLibrary::DataStorage;

        public ref class AimpGroupingTreeSelection :
            public AimpObject<IAIMPMLGroupingTreeSelection>,
            public IAimpGroupingTreeSelection
        {
        public:
            explicit AimpGroupingTreeSelection(IAIMPMLGroupingTreeSelection* aimpObject);

            ~AimpGroupingTreeSelection();

            !AimpGroupingTreeSelection();

            virtual int GetCount();

            virtual AimpActionResult GetValue(int index, System::String^% fieldName, System::Object^% value);
        };
    }
}
