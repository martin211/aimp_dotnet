#pragma once
#include <vcclr.h>

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::MusicLibrary::DataFilter;
        using namespace AIMP::SDK::MusicLibrary::DataStorage;

        class InternalAimpGroupingTreeDataProviderSelection :
            public IUnknownInterfaceImpl<IAIMPMLGroupingTreeDataProviderSelection>
        {
        private:
            gcroot<IAimpGroupingTreeDataProviderSelection^> _managedInstance;
            typedef IUnknownInterfaceImpl<IAIMPMLGroupingTreeDataProviderSelection> Base;

        public:
            explicit InternalAimpGroupingTreeDataProviderSelection(gcroot<IAimpGroupingTreeDataProviderSelection^> managedInstance)
            {
                _managedInstance = managedInstance;
            }

            virtual HRESULT WINAPI GetDisplayValue(IAIMPString** S)
            {
                String^ str;
                AimpActionResult result = _managedInstance->GetDisplayValue(str);

                if (result == AimpActionResult::Ok)
                {
                    *S = AimpExtension::GetAimpString(str);
                }

                return (HRESULT)result;
            }

            virtual DWORD WINAPI GetFlags()
            {
                return (DWORD)_managedInstance->GetFlags();
            }

            virtual HRESULT WINAPI GetImageIndex(int* Index)
            {
                FieldImageIndex index;
                AimpActionResult result = _managedInstance->GetImageIndex(index);

                if (result == AimpActionResult::Ok)
                {
                    *Index = (int)index;
                }

                return (HRESULT)result;
            }

            virtual HRESULT WINAPI GetValue(IAIMPString** FieldName, VARIANT* Value)
            {
                String^ fieldName;
                Object^ val;

                AimpActionResult result = _managedInstance->GetValue(fieldName, val);

                if (result == AimpActionResult::Ok)
                {
                    *FieldName = AimpExtension::GetAimpString(fieldName);
                    VARIANT v = AimpExtension::ToVariant(val);
                    Value = &v;
                }

                return (HRESULT)result;
            }

            virtual BOOL WINAPI NextRow()
            {
                return (BOOL)_managedInstance->NextRow();
            }
        };
    }
}
