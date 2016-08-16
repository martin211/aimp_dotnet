#pragma once

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::MusicLibrary;
        using namespace AIMP::SDK::MusicLibrary::DataFilter;

        public ref class AimpGroupingTreeDataProvider :
            public AimpObject<IAIMPMLGroupingTreeDataProvider>,
            public IAimpGroupingTreeDataProvider
        {
        public:
            explicit AimpGroupingTreeDataProvider(IAIMPMLGroupingTreeDataProvider *aimpObject) : AimpObject(aimpObject)
            {}

            virtual AimpActionResult AppendFilter(IAimpDataFilterGroup^ filter, IAimpGroupingTreeSelection^ selection)
            {
                return AimpActionResult::NotImplemented;
            }

            virtual AIMP::SDK::MusicLibrary::DataStorage::CapabilitiesFlags GetCapabilities()
            {
                return (CapabilitiesFlags)InternalAimpObject->GetCapabilities();
            }

            virtual AimpActionResult GetData(IAimpGroupingTreeSelection ^selection, IAimpGroupingTreeDataProviderSelection ^%data)
            {
                data = nullptr;
                return AimpActionResult::NotImplemented;
            }

            virtual AimpActionResult GetFieldForAlphabeticIndex(String^ fileName)
            {
                return AimpActionResult::NotImplemented;
            }
        };
    }
}