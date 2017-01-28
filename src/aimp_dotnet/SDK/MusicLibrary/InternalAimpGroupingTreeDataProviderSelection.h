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

        class InternalAimpGroupingTreeDataProviderSelection : public IUnknownInterfaceImpl<IAIMPMLGroupingTreeDataProviderSelection>
        {
        private:
            ULONG _LinkCounter = 1;
            gcroot<IAimpGroupingTreeDataProviderSelection^> _managedInstance;

        public:
            typedef IUnknownInterfaceImpl<IAIMPMLGroupingTreeDataProviderSelection> Base;

            explicit InternalAimpGroupingTreeDataProviderSelection(gcroot<IAimpGroupingTreeDataProviderSelection^> managedInstance);

            virtual HRESULT WINAPI GetDisplayValue(IAIMPString** S);

            virtual DWORD WINAPI GetFlags();

            virtual HRESULT WINAPI GetImageIndex(int* Index);

            virtual HRESULT WINAPI GetValue(IAIMPString** FieldName, VARIANT* Value);

            virtual BOOL WINAPI NextRow();

            virtual ULONG WINAPI AddRef(void);

            virtual ULONG WINAPI Release(void);

            virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
        };
    }
}
