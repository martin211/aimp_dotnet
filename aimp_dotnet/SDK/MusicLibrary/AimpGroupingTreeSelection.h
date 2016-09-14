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
                IAIMPString* str = NULL;
                VARIANT* val = NULL;
                fieldName = nullptr;
                value = nullptr;

                AimpActionResult result = CheckResult(InternalAimpObject->GetValue(index, &str, val));

                if (result == AimpActionResult::Ok)
                {
                    if (str != NULL)
                        fieldName = AimpExtension::GetString(str);
                }

                return result;
            }
        };
    }
}
