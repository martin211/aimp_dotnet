//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "SDK\BaseAimpService.h"

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::Playlist;
        using namespace AIMP::SDK::Playlist::Extensions;

        class AimpPlaylistPreimageFactory : public IUnknownInterfaceImpl<IAIMPExtensionPlaylistPreimageFactory> {
        private:
            gcroot<IAimpExtensionPlaylistPreimageFactory^> _managedObject;
            typedef IUnknownInterfaceImpl<IAIMPExtensionPlaylistPreimageFactory> Base;

        public:
            AimpPlaylistPreimageFactory(gcroot<IAimpExtensionPlaylistPreimageFactory^> managedObject);

            virtual HRESULT WINAPI CreatePreimage(IAIMPPlaylistPreimage** preimage);

            virtual HRESULT WINAPI GetID(IAIMPString** ID);

            virtual HRESULT WINAPI GetName(IAIMPString** Name);

            virtual DWORD WINAPI GetFlags();

            virtual ULONG WINAPI AddRef(void);

            virtual ULONG WINAPI Release(void);

            virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
        };
    }
}
