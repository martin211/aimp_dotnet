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
            explicit AimpGroupingTreeSelection(IAIMPMLGroupingTreeSelection* aimpObject) : AimpObject(aimpObject)
            {}

            virtual int GetCount()
            {
                return InternalAimpObject->GetCount();
            }

            virtual AimpActionResult GetValue(int index, System::String^% fieldName, System::Object^% value)
            {
                IAIMPString* str;
                VARIANT* val;

                AimpActionResult result = CheckResult(InternalAimpObject->GetValue(index, &str, val));

                fieldName = AimpExtension::GetString(str);

                return result;
            }
        };
    }
}
