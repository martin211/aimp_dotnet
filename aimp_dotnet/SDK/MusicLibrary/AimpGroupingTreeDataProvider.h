#pragma once

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::MusicLibrary::DataFilter;
        using namespace AIMP::SDK::MusicLibrary::DataStorage;

        public ref class AimpGroupingTreeDataProvider :
            public AimpObject<IAIMPMLGroupingTreeDataProvider>,
            public IAimpGroupingTreeDataProvider
        {
        public:
            explicit AimpGroupingTreeDataProvider(IAIMPMLGroupingTreeDataProvider* aimpObject) : AimpObject(aimpObject)
            {}

            virtual AIMP::SDK::AimpActionResult AppendFilter(AIMP::SDK::MusicLibrary::DataFilter::IAimpDataFilterGroup^ filter, AIMP::SDK::MusicLibrary::DataStorage::IAimpGroupingTreeSelection^ selection)
            {
                return AimpActionResult::NotImplemented;
            }

            virtual AIMP::SDK::MusicLibrary::DataStorage::CapabilitiesFlags GetCapabilities()
            {
                return (AIMP::SDK::MusicLibrary::DataStorage::CapabilitiesFlags)InternalAimpObject->GetCapabilities();
            }

            virtual AIMP::SDK::AimpActionResult GetData(AIMP::SDK::MusicLibrary::DataStorage::IAimpGroupingTreeSelection^ selection, AIMP::SDK::MusicLibrary::DataStorage::IAimpGroupingTreeDataProviderSelection^% data)
            {
                AIMP::SDK::MusicLibrary::DataStorage::IAimpGroupingTreeDataProviderSelection ^d = nullptr;
                data = d;
                return AimpActionResult::NotImplemented;
            }

            virtual AIMP::SDK::AimpActionResult GetFieldForAlphabeticIndex(System::String^ fileName)
            {
                return AimpActionResult::NotImplemented;
            }
        };
    }
}