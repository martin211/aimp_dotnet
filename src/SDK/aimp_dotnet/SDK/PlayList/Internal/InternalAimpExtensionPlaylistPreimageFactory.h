// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

namespace AIMP {
    namespace SDK {
        using namespace SDK;
        using namespace Playlist;
        using namespace Playlist::Extensions;

        class InternalAimpExtensionPlaylistPreimageFactory :
            public IUnknownInterfaceImpl<IAIMPExtensionPlaylistPreimageFactory>
            //public IAIMPPlaylistPreimageDataProvider
        {
        private:
            gcroot<IAimpExtensionPlaylistPreimageFactory^> _managedInstance;
        public:
            typedef IUnknownInterfaceImpl<IAIMPExtensionPlaylistPreimageFactory> Base;

            InternalAimpExtensionPlaylistPreimageFactory(
                gcroot<IAimpExtensionPlaylistPreimageFactory^> managedInstance);

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
