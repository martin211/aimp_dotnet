//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include <vcclr.h>

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace SDK;
        using namespace MusicLibrary::DataFilter;
        using namespace MusicLibrary::DataStorage;

        class InternalAimpGroupingTreeDataProviderSelection :
            public IUnknownInterfaceImpl<IAIMPMLGroupingTreeDataProviderSelection> {
        private:
            ULONG _LinkCounter = 1;
            gcroot<IAimpGroupingTreeDataProviderSelection^> _managedInstance;

        public:
            typedef IUnknownInterfaceImpl<IAIMPMLGroupingTreeDataProviderSelection> Base;

            explicit InternalAimpGroupingTreeDataProviderSelection(
                gcroot<IAimpGroupingTreeDataProviderSelection^> managedInstance);

            virtual HRESULT WINAPI GetDisplayValue(IAIMPString** S);

            virtual DWORD WINAPI GetFlags();

            virtual HRESULT WINAPI GetImageIndex(int* Index);

            virtual HRESULT WINAPI GetValue(IAIMPString** FieldName, VARIANT* Value);

            virtual BOOL WINAPI NextRecord();

            virtual ULONG WINAPI AddRef(void);

            virtual ULONG WINAPI Release(void);

            virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
        };
    }
}
