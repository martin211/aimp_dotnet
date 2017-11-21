// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once
#include "SDK\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::Playlist;

        class AimpPlaylistPreimageFactory : public IUnknownInterfaceImpl<IAIMPExtensionPlaylistPreimageFactory>
        {
        private:
            gcroot<Playlist::IAimpExtensionPlaylistPreimageFactory^> _managedObject;
            typedef IUnknownInterfaceImpl<IAIMPExtensionPlaylistPreimageFactory> Base;

        public:
            AimpPlaylistPreimageFactory(gcroot<Playlist::IAimpExtensionPlaylistPreimageFactory^> managedObject);

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
