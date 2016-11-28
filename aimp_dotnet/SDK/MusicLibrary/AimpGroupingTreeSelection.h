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

            ~AimpGroupingTreeSelection()
            {
                this->!AimpGroupingTreeSelection();
            }

            !AimpGroupingTreeSelection()
            {
                System::Diagnostics::Debug::WriteLine("Dispose AimpGroupingTreeSelection");
                if (_aimpObject != NULL)
                {
                    _aimpObject->Release();
                    _aimpObject = NULL;
                }
            }

            virtual int GetCount()
            {
                return InternalAimpObject->GetCount();
            }

            virtual AimpActionResult GetValue(int index, System::String^% fieldName, System::Object^% value)
            {
                IAIMPString* str;
                VARIANT val;

                fieldName = nullptr;
                value = nullptr;

                AimpActionResult result = CheckResult(InternalAimpObject->GetValue(index, &str, &val));

                try
                {
                    if (result == AimpActionResult::Ok)
                    {
                        if (str != NULL)
                            fieldName = AimpExtension::GetString(str);

                        value = AimpExtension::FromVaiant(&val);
                    }
                }
                finally
                {
                    if (str != NULL)
                    {
                        str->Release();
                        str = NULL;
                    }
                }

                return result;
            }
        };
    }
}
