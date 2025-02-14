//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "SDK/PlayList/Internal/InternalAimpPlaylistPreimage.h"

using namespace AIMP::SDK;
using namespace MusicLibrary;

namespace AIMP {
    namespace SDK {
        class InternalAimpMusicLibraryPlaylistPreimage :
            IUnknownInterfaceImpl<IAIMPMLPlaylistPreimage>,
            public IAIMPMLPlaylistPreimage,
            public InternalAimpPlaylistPreimage {
        private:
            gcroot<IAimpMusicLibraryPlaylistPreimage^> _managedInstance;
        public:
            typedef IUnknownInterfaceImpl<IAIMPMLPlaylistPreimage> Base;
            InternalAimpMusicLibraryPlaylistPreimage(gcroot<IAimpMusicLibraryPlaylistPreimage^> managedInstance);
            virtual HRESULT WINAPI GetFilter(IAIMPMLDataFilter** Filter);
            virtual HRESULT WINAPI GetStorage(IUnknown** Storage);
            virtual ULONG WINAPI AddRef(void);
            virtual ULONG WINAPI Release(void);
            virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
        };
    }
}
